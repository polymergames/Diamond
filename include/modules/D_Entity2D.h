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

#ifndef D_ENTITY2D_H
#define D_ENTITY2D_H

#include <memory>
#include "Q_QuantumWorld2D.h"

#include "D_Component.h"
#include "D_typedefs.h"

namespace Diamond {
	class Entity2D {
		public:
		Entity2D();
		~Entity2D();
		
		Entity2D(const Entity2D &other);
		Entity2D(Entity2D &&other);
		
		Entity2D &operator=(const Entity2D &other);
		Entity2D &operator=(Entity2D &&other);
		
		/**
		 Returns a reference to this entity's transform.
		 Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
		 Only use this reference immediately after calling this function! (ie, call this function again every time you want access)
		 */
		Transform2i &getTransform() const;
		
		void setTransform(Transform2i &new_transform);
		void setTransform(Vector2i &position);
		void setTransform(int x, int y);
		void setRotation(float rotation);
		
		void update(int16_t delta_ms);
		
		protected:
		transform2_id transform;
		
		Entity2D *parent;
		std::vector<Entity2D*> children;
		std::vector<std::unique_ptr<Component>> components;
		
		private:
		void freeTransform();
	};
}

inline Diamond::Transform2i &Diamond::Entity2D::getTransform() const {
	return Quantum2D::QuantumWorld2D::getTransform(transform);
}

inline void Diamond::Entity2D::setTransform(Transform2i &new_transform) {
	getTransform() = new_transform;
}

inline void Diamond::Entity2D::setTransform(Diamond::Vector2i &position) {
	Quantum2D::QuantumWorld2D::getTransform(transform).position = position;
}

inline void Diamond::Entity2D::setTransform(int x, int y) {
	Quantum2D::QuantumWorld2D::getTransform(transform).position.x = x;
	Quantum2D::QuantumWorld2D::getTransform(transform).position.y = y;
}

inline void Diamond::Entity2D::setRotation(float rotation) {
	Quantum2D::QuantumWorld2D::getTransform(transform).rotation = rotation;
}


#endif // D_ENTITY2D_H
