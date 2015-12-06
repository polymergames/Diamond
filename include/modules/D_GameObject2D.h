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
#include "Q_QuantumWorld2D.h"

#include "D_Graphics2D.h"
#include "D_Texture.h"
#include "D_Transform2i.h"
#include "D_typedefs.h"

namespace Diamond {
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
		 Returns a reference to this gameobject's transform.
		 Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
		 Only use this reference immediately after calling this function! (ie, call this function again every time you want access)
		*/
		Transform2i &getTransform() const;
		
		float getScale() const;
		
		void setTransform(Transform2i &new_transform);
		
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
		
		~GameObject2D();

		private:
		std::shared_ptr<Texture> sprite;
		transform2_id transform;
		renderobj_id render_obj;
		bool visible;
		float scale;

		void applyScale();
		void freeTransform();
		void freeRenderObj();
	};
}

inline std::shared_ptr<Diamond::Texture> Diamond::GameObject2D::getSprite() const {
	return sprite;
}

inline Diamond::Transform2i &Diamond::GameObject2D::getTransform() const {
	return Quantum2D::QuantumWorld2D::getTransform(transform);
}

inline float Diamond::GameObject2D::getScale() const {
	return scale;
}

inline void Diamond::GameObject2D::setTransform(Diamond::Vector2i &position) {
	Quantum2D::QuantumWorld2D::getTransform(transform).position = position;
}

inline void Diamond::GameObject2D::setTransform(int x, int y) {
	Quantum2D::QuantumWorld2D::getTransform(transform).position.x = x;
	Quantum2D::QuantumWorld2D::getTransform(transform).position.y = y;
}

inline void Diamond::GameObject2D::setSize(Diamond::Vector2i &size) {
	Quantum2D::QuantumWorld2D::getTransform(transform).size = size;
}

inline void Diamond::GameObject2D::setRotation(float rotation) {
	Quantum2D::QuantumWorld2D::getTransform(transform).rotation = rotation;
}

inline void Diamond::GameObject2D::flipX() {
	Graphics2D::getRenderObj(render_obj)->flipX();
}

inline void Diamond::GameObject2D::flipY() {
	Graphics2D::getRenderObj(render_obj)->flipY();
}

inline int Diamond::GameObject2D::isFlippedX() const {
	return Graphics2D::getRenderObj(render_obj)->isFlippedX();
}

inline int Diamond::GameObject2D::isFlippedY() const {
	return Graphics2D::getRenderObj(render_obj)->isFlippedY();
}

inline bool Diamond::GameObject2D::isVisible() const {
	return visible;
}

#endif // D_GAME_OBJECT_2D_H
