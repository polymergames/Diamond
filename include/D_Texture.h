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

#ifndef D_TEXTURE_H
#define D_TEXTURE_H

#include "D_Config.h"

namespace Diamond {
    class Texture {
    public:
        Texture(int16_t width, int16_t height);
        virtual ~Texture();

        int16_t getWidth() const {
            return width;
        }

        int16_t getHeight() const {
            return height;
        }
        
        virtual RGBA getColor() const;

        virtual void setColor(RGBA color);
        
    protected:
        int16_t width, height;
        RGBA color;
    };
}

#endif // D_TEXTURE_H
