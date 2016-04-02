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

#ifndef D_COLLIDER_COMPONENT_2D_H
#define D_COLLIDER_COMPONENT_2D_H

#include <functional>
#include "D_Component.h"
#include "D_Collider2D.h"
#include "D_PhysicsWorld2D.h"
#include "D_RigidbodyComponent2D.h"
#include "D_Rigidbody2D.h"

namespace Diamond {
    class ColliderComponent2D : public Component {
    public:
        template <typename... Args>
        ColliderComponent2D(Entity2D *parent, Collider2D *collider) : Component(parent), collider(collider) {}
        
        ~ColliderComponent2D() {
            // TODO: should be managed by physics world?
            delete collider;
        }
        
        void *getCollider() const { return collider; }
    
    private:
        Collider2D *collider;
    };
}

#endif // D_COLLIDER_COMPONENT_2D_H

