/*
 Copyright (c) 2015 Polymer Games
 */

#include "Graphics.h"

Graphics Graphics::*graphics = nullptr;

void Graphics::setGraphics(Graphics *graphics)
{
	Graphics::graphics = graphics;
}
