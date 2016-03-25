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
#include "D_PhysicsWorld2D.h"
#include "D_Rigidbody2D.h"

namespace Diamond {
    /**
     An abstract base class for Collider components.
     Do not try to instantiate. Use a derived shape collider component.
    */
    class ColliderComponent2D : public Component {
    public:
        virtual ~ColliderComponent2D() = 0;

        void onCollide(void *other) {
            onCollision(static_cast<Entity2D*>(other));
        }
    
    protected:
        std::function<void(Entity2D *other)> onCollision;
        PhysicsWorld2D *phys_world;
        DRigidbody2D *body;

        ColliderComponent2D(Entity2D *parent,
                            std::function<void(Entity2D *other)> &onCollision,
                            PhysicsWorld2D *phys_world);
    };
}

#endif // D_COLLIDER_COMPONENT_2D_H

