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

#ifndef D_SDL_RENDERER_2D_H
#define D_SDL_RENDERER_2D_H

#include <vector>
#include "SDL.h"

#include "D_Renderer2D.h"
#include "D_SDLtypedefs.h"


namespace Diamond {
    class SDLRenderer2D : public Renderer2D {
    public:
        SDLRenderer2D();
        
        /**
         Destroys window and renderer and shuts down SDL and SDL extensions.
        */
        ~SDLRenderer2D();

        /**
         Initializes SDL, creates window, and initializes image loading.
         Returns whether all of the initialization was successful.
        */
        bool init(const Config &config) override;
        
        void renderAll() override;
        
        Vector2<int> getResolution() const override;

        Diamond::Vector2<int> getScreenResolution() const override;
        
        SharedPtr<Texture> loadTexture(std::string path) override;
        
        SharedPtr<RenderComponent2D> makeRenderComponent(
            const DTransform2 &transform,
            const SharedPtr<const Texture> &texture,
            const Vector2<tD_pos> &pivot
        ) override;

    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        SDLRenderObjList m_render_objects;
    };
}

#endif // D_SDL_RENDERER_2D_H
