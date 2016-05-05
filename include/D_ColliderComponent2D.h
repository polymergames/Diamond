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

#include "D_Component.h"
#include "D_Collider2D.h"
#include "D_PhysicsWorld2D.h"

namespace Diamond {
    class ColliderComponent2D : public Component {
    public:
        ColliderComponent2D(Collider2D *collider, PhysicsWorld2D *phys_world) 
            : collider(collider), phys_world(phys_world) {}
        
        ~ColliderComponent2D() { phys_world->freeCollider(collider); }
        
        Collider2D *getCollider() const { return collider; }

        Collider2D *operator->() const { return collider; }
    
    private:
        Collider2D *collider;
        PhysicsWorld2D *phys_world;
    };
}

#endif // D_COLLIDER_COMPONENT_2D_H

