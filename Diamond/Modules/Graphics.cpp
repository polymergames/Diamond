/*
 Copyright (c) 2015 Polymer Games
 */

#include "Graphics.h"

std::unique_ptr<Graphics> Graphics::graphics;

void Graphics::setGraphics(std::unique_ptr<Graphics> graphics) {
	Graphics::graphics = std::move(graphics);
}
