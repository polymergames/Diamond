/*
 Copyright (c) 2015 Polymer Games
*/

#include "GameObject2D.h"
#include "Graphics2D.h"
#include "Launcher.h"
#include "RenderObj2D.h"

Diamond::GameObject2D::GameObject2D() : sprite(nullptr), transform(nullptr), render_obj(nullptr), visible(false) {}

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite) : sprite(sprite), transform(nullptr), render_obj(nullptr), visible(true) {
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
	this->transform = &(render_obj->transform);
}

Diamond::GameObject2D::~GameObject2D() {
	if (Launcher::is_open && render_obj != nullptr) {
		Graphics2D::destroy_render_obj(render_obj->index);
	}
}
