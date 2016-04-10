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
#include "D_SDLTexture.h"

namespace Diamond {
    namespace SDLRenderSpace {
        static inline void render(Diamond::SDLRenderObj2D &obj, SDL_Renderer *renderer) {
            Diamond::Transform2<tDrender_pos, tDrender_rot> transform = obj.getTransform();
            Vector2<tDrender_pos> size = obj.getSize();
            SDL_Rect render_rect = {transform.position.x, transform.position.y, size.x, size.y};
            SDL_RenderCopyEx(renderer, 
                             obj.getTexture()->texture, 
                             obj.getClip(), // source rect
                             &render_rect, // destination rect
                             transform.rotation, 
                             NULL, // TODO: rotation pivot
                             obj.getFlip());
        }
    }
}


Diamond::SDLRenderer2D::SDLRenderer2D() : window(nullptr), renderer(nullptr) {}

bool Diamond::SDLRenderer2D::init(const Config &config) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        // TODO: Handle initialization failure and log
        std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow(config.game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              config.window_width, config.window_height, 
                              config.fullscreen 
                              || config.window_width <= 0
                              || config.window_height <= 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    if (window == nullptr) {
        // TODO: Handle window creation failure and log
        std::cout << "SDL failed to create window! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | (config.vsync ? SDL_RENDERER_PRESENTVSYNC : 0x00000000));
    if (renderer == nullptr) {
        // TODO: Handle renderer creation failure and log
        std::cout << "SDL failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, config.bg_color.r, config.bg_color.g, config.bg_color.b, config.bg_color.a);

    // Initialize image loading
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(img_flags) != img_flags) {
        // TODO: Handle image-loader initialization failure and log
        std::cout << "SDL_image failed to initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void Diamond::SDLRenderer2D::renderAll() {
    // Render all the graphics
    SDL_RenderClear(renderer);
    for (std::vector<SDLRenderObj2D>::iterator i = render_objects.begin(); i != render_objects.end(); ++i) {
        //std::cout << i->transform.position.x << " and " << i->transform.position.y << " and " << i->transform.scale << std::endl; // DEBUG
        SDLRenderSpace::render(*i, renderer);
    }

    // Update screen
    SDL_RenderPresent(renderer);
}

Diamond::Vector2<int> Diamond::SDLRenderer2D::getScreenResolution() const {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return Vector2<int>(mode.w, mode.h);
}

Diamond::Vector2<int> Diamond::SDLRenderer2D::getResolution() const {
    Vector2<int> r;
    SDL_GL_GetDrawableSize(window, &(r.x), &(r.y));
    return r;
}

Diamond::Texture *Diamond::SDLRenderer2D::loadTexture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        // TODO: Handle image loading failure and log
        std::cout << "Failed to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        // TODO: Handle texture creation failure and log
        std::cout << "Failed to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    int width = surface->w;
    int height = surface->h;
    
    SDL_FreeSurface(surface);
    return new SDLTexture(texture, width, height);
}

Diamond::RenderObj2D *Diamond::SDLRenderer2D::getRenderObj(renderobj_id render_obj) {
    return &render_objects[render_obj];
}

renderobj_id Diamond::SDLRenderer2D::genRenderObj(Entity2D *parent, Texture *texture, float scale) {
    return render_objects.emplace_back(parent, texture, scale);
}

void Diamond::SDLRenderer2D::freeRenderObj(renderobj_id render_obj) {
    render_objects.erase(render_obj);
}

Diamond::SDLRenderer2D::~SDLRenderer2D() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    IMG_Quit();
    SDL_Quit();
}
