/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Graphics2D.h"

#include <memory>

#include "D_Renderer2D.h"

namespace Diamond {
	namespace Graphics2D {
		static std::unique_ptr<Diamond::Renderer2D> renderer = nullptr;
	}
}

Diamond::Texture *Diamond::Graphics2D::loadTexture(std::string path) {
	return renderer->loadTexture(path);
}

bool Diamond::Graphics2D::initRenderer(Renderer2D *renderer) {
	if (Graphics2D::renderer == nullptr && renderer != nullptr) {
		Graphics2D::renderer = std::unique_ptr<Renderer2D>(renderer);
		return renderer->init();
	}
	return false;
}

void Diamond::Graphics2D::render() {
	renderer->render();
}

void Diamond::Graphics2D::genRenderObj(GameObject2D *parent, Texture *texture) {
	renderer->genRenderObj(parent, texture);
}

void Diamond::Graphics2D::activateRenderObj(unsigned long index) {
	renderer->activateRenderObj(index);
}

void Diamond::Graphics2D::deactivateRenderObj(unsigned long index) {
	renderer->deactivateRenderObj(index);
}

void Diamond::Graphics2D::destroyRenderObj(unsigned long index) {
	renderer->destroyRenderObj(index);
}

void Diamond::Graphics2D::destroyInactiveRenderObj(unsigned long index) {
	renderer->destroyInactiveRenderObj(index);
}
