/*
 Copyright (c) 2015 Polymer Games
*/

#include "Graphics.h"

std::unique_ptr<Diamond::Renderer> Diamond::Graphics::renderer = nullptr;

Diamond::SoftSprite *Diamond::Graphics::gen_soft_sprite(std::string img) {
	return Graphics::renderer->gen_soft_sprite(img);
}

void Diamond::Graphics::setRenderer(Renderer *renderer) {
	Graphics::renderer = std::unique_ptr<Renderer>(renderer);
}
