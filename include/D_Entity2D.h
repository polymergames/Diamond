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
#include <vector>
#include "D_Component.h"
#include "D_DataCenter.h"
#include "D_typedefs.h"

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

        // Local transform functions.
        const Transform2<tD_pos, tD_rot> &getLocalTransform() const { return local_transform; }
        Transform2<tD_pos, tD_rot> &getLocalTransform() { return local_transform; }

        void setLocalTransform(const Transform2<tD_pos, tD_rot> &newtrans) { local_transform = newtrans; }
        void setLocalPosition(const Vector2<tD_pos> &newpos) { local_transform.position = newpos; }
        void setLocalRotation(tD_rot newrot) { local_transform.rotation = newrot; }


        // World transform functions.
        const Transform2<tD_pos, tD_rot> &getWorldTransform() const { return data->getTransform(world_transform); }
        Transform2<tD_pos, tD_rot> &getWorldTransform() { return data->getTransform(world_transform); }
        transform2_id getTransformID() const { return world_transform; }

        void setWorldTransform(const Transform2<tD_pos, tD_rot> &newtrans) { data->getTransform(world_transform) = newtrans; }
        void setWorldPosition(const Vector2<tD_pos> &newpos) { data->getTransform(world_transform).position = newpos; }
        void setWorldRotation(tD_rot newrot) { data->getTransform(world_transform).rotation = newrot; }


        // Manage entity tree.

        /**
         Adds the given entity to this entity's children and sets the child's parent as this entity.
        */
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


        // Tree update functions
        void update(tD_delta delta, Vector2<tD_pos> parent_translation);
        void update(tD_delta delta);
        void updateComponents(tD_delta delta);
        void updateChildren(tD_delta delta);

    protected:
        //tD_id id;
        std::string name;
        Transform2<tD_pos, tD_rot> local_transform;
        transform2_id world_transform;
        DataCenter *data;
        
        Entity2D *parent;
        std::vector<Entity2D*> children;

        // Components interface with backend data, therefore each entity has its own unique copy.
        // All components are updated once every frame.
        std::map<std::type_index, std::unique_ptr<Component> > components;
        
        void setParent(Entity2D *parent);

        void freeTransform();
    };
}


#endif // D_ENTITY2D_H
