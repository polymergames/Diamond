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

#include "D_Entity2D.h"
#include "D_Launcher.h"


Diamond::Entity2D::Entity2D() {
	transform = Quantum2D::QuantumWorld2D::genTransform();
}


Diamond::Entity2D::~Entity2D() {
	// TODO: find exception-safer method of memory management. ie it's possible that transform has been destroyed/game has ended/crashed even if is_open = true
	if (Launcher::is_open) {
		freeTransform();

		for (Entity2D *child : children) {
			child->setParent(parent);
		}
	}
}


Diamond::Entity2D::Entity2D(const Entity2D &other) {
	transform = Quantum2D::QuantumWorld2D::genTransform();
	getTransform() = other.getTransform();
}

Diamond::Entity2D::Entity2D(Entity2D &&other) : transform(other.transform) {
	other.transform = Diamond::INVALID;
}

Diamond::Entity2D &Diamond::Entity2D::operator=(const Entity2D &other) {
	if (this != &other) {
		getTransform() = other.getTransform();
	}
	return *this;
}

Diamond::Entity2D &Diamond::Entity2D::operator=(Entity2D &&other) {
	if (this != &other) {
		// free transform
		transform = other.transform;
		other.transform = Diamond::INVALID;
	}
	return *this;
}

void Diamond::Entity2D::addChild(Entity2D *child){
	children.push_back(child);
	child->setParent(this);
}

void Diamond::Entity2D::addComponent(Component *component) {
	component->setParent(this);
	components[std::type_index(typeid(*component))] = std::unique_ptr<Component>(component);
}

void Diamond::Entity2D::setParent(Entity2D *parent) {
	this->parent = parent;
}

void Diamond::Entity2D::updateComponents(tD_delta delta_ms) {
	// TODO: update this entity's components
	for (Entity2D *child : children) {
		child->updateComponents(delta_ms);
	}
}

void Diamond::Entity2D::freeTransform() {
	if ((tD_index)transform != Diamond::INVALID) {
		Quantum2D::QuantumWorld2D::freeTransform(transform);
		transform = Diamond::INVALID;
	}
}
