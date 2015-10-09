/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <iostream>

namespace Diamond {
	struct Config;

	class Renderer2D {
		public:
		virtual bool init(Config &config) = 0;
		virtual void render() = 0;
		virtual ~Renderer2D();
	};
}

#endif // RENDERER_2D_H
