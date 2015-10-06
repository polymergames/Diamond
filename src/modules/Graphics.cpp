/*
 Copyright (c) 2015 Polymer Games
*/

#include "Graphics.h"

std::unique_ptr<Diamond::Renderer> Diamond::Graphics::renderer = nullptr;

void Diamond::Graphics::setRenderer(Renderer *renderer) {
	Graphics::renderer = std::unique_ptr<Renderer>(renderer);
}

void Diamond::Graphics::render() {
	renderer->render();
}
