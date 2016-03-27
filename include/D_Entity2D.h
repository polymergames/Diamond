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
#include <vector>
#include "D_typedefs.h"
#include "D_Behavior.h"
#include "D_Component.h"
#include "D_PhysicsWorld2D.h"

namespace Diamond {
    class Entity2D {
    public:
        Entity2D(PhysicsWorld2D *phys_world, const std::string &name);
        virtual ~Entity2D();
        
        Entity2D(const Entity2D &other);
        Entity2D(Entity2D &&other);
        
        Entity2D &operator=(const Entity2D &other);
        Entity2D &operator=(Entity2D &&other);
        
        //tD_id getID() const;

        std::string getName() const { return name; }

        void addChild(Entity2D *child);
        
        /**
         Searches children for the given child and removes it from children.
         Returns true if child was found and removed, otherwise false.
        */
        bool removeChild(Entity2D *child);

        /**
         This entity removes itself from the entity tree.
         More specifically, this entity transfers all of its children to its parent
         and removes itself from its parent's children list.
        */
        void removeSelf();

        std::vector<Entity2D*> &getChildren() { return children; }

        Entity2D *getParent() const { return parent; }

        void addComponent(Component *component);
        template <class T, typename... Args> void addComponent(Args&&... args);
        template <class T> T *getComponent();
        template <class T> void removeComponent();

        void addBehavior(Behavior *behavior);
        template <class T, typename... Args> void addBehavior(Args&&... args);
        template <class T> T *getBehavior();
        template <class T> void removeBehavior();

        /**
         Returns this entity's current transform.
        */
        Transform2<tD_pos, tD_rot> getTransform() const { return phys_world->getTransform(transform); }
        transform2_id getTransformID() const { return transform; }
        
        void setTransform(const Transform2<tD_pos, tD_rot> &newtrans) { phys_world->setTransform(transform, newtrans); }
        void setPosition(const Vector2<tD_pos> &newpos) { phys_world->setPosition(transform, newpos); }
        void setRotation(tD_rot newrot) { phys_world->setRotation(transform, newrot); }

        void updateBehaviors(tD_delta delta_ms);

    protected:
        PhysicsWorld2D *phys_world;
        //tD_id id;
        std::string name;
        transform2_id transform;
        
        Entity2D *parent;
        std::vector<Entity2D*> children;
        std::unordered_map<std::type_index, std::unique_ptr<Component> > components; // components interface with backend data, therefore each entity has its own unique copy
        std::map<std::type_index, std::unique_ptr<Behavior> > behaviors;  // a behavior should be self-contained, so main data manipulation happens within the behavior. 
        // Unlike commponents, behaviors are iterated and updated directly from the entity.
        
        void setParent(Entity2D *parent);

        void freeTransform();
    };
}

/*inline tD_id Diamond::Entity2D::getID() const {
    return id;
}*/

// Special thanks to Chewy Gumball and vijoc on stackoverflow for addComponent() and getComponent() functions.
// http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
template <class T, typename... Args>
void Diamond::Entity2D::addComponent(Args&&... args) {
    std::type_index index = typeid(T);
    if (!components[index])
        components[index] = std::unique_ptr<Component>(new T(std::forward<Args>(args)...));
}

template <class T>
T *Diamond::Entity2D::getComponent() {
    auto c = components.find(std::type_index(typeid(T)));
    if (c != components.end())
        return static_cast<T*>(c->second.get());
    else
        return nullptr;
}

template <class T>
void Diamond::Entity2D::removeComponent() {
    auto c = components.find(std::type_index(typeid(T)));
    if (c != components.end())
        components.erase(c);
}

template <class T, typename... Args>
void Diamond::Entity2D::addBehavior(Args&&... args) {
    std::type_index index = typeid(T);
    if (!behaviors[index])
        behaviors[index] = std::unique_ptr<Behavior>(new T(std::forward<Args>(args)...));
}

template <class T>
T *Diamond::Entity2D::getBehavior() {
    auto b = behaviors.find(std::type_index(typeid(T)));
    if (b != behaviors.end())
        return static_cast<T*>(b->second.get());
    else
        return nullptr;
}

template <class T>
void Diamond::Entity2D::removeBehavior() {
    auto b = behaviors.find(std::type_index(typeid(T)));
    if (b != behaviors.end())
        behaviors.erase(b);
}


#endif // D_ENTITY2D_H
