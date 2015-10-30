/*
 Copyright (c) 2015 Polymer Games
*/

#include "GameObject2D.h"
#include "Graphics2D.h"
#include "Launcher.h"
#include "RenderObj2D.h"

Diamond::GameObject2D::GameObject2D() : sprite(nullptr), render_obj(nullptr), visible(false) {}

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite) : sprite(sprite), render_obj(nullptr), visible(true) {
	Graphics2D::gen_render_obj(this, sprite.get());
}

std::shared_ptr<Diamond::Texture> Diamond::GameObject2D::get_sprite() {
	return sprite;
}

void Diamond::GameObject2D::set_sprite(std::shared_ptr<Texture> sprite) {
	this->sprite = sprite;
	if (render_obj != nullptr)	render_obj->set_texture(sprite.get());
	else    Graphics2D::gen_render_obj(this, sprite.get());
}

Diamond::Transform2 Diamond::GameObject2D::get_transform() {
	return render_obj != nullptr ? render_obj->transform : Transform2();
}

void Diamond::GameObject2D::set_transform(Diamond::Transform2 &transform) {
	if (render_obj != nullptr)	render_obj->transform = transform;
}

void Diamond::GameObject2D::set_transform(Diamond::Vector2 &position) {
	if (render_obj != nullptr) {
		render_obj->transform.position = position;
	}
}

void Diamond::GameObject2D::set_transform(float x, float y, float rotation, float scale) {
	if (render_obj != nullptr) {
		render_obj->transform.position.x = x;
		render_obj->transform.position.y = y;
		render_obj->transform.rotation = rotation;
		render_obj->transform.scale = scale;
	}
}

void Diamond::GameObject2D::set_transform(float x, float y) {
	if (render_obj != nullptr) {
		render_obj->transform.position.x = x;
		render_obj->transform.position.y = y;
	}
}

void Diamond::GameObject2D::set_rotation(float rotation) {
	if (render_obj != nullptr) {
		render_obj->transform.rotation = rotation;
	}
}

void Diamond::GameObject2D::set_scale(float scale) {
	if (render_obj != nullptr) {
		render_obj->transform.scale = scale;
	}
}

void Diamond::GameObject2D::flip_x() {
	if (render_obj != nullptr)	render_obj->flip_x();
}

void Diamond::GameObject2D::flip_y() {
	if (render_obj != nullptr)	render_obj->flip_y();
}

bool Diamond::GameObject2D::is_flipped_x() {
	if (render_obj != nullptr)	return render_obj->is_flipped_x();
	return false;
}

bool Diamond::GameObject2D::is_flipped_y() {
	if (render_obj != nullptr)	return render_obj->is_flipped_y();
	return false;
}

bool Diamond::GameObject2D::is_visible() {
	return visible;
}

bool Diamond::GameObject2D::make_visible() {
	if (render_obj != nullptr) {
		visible = true;
		Graphics2D::activate_render_obj(render_obj->index);
		return true;
	}
	return false;
}

void Diamond::GameObject2D::make_invisible() {
	visible = false;
	if (render_obj != nullptr) {
		Graphics2D::deactivate_render_obj(render_obj->index);
	}
}

bool Diamond::GameObject2D::toggle_visibility() {
	if (visible) {
		make_invisible();
		return true;
	}
	else {
		return make_visible();
	}
}

void Diamond::GameObject2D::re_adopt_render_obj() {
	render_obj->parent = this;
}

void Diamond::GameObject2D::set_render_obj(RenderObj2D *render_obj) {
	this->render_obj = render_obj;
}

Diamond::GameObject2D::~GameObject2D() {
	if (Launcher::is_open && render_obj != nullptr) { // TODO: find exception-safer method of memory management. ie it's possible that render_obj has been destroyed/game has ended/crashed even if is_open = true
		Graphics2D::destroy_render_obj(render_obj->index);
	}
}
