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

Diamond::SDLRenderObj2D::SDLRenderObj2D(renderobj_id obj_id, Texture *texture, transform2_id transform, float scale)
: RenderObj2D(obj_id, transform), flip(SDL_FLIP_NONE), clip(NULL) {
	setTexture(texture, scale);
}

Diamond::SDLRenderObj2D::~SDLRenderObj2D() {
	if (clip)	delete clip;
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
		size.x = texture->width * scale;
		size.y = texture->height * scale;
	}
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

void Diamond::SDLRenderObj2D::initClip() {
	if (!clip)	clip = new SDL_Rect;
	clip->x = 0;
	clip->y = 0;
	clip->w = texture->width;
	clip->h = texture->height;
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
	if (!clip)	return false;
	dim.x = clip->w;
	dim.y = clip->h;
	return true;
}
