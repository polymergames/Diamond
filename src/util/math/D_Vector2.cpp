/*
    Copyright 2015 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
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
