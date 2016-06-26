/*
    Copyright 2015 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "D_SDLRenderer2D.h"

#include <iostream>
#include "SDL_image.h"
#include "D_Log.h"
#include "D_SDLRenderComponent2D.h"
#include "D_SDLTexture.h"
#include "D_Transform2.h"


Diamond::SDLRenderer2D::SDLRenderer2D() 
    : m_window(nullptr), m_renderer(nullptr) {}

Diamond::SDLRenderer2D::~SDLRenderer2D() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    
    IMG_Quit();
    SDL_Quit();
}


bool Diamond::SDLRenderer2D::init(const Config &config) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Log::log("SDL failed to initialize! SDL Error: " + std::string(SDL_GetError()));
        return false;
    }

    // Create window
    m_window = SDL_CreateWindow(config.game_name.c_str(),
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED,
                                config.window_width, 
                                config.window_height, 
                                config.fullscreen 
                                || config.window_width <= 0
                                || config.window_height <= 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    if (m_window == nullptr) {
        Log::log("SDL failed to create window! SDL Error: " + std::string(SDL_GetError()));
        return false;
    }

    // Create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED
                                              | (config.vsync ? SDL_RENDERER_PRESENTVSYNC : 0x00000000));
    if (m_renderer == nullptr) {
        Log::log("SDL failed to create renderer! SDL Error: " + std::string(SDL_GetError()));
        return false;
    }
    SDL_SetRenderDrawColor(m_renderer, config.bg_color.r, config.bg_color.g, config.bg_color.b, config.bg_color.a);

    // Initialize image loading
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(img_flags) != img_flags) {
        Log::log("SDL_image failed to initialize! SDL_image Error: " + std::string(IMG_GetError()));
        // return false; // TODO: what's wrong with SDL Image init on Android?
    }

    return true;
}

void Diamond::SDLRenderer2D::renderAll() {
    // Render all the graphics
    SDL_RenderClear(m_renderer);
    for (auto l = m_render_objects.begin(); l != m_render_objects.end(); ++l) {
        for (auto i = l->begin(); i != l->end(); ++i) {
            //Log::log(i->transform.position.x + " and " + i->transform.position.y + " and " + i->transform.scale); // DEBUG
            Transform2<tSDLrender_pos, tSDLrender_rot, tD_real> transform = (*i).getTransform();

            SDL_Point pivot = (*i).pivot();
            SDL_Rect clip = (*i).clip();

            SDL_Rect render_rect = {
                (int)(transform.position.x - pivot.x), // render position x
                (int)(transform.position.y - pivot.y), // render position y
                (int)(clip.w * transform.scale.x), // render width
                (int)(clip.h * transform.scale.y) // render height
            };

            SDL_RenderCopyEx(
                m_renderer, // The SDL backend renderer for this SDL instance.
                (*i).texture()->texture, // TODO: remove extra dereference, store SDL_Texture directly in SDLRenderObj!
                &clip, // source rect
                &render_rect, // destination rect
                transform.rotation, // rotation for destination rect in degrees
                &pivot, // rotation pivot location in local space
                (*i).getFlip() // current flip status
            );
        }
    }

    // Update screen
    SDL_RenderPresent(m_renderer);
}

Diamond::Vector2<int> Diamond::SDLRenderer2D::getScreenResolution() const {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return Vector2<int>(mode.w, mode.h);
}

Diamond::Vector2<int> Diamond::SDLRenderer2D::getResolution() const {
    Vector2<int> r;
    SDL_GL_GetDrawableSize(m_window, &(r.x), &(r.y));
    return r;
}

Diamond::SharedPtr<Diamond::Texture> Diamond::SDLRenderer2D::loadTexture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        // TODO: Handle image loading failure
        Log::log("Failed to load image " + path + "! SDL_image Error: " + std::string(IMG_GetError()));
        return nullptr;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (texture == NULL) {
        // TODO: Handle texture creation failure
        Log::log("Failed to create texture from " + path + "! SDL Error: " + std::string(SDL_GetError()));
        return nullptr;
    }
    int width = surface->w;
    int height = surface->h;
    
    SDL_FreeSurface(surface);
    return makeShared<SDLTexture>(texture, width, height);
}

Diamond::SharedPtr<Diamond::RenderComponent2D> Diamond::SDLRenderer2D::makeRenderComponent(
    const DTransform2 &transform,
    const SharedPtr<const Texture> &texture,
    uint8_t layer,
    const Vector2<tD_pos> &pivot
    ) {
    // Make room for a new layer if necessary
    if ((int)layer > (int)m_render_objects.size() - 1) {
        m_render_objects.resize(layer + 1);
    }
    
    SDLrenderobj_id robj = m_render_objects[layer].emplace(
        transform, std::dynamic_pointer_cast<const SDLTexture>(texture), pivot
    );

    return makeShared<SDLRenderComponent2D>(*this, robj, layer);
}

Diamond::SDLrenderobj_id Diamond::SDLRenderer2D::changeLayer(uint8_t curLayer,
                                                             SDLrenderobj_id robj,
                                                             uint8_t newLayer) {
    // Make room for a new layer if necessary
    if (newLayer > m_render_objects.size() - 1) {
        m_render_objects.resize(newLayer + 1);
    }
    
    SDLrenderobj_id newID =
        m_render_objects[newLayer].insert(std::move(m_render_objects[curLayer][robj]));
    m_render_objects[curLayer].erase(robj);
    
    return newID;
}
