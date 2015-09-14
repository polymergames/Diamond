/*
 Copyright (c) 2015 Polymer Games
 */
#pragma once
class Renderer
{
	public:
	static void setRenderer(Renderer *renderer);

	private:
	static Renderer *renderer;
};
