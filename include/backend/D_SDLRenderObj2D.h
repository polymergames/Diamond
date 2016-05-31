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

#ifndef D_SDL_RENDER_OBJ_2D_H
#define D_SDL_RENDER_OBJ_2D_H

#include "SDL.h"

#include "duVector2.h"
#include "D_SDLTexture.h"
#include "D_SDLtypedefs.h"

namespace Diamond {
    class SDLRenderObj2D {
    public:
        SDLRenderObj2D(transform2_id transform,
                       const SharedPtr<const SDLTexture> &texture,
                       const Vector2<tSDLrender_pos> &pivot)
            : m_transform(transform), m_texture(texture), m_flip(SDL_FLIP_NONE) {
            m_pivot.x = pivot.x;
            m_pivot.y = pivot.y;
            m_clip.x = 0;
            m_clip.y = 0;
            m_clip.w = m_texture->getWidth();
            m_clip.h = m_texture->getHeight();
        }


        transform2_id getTransformID() const { return m_transform; }

        SDL_Point &pivot() { return m_pivot; }
        const SDL_Point &pivot() const { return m_pivot; }
        
        SharedPtr<const SDLTexture> &texture() { return m_texture; }
        const SharedPtr<const SDLTexture> &texture() const { return m_texture; }


        SDL_RendererFlip getFlip() const { return m_flip; }
        void flipX() { m_flip = (SDL_RendererFlip)(m_flip ^ SDL_FLIP_HORIZONTAL); }
        void flipY() { m_flip = (SDL_RendererFlip)(m_flip ^ SDL_FLIP_VERTICAL); }

        int isFlippedX() const { return m_flip & SDL_FLIP_HORIZONTAL; }
        int isFlippedY() const { return m_flip & SDL_FLIP_VERTICAL; }


        SDL_Rect &clip() { return m_clip; }
        const SDL_Rect &clip() const { return m_clip; }

    private:
        transform2_id m_transform;
        SDL_Point m_pivot;
        SharedPtr<const SDLTexture> m_texture;
        SDL_Rect m_clip;
        SDL_RendererFlip m_flip;
    };
}

#endif // D_SDL_RENDER_OBJ_2D_H
