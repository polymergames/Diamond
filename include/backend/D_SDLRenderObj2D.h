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
#include "D_Entity2D.h"

namespace Diamond {
    class SDLTexture;
    
    class SDLRenderObj2D : public RenderObj2D {
    public:
        SDLRenderObj2D(Entity2D *parent, 
                       Texture *texture,  
                       float scale);
        ~SDLRenderObj2D();

        SDLRenderObj2D(const SDLRenderObj2D &other);
        SDLRenderObj2D(SDLRenderObj2D &&other);

        SDLRenderObj2D &operator=(const SDLRenderObj2D &other);
        SDLRenderObj2D &operator=(SDLRenderObj2D &&other);

        Transform2<tDrender_pos, tDrender_rot> getTransform() const {
            Transform2<tDrender_pos, tDrender_pos> trans = parent->getTransform();
            trans.position.x -= pivot.x;
            trans.position.y -= pivot.y;
            return trans;
        };
        
        SDLTexture *getTexture() const { return texture; }
        SDL_RendererFlip getFlip() const { return flip; }
        const Vector2<tDrender_pos> getSize() const { return size; }
        const SDL_Rect *getClip() const { return clip; }

        void setTexture(Texture *texture, float scale) override;
        void applyScale(float scale) override;

        void flipX() override { flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_HORIZONTAL); }
        void flipY() override { flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_VERTICAL); }

        int isFlippedX() const override { return flip & SDL_FLIP_HORIZONTAL; }
        int isFlippedY() const override { return flip & SDL_FLIP_VERTICAL; }

        Vector2<tDrender_pos> getPivot() const override { return Vector2<tDrender_pos>(pivot.x, pivot.y); }
        void setPivot(const Vector2<tDrender_pos> &newpivot) override { pivot.x = newpivot.x; pivot.y = newpivot.y; }
        const SDL_Point getSDLPivot() const { return pivot; }
        
        void initClip() override;

        void setClip(int x, int y, int w, int h) override;
        void setClip(int x, int y) override;

        bool getClipDim(Vector2<int> &dim) const override;

    private:
        Entity2D *parent;
        Vector2<tDrender_pos> size;
        SDLTexture *texture;
        SDL_Rect *clip;
        SDL_Point pivot;
        SDL_RendererFlip flip;
    };
}

#endif // D_SDL_RENDER_OBJ_2D_H
