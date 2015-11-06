/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_RENDERER_2D_H
#define D_SDL_RENDERER_2D_H

#include <vector>
#include "SDL.h"

#include "D_Config.h"
#include "D_Renderer2D.h"
#include "D_SDLRenderObj2D.h"

namespace Diamond {
	class SDLRenderer2D : public Renderer2D {
		public:
		static int reserve_size; ///< For advanced users: can set the # objects by which to reallocate when growing rendering vectors

		SDLRenderer2D();
		
		/**
		 Initializes SDL, creates window, and initializes image loading.
		 Returns whether all of the initialization was successful.
		*/
		bool init() override;

		/**
		 Called in game loop. Renders graphics as well as handles SDL events.
		*/
		void render() override;
		
		/**
		 Loads an image file as an SDL texture. Caller is responsible for ownership!
		 Returns nullptr if texture failed to load.
		*/
		Texture *load_texture(std::string path) override;

		/**
		 Creates an SDLRenderObj2D, which is a rendering unit for the render loop.
		*/
		void gen_render_obj(GameObject2D *parent, Texture *texture) override;
		
		void activate_render_obj(unsigned long index) override;
		
		void deactivate_render_obj(unsigned long index) override;

		/**
		 Removes the render object at the given index from the rendering vector.
		*/
		void destroy_render_obj(unsigned long index) override;
		
		void destroy_inactive_render_obj(unsigned long index) override;

		/**
		 Destroys window and renderer and shuts down SDL and SDL extensions.
		*/
		~SDLRenderer2D();

		private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event e;

		std::vector<SDLRenderObj2D> render_objects;
		std::vector<SDLRenderObj2D> inactive_render_objects;

		void reserve_r_obj_vec(std::vector<SDLRenderObj2D> &v);
	};
}

#endif // D_SDL_RENDERER_2D_H
