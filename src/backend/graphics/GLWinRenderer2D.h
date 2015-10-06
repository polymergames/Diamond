/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GL_WIN_RENDERER_2D_H
#define GL_WIN_RENDERER_2D_H

#include <iostream>
#include <memory>
#include "GL/glew.h"
#include "Launcher.h"
#include "Renderer.h"
#include "SDL.h"
#include "SDL_opengl.h"

namespace Diamond {
	class GLWinRenderer2D : public Renderer {
		public:
		GLWinRenderer2D(Config &config);
		~GLWinRenderer2D();

		private:
		SDL_Window *window;
		SDL_GLContext context;
	};
}

#endif // GL_WIN_RENDERER_2D_H
