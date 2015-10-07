/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

namespace Diamond {
	struct Config;

	class Renderer {
		public:
		virtual bool init(Config &config) = 0;
		virtual void render() = 0;
		virtual ~Renderer();
	};
}

#endif // RENDERER_H
