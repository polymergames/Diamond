/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Texture.h"

Diamond::Texture::Texture(int width, int height) : width(width), height(height), color({255, 255, 255, 255}) {}

Diamond::RGBA Diamond::Texture::get_color() const {
	return color;
}

void Diamond::Texture::set_color(RGBA color) {
	this->color = color;
}

Diamond::Texture::~Texture() {}
