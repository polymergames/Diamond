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

#include "D_GameObject2D.h"
#include "D_SDLTexture.h"

Diamond::SDLRenderObj2D::SDLRenderObj2D(renderobj_id obj_id, Texture *texture, transform2_id transform, float scale)
: RenderObj2D(obj_id, transform), flip(SDL_FLIP_NONE) {
	setTexture(texture, scale);
}

void Diamond::SDLRenderObj2D::setTexture(Texture *texture, float scale) {
	this->texture = dynamic_cast<SDLTexture*>(texture);
	applyScale(scale);
}

void Diamond::SDLRenderObj2D::applyScale(float scale) {
	size.x = texture->width * scale;
	size.y = texture->height * scale;
}

void Diamond::SDLRenderObj2D::flipX() {
	flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_HORIZONTAL);
}

void Diamond::SDLRenderObj2D::flipY() {
	flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_VERTICAL);
}

int Diamond::SDLRenderObj2D::isFlippedX() const {
	return flip & SDL_FLIP_HORIZONTAL;
}

int Diamond::SDLRenderObj2D::isFlippedY() const {
	return flip & SDL_FLIP_VERTICAL;
}
