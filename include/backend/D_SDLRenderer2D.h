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
#include "SDL_ttf.h"
#include "duPoolManager.h"
#include "D_Renderer2D.h"
#include "D_SDLtypedefs.h"
#include "SDLRenderObjectPool.h"
#include "D_SDLRenderComponent2D.h"

namespace Diamond {
    struct SDLRenderablePoint {
        Vector2<int> coords;
        RGBA color;
    };

    struct SDLRenderableLine {
        Vector2<int> p1;
        Vector2<int> p2;
        RGBA color;
    };

    class SDLFont : public Font {
    public:
        SDLFont(TTF_Font *font) : font(font) {}

        ~SDLFont() {
            TTF_CloseFont(font);
        }

        TTF_Font *font;
    };

    class SDLRenderer2D : public Renderer2D {
    public:
        /**
         Initializes SDL, creates window, and initializes image loading.
         Success indicates whether all of the initialization was successful.
         */
        SDLRenderer2D(const Config &config, bool &success);

        /**
         Destroys window and renderer and shuts down SDL and SDL extensions.
        */
        ~SDLRenderer2D();

        void renderAll() override;

        Vector2<int> getResolution() const override;

        Diamond::Vector2<int> getScreenResolution() const override;
        
        int getRefreshRate() const override;

        DumbPtr<Font> loadFont(const std::string &fontPath, int ptsize) override;

        DumbPtr<Texture> loadTexture(std::string path) override;

        DumbPtr<Texture> loadTextTexture(const std::string &text,
                                         const Font *font,
                                         const RGBA &color) override;

        DumbPtr<RenderComponent2D> makeRenderComponent(
            const DTransform2 &transform,
            const Texture *texture,
            RenderLayer layer = 0,
            const Vector2<tD_pos> &pivot = Vector2<tD_pos>(0, 0)
        ) override;


        void renderPoint(const Vector2<tD_pos> &coords,
                         const RGBA &color) override;

        void renderLine(const Vector2<tD_pos> &p1,
                        const Vector2<tD_pos> &p2,
                        const RGBA &color) override;


      

    private:
        SDL_Window   *m_window;
        SDL_Renderer *m_renderer;

        RGBA          m_bgColor;

		SDLRenderObjectPool m_render_objects;

        std::vector<SDLRenderablePoint>          m_render_points_queue;
        std::vector<SDLRenderableLine>           m_render_lines_queue;

        DumbPoolManager<SDLRenderComponent2D>    m_renderCompPool;
    };
}

#endif // D_SDL_RENDERER_2D_H
