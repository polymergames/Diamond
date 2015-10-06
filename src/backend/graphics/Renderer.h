/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

namespace Diamond {
	class Renderer {
		public:
		virtual void render() = 0;
		virtual ~Renderer();
	};
}

#endif // RENDERER_H
