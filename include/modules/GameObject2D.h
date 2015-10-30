/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_GAME_OBJECT_2D_H
#define D_GAME_OBJECT_2D_H

#include <memory>
#include "Texture.h"
#include "Transform2.h"

namespace Diamond {
	class RenderObj2D;

	class GameObject2D {
		public:
		GameObject2D();
		GameObject2D(std::shared_ptr<Texture> sprite);

		std::shared_ptr<Texture> get_sprite();
		void set_sprite(std::shared_ptr<Texture> sprite);

		/**
		 Returns a COPY of this game object's transform if it has one, or returns a new transform.
		*/
		Transform2 get_transform();
		
		void set_transform(Transform2 &transform);
		void set_transform(Vector2 &position);
		void set_transform(float x, float y, float rotation, float scale);
		void set_transform(float x, float y);
		void set_rotation(float rotation);
		void set_scale(float scale);
		
		void flip_x();
		void flip_y();
		
		bool is_flipped_x();
		bool is_flipped_y();

		/**
		 Returns whether this game object's sprite is currently being rendered.
		*/
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
		 Call this if this game object's address has changed (might happen if, for ex, you store your gameobjects in a vector).
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

#endif // D_GAME_OBJECT_2D_H
