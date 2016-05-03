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

#include "D_RenderObj2D.h"
#include "D_SDLTexture.h"

namespace Diamond {
    class SDLRenderObj2D : public RenderObj2D {
    public:
        SDLRenderObj2D(transform2_id transform,
                       const Texture *texture,
                       float scale, 
                       const Vector2<tDrender_pos> &pivot);
        ~SDLRenderObj2D();

        SDLRenderObj2D(const SDLRenderObj2D &other);
        SDLRenderObj2D(SDLRenderObj2D &&other);

        SDLRenderObj2D &operator=(const SDLRenderObj2D &other);
        SDLRenderObj2D &operator=(SDLRenderObj2D &&other);

        transform2_id getTransformID() const { return transform; }

        Vector2<tDrender_pos> getPivot() const override { return Vector2<tDrender_pos>(pivot.x, pivot.y); }
        void setPivot(const Vector2<tDrender_pos> &newpivot) override { pivot.x = newpivot.x; pivot.y = newpivot.y; }
        const SDL_Point &getSDLPivot() const { return pivot; }
        
        const SDLTexture *getTexture() const { return texture; }
        SDL_RendererFlip getFlip() const { return flip; }
        const Vector2<tDrender_pos> getSize() const { return size; }
        const SDL_Rect *getClip() const { return clip; }

        void setTexture(const Texture *texture, float scale) override;
        void applyScale(float scale) override;

        void flipX() override { flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_HORIZONTAL); }
        void flipY() override { flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_VERTICAL); }

        int isFlippedX() const override { return flip & SDL_FLIP_HORIZONTAL; }
        int isFlippedY() const override { return flip & SDL_FLIP_VERTICAL; }
        
        void initClip() override;

        void setClip(int x, int y, int w, int h) override;
        void setClip(int x, int y) override;

        bool getClipDim(Vector2<int> &dim) const override;

    private:
        transform2_id transform;
        SDL_Point pivot;
        Vector2<tDrender_pos> size;
        const SDLTexture *texture;
        SDL_Rect *clip;
        SDL_RendererFlip flip;
    };
}

#endif // D_SDL_RENDER_OBJ_2D_H
