/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_GameObject2D.h"

#include "D_Graphics2D.h"
#include "D_Launcher.h"
#include "D_RenderObj2D.h"

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite) : sprite(sprite), render_obj(nullptr), visible(true) {
	Graphics2D::gen_render_obj(this, sprite.get());
}

// TODO: test
Diamond::GameObject2D::GameObject2D(const GameObject2D &other) : sprite(other.sprite), render_obj(nullptr), visible(other.visible) {
	Graphics2D::gen_render_obj(this, sprite.get());
	if (!visible) {
		Graphics2D::deactivate_render_obj(render_obj->index);
	}
	
	render_obj->transform = other.render_obj->transform;
	if (other.is_flipped_x())	flip_x();
	if (other.is_flipped_y())	flip_y();
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
		visible = other.visible;
		Graphics2D::gen_render_obj(this, sprite.get());
		if (!visible) {
			Graphics2D::deactivate_render_obj(render_obj->index);
		}
		
		render_obj->transform = other.render_obj->transform;
		if (other.is_flipped_x())	flip_x();
		if (other.is_flipped_y())	flip_y();
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
	render_obj->set_texture(sprite.get());
}

Diamond::Transform2 Diamond::GameObject2D::get_transform() const {
	return render_obj->transform;
}

void Diamond::GameObject2D::set_transform(Diamond::Transform2 &transform) {
	render_obj->transform = transform;
}

void Diamond::GameObject2D::set_transform(Diamond::Vector2 &position) {
	render_obj->transform.position = position;
}

void Diamond::GameObject2D::set_transform(float x, float y, float rotation, float scale) {
	render_obj->transform.position.x = x;
	render_obj->transform.position.y = y;
	render_obj->transform.rotation = rotation;
	render_obj->transform.scale = scale;
}

void Diamond::GameObject2D::set_transform(float x, float y) {
	render_obj->transform.position.x = x;
	render_obj->transform.position.y = y;
}

void Diamond::GameObject2D::set_rotation(float rotation) {
	render_obj->transform.rotation = rotation;
}

void Diamond::GameObject2D::set_scale(float scale) {
	render_obj->transform.scale = scale;
}

void Diamond::GameObject2D::flip_x() {
	render_obj->flip_x();
}

void Diamond::GameObject2D::flip_y() {
	render_obj->flip_y();
}

int Diamond::GameObject2D::is_flipped_x() const {
	return render_obj->is_flipped_x();
}

int Diamond::GameObject2D::is_flipped_y() const {
	return render_obj->is_flipped_y();
}

bool Diamond::GameObject2D::is_visible() const {
	return visible;
}

void Diamond::GameObject2D::make_visible() {
	if (!visible) {
		Graphics2D::activate_render_obj(render_obj->index);
		visible = true;
	}
}

void Diamond::GameObject2D::make_invisible() {
	if (visible) {
		Graphics2D::deactivate_render_obj(render_obj->index);
		visible = false;
	}
}

void Diamond::GameObject2D::toggle_visibility() {
	visible ? make_invisible() : make_visible();
}

void Diamond::GameObject2D::re_adopt_render_obj() {
	render_obj->parent = this;
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
