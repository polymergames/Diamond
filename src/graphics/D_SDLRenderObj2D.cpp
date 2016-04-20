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

#include "D_SDLRenderObj2D.h"

#include "D_SDLTexture.h"

Diamond::SDLRenderObj2D::SDLRenderObj2D(Entity2D *parent, 
                                        Texture *texture, 
                                        float scale, 
                                        const Vector2<tDrender_pos> &pivot)
    : parent(parent), clip(nullptr), flip(SDL_FLIP_NONE) {
    setTexture(texture, scale);
    this->pivot.x = pivot.x;
    this->pivot.y = pivot.y;
}

Diamond::SDLRenderObj2D::~SDLRenderObj2D() {
    delete clip;
}

Diamond::SDLRenderObj2D::SDLRenderObj2D(const SDLRenderObj2D &other)
    : RenderObj2D(other), parent(other.parent), texture(other.texture), flip(other.flip), clip(nullptr), pivot(other.pivot) {
    if (other.clip) {
        clip = new SDL_Rect;
        *clip = *(other.clip);
    }

    size = other.size; // put this after clip copy for exception safety
}

Diamond::SDLRenderObj2D::SDLRenderObj2D(SDLRenderObj2D &&other)
    : RenderObj2D(other), 
      parent(other.parent), texture(other.texture), flip(other.flip), size(other.size), clip(other.clip), pivot(other.pivot) {
    other.texture = nullptr;
    other.clip = nullptr;
}

Diamond::SDLRenderObj2D &Diamond::SDLRenderObj2D::operator=(const SDLRenderObj2D &other) {
    RenderObj2D::operator=(other);
    if (this != &other) {
        parent = other.parent;
        texture = other.texture;
        flip = other.flip;
        size = other.size;
        pivot = other.pivot;

        if (other.clip) {
            if (!clip)   clip = new SDL_Rect;
            *clip = *(other.clip);
        }
        else
            clip = nullptr;
    }
    return *this;
}

Diamond::SDLRenderObj2D &Diamond::SDLRenderObj2D::operator=(SDLRenderObj2D &&other) {
    RenderObj2D::operator=(other);
    if (this != &other) {
        parent = other.parent;
        texture = other.texture;
        flip = other.flip;
        size = other.size;
        clip = other.clip;
        pivot = other.pivot;

        other.texture = nullptr;
        other.clip = nullptr;
    }
    return *this;
}

void Diamond::SDLRenderObj2D::setTexture(Texture *texture, float scale) {
    this->texture = dynamic_cast<SDLTexture*>(texture);
    applyScale(scale);
}

void Diamond::SDLRenderObj2D::applyScale(float scale) {
    if (clip) {
        size.x = clip->w * scale;
        size.y = clip->h * scale;
    }
    else {
        size.x = texture->getWidth() * scale;
        size.y = texture->getHeight() * scale;
    }
}

void Diamond::SDLRenderObj2D::initClip() {
    if (!clip)  clip = new SDL_Rect;
    clip->x = 0;
    clip->y = 0;
    clip->w = texture->getWidth();
    clip->h = texture->getHeight();
}

void Diamond::SDLRenderObj2D::setClip(int x, int y, int w, int h) {
    clip->x = x;
    clip->y = y;

    size.x *= (float)w / clip->w;
    size.y *= (float)h / clip->h;

    clip->w = w;
    clip->h = h;
}

void Diamond::SDLRenderObj2D::setClip(int x, int y) {
    clip->x = x;
    clip->y = y;
}

bool Diamond::SDLRenderObj2D::getClipDim(Vector2<int> &dim) const {
    if (!clip)  return false;
    dim.x = clip->w;
    dim.y = clip->h;
    return true;
}
