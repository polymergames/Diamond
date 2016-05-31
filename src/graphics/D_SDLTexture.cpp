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

#include "D_SDLTexture.h"

Diamond::SDLTexture::SDLTexture(SDL_Texture *texture, int width, int height) 
    : texture(texture), width(width), height(height), color({ 255, 255, 255, 255 }) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

Diamond::SDLTexture::~SDLTexture() {
    SDL_DestroyTexture(texture);
}

void Diamond::SDLTexture::setColor(Diamond::RGBA color) {
    this->color = color;
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture, color.a);
}
