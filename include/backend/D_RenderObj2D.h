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

#ifndef D_RENDER_OBJ_2D_H
#define D_RENDER_OBJ_2D_H

#include "D_Texture.h"
#include "D_Vector2.h"
#include "D_typedefs.h"

namespace Diamond {
    class RenderObj2D {
    public:
        virtual ~RenderObj2D() {}

        virtual void setTexture(const Texture *texture) = 0;
        
        virtual void flipX() = 0;
        virtual void flipY() = 0;

        virtual int isFlippedX() const = 0;
        virtual int isFlippedY() const = 0;
        
        virtual Vector2<tDrender_pos> getPivot() const = 0;
        virtual void setPivot(const Vector2<tDrender_pos> &newpivot) = 0;
        
        virtual void setClip(int x, int y, int w, int h) = 0;
        virtual void setClip(int x, int y) = 0;

        /**
         Stores the clip dimensions in dim.
        */
        virtual void getClipDim(Vector2<int> &dim) const = 0;
    };
}

#endif // D_RENDER_OBJ_2D_H
