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


Diamond::Entity2D::Entity2D(const std::string &name, DataCenter *data)
    : name(name), 
      local_transform(Vector2<tD_pos>(0,0), 0), 
      data(data), 
      parent(nullptr), 
      world_transform(data->genTransform()) {}

Diamond::Entity2D::~Entity2D() {
    freeTransform();
}


Diamond::Entity2D::Entity2D(const Entity2D &other) 
    : data(other.data), name(other.name), local_transform(other.local_transform) {
    world_transform = data->genTransform();
    setWorldTransform(other.getWorldTransform());
}

Diamond::Entity2D::Entity2D(Entity2D &&other) 
    : data(other.data), name(other.name), 
      local_transform(other.local_transform), world_transform(other.world_transform) {
    other.world_transform = Diamond::INVALID;
}

Diamond::Entity2D &Diamond::Entity2D::operator=(const Entity2D &other) {
    if (this != &other) {
        name = other.name;
        local_transform = other.local_transform;
        setWorldTransform(other.getWorldTransform());
    }
    return *this;
}

Diamond::Entity2D &Diamond::Entity2D::operator=(Entity2D &&other) {
    if (this != &other) {
        name = other.name;
        local_transform = other.local_transform;
        freeTransform();
        world_transform = other.world_transform;
        other.world_transform = Diamond::INVALID;
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
        (*it)->parent = nullptr;
        children.erase(it);
        return true;
    }
    return false;
}

void Diamond::Entity2D::removeSelf() {
    if (parent) {
        // Give this entity's children away to their granddaddy
        // TODO: more efficient way to do this? Copy vector range and apply function to range to change each child's parent?
        for (Entity2D *child : children) {
            parent->children.push_back(child);
            child->parent = parent;
        }
        
        // Get disowned
        parent->removeChild(this);
    }
    else {
        // Turn this entity's children into poor little orphans
        for (Entity2D *child : children) {
            child->parent = nullptr;
        }
    }
    // Free at last
    children.clear();
}

void Diamond::Entity2D::addComponent(Component *component) {
    std::type_index index = typeid(*component);
    if (!components[index])
        components[index] = std::unique_ptr<Component>(component);
}

void Diamond::Entity2D::setParent(Entity2D *parent) {
    if (this->parent && this->parent != parent)
        this->parent->removeChild(this);
    this->parent = parent;
}

void Diamond::Entity2D::update(tD_delta delta, Vector2<tD_pos> parent_translation, tD_rot parent_rot) {
    Transform2<tD_pos, tD_rot> &wtrans = getWorldTransform();
    wtrans.position = local_transform.position + parent_translation;
    wtrans.rotation = local_transform.rotation + parent_rot;

    updateComponents(delta);

    updateChildren(delta);
}

void Diamond::Entity2D::update(tD_delta delta) {
    updateComponents(delta);

    updateChildren(delta);
}

void Diamond::Entity2D::updateComponents(tD_delta delta) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        it->second->update(delta);
    }
}

void Diamond::Entity2D::updateChildren(tD_delta delta) {
    Transform2<tD_pos, tD_rot> wtrans = getWorldTransform();
    for (Entity2D *child : children) {
        child->update(delta, wtrans.position, wtrans.rotation);
    }
}

void Diamond::Entity2D::freeTransform() {
    if ((tD_index)world_transform != Diamond::INVALID) {
        data->freeTransform(world_transform);
        world_transform = Diamond::INVALID;
    }
}
