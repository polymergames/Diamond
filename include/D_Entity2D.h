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
#include "D_DataCenter.h"

namespace Diamond {
    class Entity2D {
    public:
        Entity2D(const std::string &name, DataCenter *data);
        virtual ~Entity2D();
        
        Entity2D(const Entity2D &other);
        Entity2D(Entity2D &&other);
        
        Entity2D &operator=(const Entity2D &other);
        Entity2D &operator=(Entity2D &&other);
        
        //tD_id getID() const { return id; }
        const std::string &getName() const { return name; }


        // Get this entity's current transform.

        const Transform2<tD_pos, tD_rot> &getTransform() const { return data->getTransform(transform); }
        Transform2<tD_pos, tD_rot> &getTransform() { return data->getTransform(transform); }
        transform2_id getTransformID() const { return transform; }
        

        // Modify this entity's transform.

        void setTransform(const Transform2<tD_pos, tD_rot> &newtrans) { data->getTransform(transform) = newtrans; }
        void setPosition(const Vector2<tD_pos> &newpos) { data->getTransform(transform).position = newpos; }
        void setRotation(tD_rot newrot) { data->getTransform(transform).rotation = newrot; }


        // Manage entity tree.

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
        const std::vector<Entity2D*> &getChildren() const { return children; }

        Entity2D *getParent() const { return parent; }


        // Manage this entity's components.

        void addComponent(Component *component);

        // Special thanks to Chewy Gumball and vijoc on stackoverflow for addComponent() and getComponent() functions.
        // http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
        template <class T, typename... Args>
        void addComponent(Args&&... args) {
            std::type_index index = typeid(T);
            if (!components[index])
                components[index] = std::unique_ptr<Component>(new T(std::forward<Args>(args)...));
        }

        template <class T>
        T *getComponent() const {
            auto c = components.find(std::type_index(typeid(T)));
            if (c != components.end())
                return static_cast<T*>(c->second.get());
            else
                return nullptr;
        }

        template <class T>
        void removeComponent() {
            auto c = components.find(std::type_index(typeid(T)));
            if (c != components.end())
                components.erase(c);
        }

        void addBehavior(Behavior *behavior);

        template <class T, typename... Args>
        void addBehavior(Args&&... args) {
            std::type_index index = typeid(T);
            if (!behaviors[index])
                behaviors[index] = std::unique_ptr<Behavior>(new T(std::forward<Args>(args)...));
        }

        template <class T>
        T *getBehavior() const {
            auto b = behaviors.find(std::type_index(typeid(T)));
            if (b != behaviors.end())
                return static_cast<T*>(b->second.get());
            else
                return nullptr;
        }

        template <class T>
        void removeBehavior() {
            auto b = behaviors.find(std::type_index(typeid(T)));
            if (b != behaviors.end())
                behaviors.erase(b);
        }

        void updateComponents(tD_delta delta_ms);
        void updateBehaviors(tD_delta delta_ms);

    protected:
        //tD_id id;
        std::string name;
        transform2_id transform;
        DataCenter *data;
        
        Entity2D *parent;
        std::vector<Entity2D*> children;

        // Components interface with backend data, therefore each entity has its own unique copy.
        std::unordered_map<std::type_index, std::unique_ptr<Component> > components;

        // A behavior should be self-contained, so main data manipulation happens within the behavior.
        // Unlike commponents, behaviors are iterated and updated directly from the entity.
        std::map<std::type_index, std::unique_ptr<Behavior> > behaviors;
        
        void setParent(Entity2D *parent);

        void freeTransform();
    };
}


#endif // D_ENTITY2D_H
