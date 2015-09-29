/*
 Copyright (c) 2015 Polymer Games
*/

#include "Graphics.h"
using namespace Diamond;

std::unique_ptr<Renderer> Diamond::Graphics::renderer = nullptr;

void Diamond::Graphics::setRenderer(Renderer *renderer) {
	Diamond::Graphics::renderer = std::unique_ptr<Renderer>(renderer);
}
