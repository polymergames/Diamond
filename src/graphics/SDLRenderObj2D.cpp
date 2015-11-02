/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderObj2D.h"

#include "SDLTexture.h"

Diamond::SDLRenderObj2D::SDLRenderObj2D(GameObject2D *parent, Texture *texture) : RenderObj2D(parent), flip(SDL_FLIP_NONE) {
	set_texture(texture);
}

void Diamond::SDLRenderObj2D::set_texture(Texture *texture) {
	this->texture = dynamic_cast<SDLTexture*>(texture);
}

void Diamond::SDLRenderObj2D::flip_x() {
	flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_HORIZONTAL);
}

void Diamond::SDLRenderObj2D::flip_y() {
	flip = (SDL_RendererFlip)(flip ^ SDL_FLIP_VERTICAL);
}

int Diamond::SDLRenderObj2D::is_flipped_x() {
	return flip & SDL_FLIP_HORIZONTAL;
}

int Diamond::SDLRenderObj2D::is_flipped_y() {
	return flip & SDL_FLIP_VERTICAL;
}

void Diamond::SDLRenderObj2D::render(SDL_Renderer *renderer) {
	SDL_Rect render_rect = {(int)transform.position.x, (int)transform.position.y,
		(int)(texture->width * transform.scale), (int)(texture->height * transform.scale)};
	SDL_RenderCopyEx(renderer, texture->texture, NULL, &render_rect, transform.rotation, NULL, flip);
}

void Diamond::SDLRenderObj2D::arm_parent() {
	parent->set_render_obj(this);
}
