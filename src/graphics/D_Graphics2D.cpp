/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Graphics2D.h"

std::unique_ptr<Diamond::Renderer2D> Diamond::Graphics2D::renderer = nullptr;

Diamond::Texture *Diamond::Graphics2D::load_texture(std::string path) {
	return renderer->load_texture(path);
}

void Diamond::Graphics2D::set_renderer(Renderer2D *renderer) {
	Graphics2D::renderer = std::unique_ptr<Renderer2D>(renderer);
}

bool Diamond::Graphics2D::init_renderer() {
	if (renderer != nullptr)
		return renderer->init();
	return false;
}

void Diamond::Graphics2D::render() {
	renderer->render();
}

void Diamond::Graphics2D::gen_render_obj(GameObject2D *parent, Texture *texture) {
	renderer->gen_render_obj(parent, texture);
}

void Diamond::Graphics2D::activate_render_obj(unsigned long index) {
	renderer->activate_render_obj(index);
}

void Diamond::Graphics2D::deactivate_render_obj(unsigned long index) {
	renderer->deactivate_render_obj(index);
}

void Diamond::Graphics2D::destroy_render_obj(unsigned long index) {
	renderer->destroy_render_obj(index);
}
