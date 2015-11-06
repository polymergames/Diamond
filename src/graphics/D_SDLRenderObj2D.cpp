/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLRenderObj2D.h"

#include "D_GameObject2D.h"
#include "D_SDLTexture.h"

Diamond::SDLRenderObj2D::SDLRenderObj2D(GameObject2D *parent, Texture *texture) : RenderObj2D(parent), flip(SDL_FLIP_NONE) {
	setTexture(texture);
}

void Diamond::SDLRenderObj2D::setTexture(Texture *texture) {
	this->texture = dynamic_cast<SDLTexture*>(texture);
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

void Diamond::SDLRenderObj2D::render(SDL_Renderer *renderer) {
	SDL_Rect render_rect = {(int)transform.position.x, (int)transform.position.y,
		(int)(texture->width * transform.scale), (int)(texture->height * transform.scale)};
	SDL_RenderCopyEx(renderer, texture->texture, NULL, &render_rect, transform.rotation, NULL, flip);
}

void Diamond::SDLRenderObj2D::armParent() {
	parent->setRenderObj(this);
}
