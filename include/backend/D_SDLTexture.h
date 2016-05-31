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

#ifndef D_SDL_TEXTURE_H
#define D_SDL_TEXTURE_H

#include "SDL.h"

#include "D_Texture.h"

namespace Diamond {
    class SDLTexture : public Texture {
    public:
        SDL_Texture *texture;

        SDLTexture(SDL_Texture *texture, int width, int height);
        ~SDLTexture();

        int getWidth() const { return width; }

        int getHeight() const { return height; }

        RGBA getColor() const { return color; }

        void setColor(RGBA color);

    private:
        int16_t width, height;
        RGBA color;
    };
}

#endif // D_SDL_TEXTURE_H
