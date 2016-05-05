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

#ifndef D_RIGIDBODY_COMPONENT_2D_H
#define D_RIGIDBODY_COMPONENT_2D_H

#include "D_Component.h"
#include "D_Entity2D.h"
#include "D_PhysicsWorld2D.h"
#include "D_Rigidbody2D.h"
#include "D_typedefs.h"

namespace Diamond {
    class RigidbodyComponent2D : public Component {
    public:
        RigidbodyComponent2D(const Entity2D *parent, PhysicsWorld2D *world) : world(world) {
            body = world->genRigidbody(parent->getTransformID());
        }

        ~RigidbodyComponent2D() { world->freeRigidbody(body); }
        
        Rigidbody2D *getBody() const { return body; }

        Rigidbody2D *operator->() const { return body; }

    private:
        Rigidbody2D *body;
        PhysicsWorld2D *world;
    };
}

#endif // D_RIGIDBODY_COMPONENT_2D_H

