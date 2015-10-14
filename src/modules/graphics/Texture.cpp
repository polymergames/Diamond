/*
 Copyright (c) 2015 Polymer Games
*/

#include "Texture.h"

Diamond::Texture::Texture(int width, int height) : width(width), height(height) {}

int Diamond::Texture::get_width() {
    return width;
}

int Diamond::Texture::get_height() {
    return height;
}

Diamond::Texture::~Texture() {}