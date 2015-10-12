/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_RENDERER_2D_H
#define SDL_RENDERER_2D_H

#include <vector>
#include "Config.h"
#include "Renderer2D.h"
#include "SDL.h"
#include "SDLRenderObj2D.h"

namespace Diamond {

	class SDLRenderer2D : public Renderer2D {
		public:
		static int reserve_size; ///< For advanced users: can set the # objects by which to reallocate when growing rendering vectors

		SDLRenderer2D();
		
		/**
		 Initializes SDL, creates window, and initializes image loading.
		*/
		bool init(Config &config);

		/**
		 Called in game loop. Renders graphics as well as handles SDL events.
		*/
		void render();

		/**
		 Creates an SDLRenderObj2D, which is a rendering unit for the render loop.
		*/
		void gen_render_obj(GameObject2D *parent, Texture *texture);

		/**
		 Removes the render object at the given index from the rendering vector.
		*/
		void destroy_render_obj(unsigned long index);

		/**
		 Destroys window and renderer and shuts down SDL and SDL extensions.
		*/
		~SDLRenderer2D();

		private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event e;

		std::vector<SDLRenderObj2D> render_objects;

		void render_graphics();
	};
}

#endif // SDL_RENDERER_2D_H
