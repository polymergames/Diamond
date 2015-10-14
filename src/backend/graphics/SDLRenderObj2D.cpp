/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderObj2D.h"
#include "SDLTexture.h"

Diamond::SDLRenderObj2D::SDLRenderObj2D(GameObject2D *parent, Texture *texture) : RenderObj2D(parent) {
	set_texture(texture);
	arm_parent();
}

void Diamond::SDLRenderObj2D::set_texture(Texture *texture) {
	this->texture = dynamic_cast<SDLTexture*>(texture);
}

void Diamond::SDLRenderObj2D::render(SDL_Renderer *renderer) {
    SDL_Rect render_rect = {(int)transform.position.x, (int)transform.position.y,
        (int)(texture->get_width() * transform.scale), (int)(texture->get_height() * transform.scale)};
    SDL_RenderCopy(renderer, texture->texture, NULL, &render_rect);
}

void Diamond::SDLRenderObj2D::arm_parent() {
	parent->set_render_obj(this);
	parent->transform = &transform;
}
