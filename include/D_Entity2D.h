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
#include "D_Component.h"
#include "D_typedefs.h"

namespace Diamond { 
    /**
     Holds a table of components indexed by type.
     The purpose of this class is to handle component ownership.
     Therefore, it takes ownership of any component added to it
     and destroys all of its components at the end of its lifetime.

     Special thanks to Chewy Gumball and vijoc on stackoverflow for addComponent() and getComponent() functions.
     http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
    */
    class Entity2D {
    public:
        void addComponent(Component *component);

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

        // TODO: remove this and remove update function from Component
        void updateComponents(tD_delta delta);

    protected:
        std::map<std::type_index, std::unique_ptr<Component> > components;
    };
}


#endif // D_ENTITY2D_H
