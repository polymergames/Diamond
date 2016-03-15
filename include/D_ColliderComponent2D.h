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
#include "Q_typedefs.h"

namespace Diamond {
    /**
     An abstract base class for Collider components.
     Do not try to instantiate. Use a derived shape collider component.
    */
    class ColliderComponent2D : public Component {
    public:
        virtual ~ColliderComponent2D() = 0;

        collider2_id getID() const { return collider; }

        void onCollide(void *other) {
            onCollision(static_cast<Entity2D*>(other));
        }
    
    protected:
        collider2_id collider;
        std::function<void(Entity2D *other)> onCollision;

        ColliderComponent2D(Entity2D *parent, std::function<void(Entity2D *other)> &onCollision);
    };
}

#endif // D_COLLIDER_COMPONENT_2D_H

