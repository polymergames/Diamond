/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_GameObject2D.h"

#include "D_Graphics2D.h"
#include "D_Launcher.h"
#include "D_RenderObj2D.h"

Diamond::GameObject2D::GameObject2D() : sprite(nullptr), render_obj(nullptr), visible(false) {}

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite) : sprite(sprite), render_obj(nullptr), visible(true) {
	Graphics2D::gen_render_obj(this, sprite.get());
}

// TODO: test
Diamond::GameObject2D::GameObject2D(const GameObject2D &other) : sprite(other.sprite), render_obj(nullptr) {
	if (sprite != nullptr) {
		visible = true;
		Graphics2D::gen_render_obj(this, sprite.get());
	}
	else {
		visible = false;
	}
}

// TODO: test
Diamond::GameObject2D::GameObject2D(GameObject2D &&other) : sprite(other.sprite), render_obj(other.render_obj), visible(other.visible) {
	re_adopt_render_obj();

	other.sprite = nullptr;
	other.render_obj = nullptr;
	other.visible = false;
}

// TODO: test
Diamond::GameObject2D &Diamond::GameObject2D::operator=(const GameObject2D &other) {
	if (this != &other) {
		destroy_render_obj();

		sprite = other.sprite;
		if (sprite != nullptr) {
			visible = true;
			Graphics2D::gen_render_obj(this, sprite.get());
		}
		else {
			visible = false;
		}
	}

	return *this;
}

// TODO: test
Diamond::GameObject2D &Diamond::GameObject2D::operator=(GameObject2D &&other) {
	if (this != &other) {
		destroy_render_obj();

		sprite = other.sprite;
		render_obj = other.render_obj;
		visible = other.visible;

		re_adopt_render_obj();

		other.sprite = nullptr;
		other.render_obj = nullptr;
		other.visible = false;
	}

	return *this;
}

std::shared_ptr<Diamond::Texture> Diamond::GameObject2D::get_sprite() const {
	return sprite;
}

void Diamond::GameObject2D::set_sprite(std::shared_ptr<Texture> sprite) {
	this->sprite = sprite;
	if (render_obj != nullptr)	render_obj->set_texture(sprite.get());
	else    Graphics2D::gen_render_obj(this, sprite.get());
}

Diamond::Transform2 Diamond::GameObject2D::get_transform() const {
	return render_obj != nullptr ? render_obj->transform : Transform2();
}

void Diamond::GameObject2D::set_transform(Diamond::Transform2 &transform) {
	if (render_obj != nullptr)	render_obj->transform = transform;
}

void Diamond::GameObject2D::set_transform(Diamond::Vector2 &position) {
	if (render_obj != nullptr)	render_obj->transform.position = position;
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
	if (render_obj != nullptr)	render_obj->transform.rotation = rotation;
}

void Diamond::GameObject2D::set_scale(float scale) {
	if (render_obj != nullptr)	render_obj->transform.scale = scale;
}

void Diamond::GameObject2D::flip_x() {
	if (render_obj != nullptr)	render_obj->flip_x();
}

void Diamond::GameObject2D::flip_y() {
	if (render_obj != nullptr)	render_obj->flip_y();
}

int Diamond::GameObject2D::is_flipped_x() const {
	if (render_obj != nullptr)	return render_obj->is_flipped_x();
	return false;
}

int Diamond::GameObject2D::is_flipped_y() const {
	if (render_obj != nullptr)	return render_obj->is_flipped_y();
	return false;
}

bool Diamond::GameObject2D::is_visible() const {
	return visible;
}

bool Diamond::GameObject2D::make_visible() {
	if (render_obj != nullptr) {
		if (visible) return true;
		Graphics2D::activate_render_obj(render_obj->index);
		return visible = true;
	}
	return visible = false;
}

void Diamond::GameObject2D::make_invisible() {
	if (visible) {
		visible = false;
		if (render_obj != nullptr) {
			Graphics2D::deactivate_render_obj(render_obj->index);
		}
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
	if(render_obj != nullptr)	render_obj->parent = this;
}

void Diamond::GameObject2D::set_render_obj(RenderObj2D *render_obj) {
	this->render_obj = render_obj;
}

void Diamond::GameObject2D::destroy_render_obj() {
	if (render_obj != nullptr) {
		if (visible) {
			Graphics2D::destroy_render_obj(render_obj->index);
		}
		else {
			Graphics2D::destroy_inactive_render_obj(render_obj->index);
		}
	}
	render_obj = nullptr;
}

Diamond::GameObject2D::~GameObject2D() {
	// TODO: find exception-safer method of memory management. ie it's possible that render_obj has been destroyed/game has ended/crashed even if is_open = true
	if (Launcher::is_open)	destroy_render_obj();
}
