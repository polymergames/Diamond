/*
    Copyright 2016 Ahnaf Siddiqui

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

#ifndef D_ENTITY_H
#define D_ENTITY_H

#include <map>
#include <memory>
#include <typeindex>
#include "D_Component.h"

namespace Diamond { 
    /**
     Holds and updates a table of components indexed by type.
     The purpose of this class is to handle component ownership.
     Therefore, it takes ownership of any component added to it
     and destroys all of its components at the end of its lifetime.

     Special thanks to Chewy Gumball and vijoc on stackoverflow for addComponent() and getComponent() functions.
     http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
    */
    class Entity {
    public:
        Entity() = default;
        virtual ~Entity() {}

        // We don't think it's a good idea to copy ownership for a set of unknown components
        Entity(const Entity&) = delete;
        Entity& operator=(const Entity&) = delete;



        /**
         Call this once a frame to update all of this entity's components.
        */
        void updateComponents(tD_delta delta) {
            for (auto it = m_components.begin(); it != m_components.end(); ++it)
                it->second->update(delta);
        }



        void addComponent(Component *component) {
            std::type_index index = typeid(*component);
            if (!m_components[index])
                m_components[index] = std::unique_ptr<Component>(component);
        }

        template <class T, typename... Args>
        void addComponent(Args&&... args) {
            std::type_index index = typeid(T);
            if (!m_components[index])
                m_components[index] = std::unique_ptr<Component>(new T(std::forward<Args>(args)...));
        }

        template <class T>
        T *getComponent() const {
            auto c = m_components.find(std::type_index(typeid(T)));
            if (c != m_components.end())
                return static_cast<T*>(c->second.get());
            else
                return nullptr;
        }

        template <class T>
        void removeComponent() {
            auto c = m_components.find(std::type_index(typeid(T)));
            if (c != m_components.end())
                m_components.erase(c);
        }

    protected:
        std::map<std::type_index, std::unique_ptr<Component> > m_components;
    };
}


#endif // D_ENTITY_H
