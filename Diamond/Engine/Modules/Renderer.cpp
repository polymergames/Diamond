/*
 Copyright (c) 2015 Polymer Games
 */
#include "Renderer.h"

Renderer Renderer::*renderer = nullptr;

void Renderer::setRenderer(Renderer *renderer)
{
	if (Renderer::renderer == nullptr && renderer != nullptr)
		Renderer::renderer = renderer;
}
