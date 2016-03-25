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

#include <algorithm>


Diamond::Entity2D::Entity2D(PhysicsWorld2D *phys_world, const std::string &name)
    : phys_world(phys_world), name(name), parent(nullptr), transform(phys_world->genTransform()) {}


Diamond::Entity2D::~Entity2D() {
    removeSelf();
    freeTransform();
}


Diamond::Entity2D::Entity2D(const Entity2D &other) : phys_world(other.phys_world), name(other.name) {
    transform = phys_world->genTransform();
    setTransform(other.getTransform());
}

Diamond::Entity2D::Entity2D(Entity2D &&other) 
    : phys_world(other.phys_world), name(other.name), transform(other.transform) {
    other.transform = Diamond::INVALID;
}

Diamond::Entity2D &Diamond::Entity2D::operator=(const Entity2D &other) {
    if (this != &other) {
        name = other.name;
        setTransform(other.getTransform());
    }
    return *this;
}

Diamond::Entity2D &Diamond::Entity2D::operator=(Entity2D &&other) {
    if (this != &other) {
        name = other.name;
        freeTransform();
        transform = other.transform;
        other.transform = Diamond::INVALID;
    }
    return *this;
}

void Diamond::Entity2D::addChild(Entity2D *child){
    if (child && child != this) {
        children.push_back(child);
        child->setParent(this);
    }
}

bool Diamond::Entity2D::removeChild(Entity2D *child) {
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        children.erase(it);
        return true;
    }
    return false;
}

void Diamond::Entity2D::removeSelf() {
    if (parent) {
        // Remove this entity from its parent's children
        parent->removeChild(this);

        // Transfer this entity's children to this entity's parent
        // TODO: more efficient way to do this? Copy vector range and apply function to range to change each child's parent?
        for (Entity2D *child : children) {
            parent->children.push_back(child);
            child->parent = parent;
        }
    }
    else {
        for (Entity2D *child : children) {
            child->parent = nullptr;
        }
    }
}

void Diamond::Entity2D::addComponent(Component *component) {
    std::type_index index = typeid(*component);
    if (!components[index])
        components[index] = std::unique_ptr<Component>(component);
}

void Diamond::Entity2D::addBehavior(Behavior *behavior) {
    std::type_index index = typeid(*behavior);
    if (!behaviors[index])
        behaviors[index] = std::unique_ptr<Behavior>(behavior);
}

void Diamond::Entity2D::setParent(Entity2D *parent) {
    if (this->parent && this->parent != parent)
        this->parent->removeChild(this);
    this->parent = parent;
}

void Diamond::Entity2D::updateBehaviors(tD_delta delta_ms) {
    for (auto it = behaviors.begin(); it != behaviors.end(); ++it) {
        it->second->update(delta_ms);
    }

    for (Entity2D *child : children) {
        child->updateBehaviors(delta_ms);
    }
}

void Diamond::Entity2D::freeTransform() {
    if ((tD_index)transform != Diamond::INVALID) {
        phys_world->freeTransform(transform);
        transform = Diamond::INVALID;
    }
}
