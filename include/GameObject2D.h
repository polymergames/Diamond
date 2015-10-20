/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GAME_OBJECT_2D_H
#define GAME_OBJECT_2D_H

#include <memory>
#include "Texture.h"
#include "Transform2.h"

namespace Diamond {
	class RenderObj2D;

	class GameObject2D {
		public:
		Transform2 *transform;

		GameObject2D();
		GameObject2D(std::shared_ptr<Texture> sprite);

		std::shared_ptr<Texture> get_sprite();

		void set_sprite(std::shared_ptr<Texture> sprite);

		bool is_visible();

		/**
		 Causes this game object to be rendered.
		 This game object must have a sprite (use set_sprite() if needed) before calling this function.
		 Returns whether this game object was successfully made visible.		 
		*/
		bool make_visible();

        /**
         Causes this game object to stop being rendered.
        */
        void make_invisible();
        
        /**
         If this game object is currently visible, makes it invisible (ie not rendered), and vice versa.
        */
        bool toggle_visibility();
        
        /**
         Updates the render object's parent pointer to point to this game object.
         Call this if this game object's address has changed.
         */
        void re_adopt_render_obj();

		/**
		 Do not call unless you know what you're doing!
		*/
		void set_render_obj(RenderObj2D *render_obj);

		~GameObject2D();

		private:
		std::shared_ptr<Texture> sprite;
		RenderObj2D *render_obj;
		bool visible;
	};
}

#endif // GAME_OBJECT_2D_H
