/*
 Copyright (c) 2015 Polymer Games
*/

#include "Graphics.h"
#include "Launcher.h"
#include "Renderer.h"

std::unique_ptr<Diamond::Renderer> Diamond::Graphics::renderer = nullptr;

void Diamond::Graphics::setRenderer(Renderer *renderer) {
	Graphics::renderer = std::unique_ptr<Renderer>(renderer);
}

bool Diamond::Graphics::init_renderer(Config &config) {
	return renderer->init(config);
}

void Diamond::Graphics::render() {
	renderer->render();
}
