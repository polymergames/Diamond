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
	this->texture = dynamic_cast<SDLTexture*>(texture)->texture;
}

void Diamond::SDLRenderObj2D::arm_parent() {
	parent->set_render_obj(this);
	parent->transform = &transform;
}
