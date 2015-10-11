/*
 Copyright (c) 2015 Polymer Games
*/

#include "GameObject2D.h"

Diamond::GameObject2D::GameObject2D() : sprite(nullptr), transform() {}

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite, Transform2 transform) : sprite(sprite), transform(transform) {}
