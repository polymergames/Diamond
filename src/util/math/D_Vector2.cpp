/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Vector2.h"

using Diamond::Vector2;

Diamond::Vector2::Vector2() : x(0), y(0) {}

Diamond::Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 &Diamond::Vector2::add(Vector2 b) {
	x += b.x, y += b.y;
	return *this;
}

Vector2 &Diamond::Vector2::sub(Vector2 b) {
	x -= b.x, y -= b.y;
	return *this;
}

Vector2 &Diamond::Vector2::scalar(float scalar) {
	x *= scalar, y *= scalar;
	return *this;
}
