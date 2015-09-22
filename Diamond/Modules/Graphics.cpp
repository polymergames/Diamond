/*
 Copyright (c) 2015 Polymer Games
*/

#include "Graphics.h"

std::unique_ptr<Renderer> Graphics::renderer = nullptr;

void Graphics::setRenderer(std::unique_ptr<Renderer> renderer) {
	Graphics::renderer = std::move(renderer);
}
