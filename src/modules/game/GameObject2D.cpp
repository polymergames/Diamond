/*
 Copyright (c) 2015 Polymer Games
*/

#include "GameObject2D.h"
#include "Graphics2D.h"
#include "RenderObj2D.h"

Diamond::GameObject2D::GameObject2D() : sprite(nullptr), transform(nullptr), render_obj(nullptr), visible(false) {}

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite, Transform2 &transform) : sprite(sprite), visible(true) {
	Graphics2D::gen_render_obj(this, sprite.get(), transform);
}

std::shared_ptr<Diamond::Texture> Diamond::GameObject2D::get_sprite() {
	return sprite;
}

void Diamond::GameObject2D::set_sprite(std::shared_ptr<Texture> sprite) {
	this->sprite = sprite;
	if (render_obj != nullptr)	render_obj->set_texture(sprite.get());
}

bool Diamond::GameObject2D::is_visible() {
	return visible;
}

bool Diamond::GameObject2D::make_visible(Transform2 &transform) {
	if (sprite != nullptr) {
		this->visible = true;
		if (render_obj == nullptr) {
			Graphics2D::gen_render_obj(this, sprite.get(), transform);
		}
		return true;
	}
	return false;
}

void Diamond::GameObject2D::make_invisible() {
	// TODO: delete/clean up this game object's render object
}

void Diamond::GameObject2D::set_render_obj(RenderObj2D *render_obj) {
	this->render_obj = render_obj;
}

Diamond::GameObject2D::~GameObject2D() {
	// TODO: delete/clean up this game object's render object
}
