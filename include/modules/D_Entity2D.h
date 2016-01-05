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

#include <map>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Q_QuantumWorld2D.h"

#include "D_typedefs.h"
#include "D_Component.h"
#include "D_Behavior.h"

namespace Diamond {
	// Special thanks to Chewy Gumball and vijoc on stackoverflow for addComponent() and getComponent() functions.
	// http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
	class Entity2D {
	public:
		Entity2D();
		virtual ~Entity2D();
		
		Entity2D(const Entity2D &other);
		Entity2D(Entity2D &&other);
		
		Entity2D &operator=(const Entity2D &other);
		Entity2D &operator=(Entity2D &&other);
		
		//tD_id getID() const;

		void addChild(Entity2D *child);
		Entity2D *getParent() const;

		void addComponent(Component *component);
		template <class T> T *getComponent();
		template <class T> void removeComponent();

		void addBehavior(Behavior *behavior);
		template <class T> T *getBehavior();
		template <class T> void removeBehavior();

		/**
		 Returns a reference to this entity's transform.
		 Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
		 Only use this reference immediately after calling this function! (ie, call this function again every time you want access)
		*/
		Transform2<int, float> &getTransform() const;
		transform2_id getTransformID() const;
		
		void setTransform(Transform2<int, float> &new_transform);
		void setTransform(Vector2<int> &position);
		void setTransform(int x, int y);
		void setRotation(float rotation);
		
		/**
		 You should call addChild() on the parent instead, which then calls this.
		*/
		void setParent(Entity2D *parent);

		void updateBehaviors(tD_delta delta_ms);

	protected:
		transform2_id transform;
		
		Entity2D *parent;
		std::vector<Entity2D*> children;
		std::unordered_map<std::type_index, std::unique_ptr<Component>> components; // components interface with backend data, therefore each entity has its own unique copy
		std::map<std::type_index, std::unique_ptr<Behavior>> behaviors;  // a behavior should be self-contained, so main data manipulation happens within the behavior. 
		// Unlike commponents, behaviors are iterated and updated directly from the entity.
		
	private:
		//tD_id id;

		void freeTransform();
	};
}

/*inline tD_id Diamond::Entity2D::getID() const {
	return id;
}*/

template <class T>
T *Diamond::Entity2D::getComponent() {
	auto c = components.find(std::type_index(typeid(T)));
	if (c != components.end()) {
		return static_cast<T*>(c->second.get());
	}
	else {
		return nullptr;
	}
}

template <class T>
void Diamond::Entity2D::removeComponent() {
	auto c = components.find(std::type_index(typeid(T)));
	if (c != components.end()) {
		components.erase(c);
	}
}

template <class T>
T *Diamond::Entity2D::getBehavior() {
	auto b = behaviors.find(std::type_index(typeid(T)));
	if (b != behaviors.end()) {
		return static_cast<T*>(b->second.get());
	}
	else {
		return nullptr;
	}
}

template <class T>
void Diamond::Entity2D::removeBehavior() {
	auto b = behaviors.find(std::type_index(typeid(T)));
	if (b != behaviors.end()) {
		behaviors.erase(b);
	}
}

inline Diamond::Entity2D *Diamond::Entity2D::getParent() const {
	return parent;
}

inline Diamond::Transform2<int, float> &Diamond::Entity2D::getTransform() const {
	return Quantum2D::QuantumWorld2D::getTransform(transform);
}

inline transform2_id Diamond::Entity2D::getTransformID() const {
	return transform;
}

inline void Diamond::Entity2D::setTransform(Transform2<int, float> &new_transform) {
	getTransform() = new_transform;
}

inline void Diamond::Entity2D::setTransform(Diamond::Vector2<int> &position) {
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
