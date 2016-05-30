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
#include "D_Log.h"
#include "SDL_image.h"
#include "D_SDLTexture.h"


Diamond::SDLRenderer2D::SDLRenderer2D(const TransformList &transform_list) 
    : m_window(nullptr), m_renderer(nullptr), m_transform_list(transform_list) {}

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
    for (std::vector<SDLRenderObj2D>::iterator i = m_render_objects.begin(); i != m_render_objects.end(); ++i) {
        //Log::log(i->transform.position.x + " and " + i->transform.position.y + " and " + i->transform.scale); // DEBUG
        const Transform2<tDrender_pos, tDrender_rot> &transform = m_transform_list[(*i).getTransformID()];

        SDL_Point pivot = (*i).getSDLPivot();

        SDL_Rect clip = (*i).getClip();

        SDL_Rect render_rect = { 
            transform.position.x - pivot.x, // render position x
            transform.position.y - pivot.y, // render position y
            clip.w * transform.scale.x, // render width
            clip.h * transform.scale.y // render height
        };

        SDL_RenderCopyEx(
            m_renderer, // The SDL backend renderer for this SDL instance.
            (*i).getTexture()->texture, // TODO: remove extra dereference, store SDL_Texture directly in SDLRenderObj!
            &clip, // source rect
            &render_rect, // destination rect
            transform.rotation, // rotation for destination rect in degrees
            &pivot, // rotation pivot location in local space
            (*i).getFlip() // current flip status
        );
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

Diamond::RenderObj2D *Diamond::SDLRenderer2D::getRenderObj(renderobj_id render_obj) {
    return &m_render_objects[render_obj];
}

renderobj_id Diamond::SDLRenderer2D::genRenderObj(transform2_id trans,
                                                  const SharedPtr<const Texture> &texture,
                                                  const Vector2<tDrender_pos> &pivot) {
    return m_render_objects.emplace_back(trans, texture.get(), pivot);
}

void Diamond::SDLRenderer2D::freeRenderObj(renderobj_id render_obj) {
    m_render_objects.erase(render_obj);
}

Diamond::SDLRenderer2D::~SDLRenderer2D() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    
    IMG_Quit();
    SDL_Quit();
}
