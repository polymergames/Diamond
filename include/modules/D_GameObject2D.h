/*
    Copyright 2015 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef D_GAME_OBJECT_2D_H
#define D_GAME_OBJECT_2D_H

#include <memory>

#include "D_Texture.h"
#include "D_Transform2i.h"

namespace Diamond {
	class RenderObj2D;
	
	class GameObject2D {
		public:
		GameObject2D(std::shared_ptr<Texture> sprite);
		GameObject2D(const GameObject2D &other);
		GameObject2D(GameObject2D &&other);

		GameObject2D &operator=(const GameObject2D &other);
		GameObject2D &operator=(GameObject2D &&other);

		std::shared_ptr<Texture> getSprite() const;
		void setSprite(std::shared_ptr<Texture> sprite);

		/**
		 Returns a COPY of this game object's transform.
		*/
		Transform2i getTransform() const;
		
		inline float getScale() const {
			return scale;
		}
		
		void setTransform(Transform2i &transform);
		void setTransform(Vector2i &position);
		void setTransform(int x, int y);
		void setSize(Vector2i &size);
		void setScale(float scale);
		void setRotation(float rotation);
		
		void flipX();
		void flipY();
		
		int isFlippedX() const;
		int isFlippedY() const;

		/**
		 Returns whether this game object's sprite is currently being rendered.
		*/
		bool isVisible() const;

		/**
		 Causes this game object to be rendered.
		 This game object must have a sprite (use setSprite() if needed) before calling this function.
		*/
		void makeVisible();

		/**
		 Causes this game object to stop being rendered.
		*/
		void makeInvisible();
		
		/**
		 If this game object is currently visible, makes it invisible (ie not rendered), and vice versa.
		*/
		void toggleVisibility();
		
		/**
		 Updates the render object's parent pointer to point to this game object.
		 Call this if this game object's address has changed (might happen if, for ex, you store your gameobjects in a vector).
		*/
		void reAdoptRenderObj();

		/**
		 Do not call unless you know what you're doing!
		*/
		void setRenderObj(RenderObj2D *render_obj);

		~GameObject2D();

		private:
		std::shared_ptr<Texture> sprite;
		RenderObj2D *render_obj;
		bool visible;
		float scale;

		void destroyRenderObj();
	};
}

#endif // D_GAME_OBJECT_2D_H
