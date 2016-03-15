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
    class ColliderComponent2D : public Component {
    public:
        ColliderComponent2D(Entity2D *parent, std::function<void(Entity2D *other)> &onCollision)
            : Component(parent), onCollision(onCollision) {}

        virtual ~ColliderComponent2D() {}

        collider2_id getID() const { return collider; }

        virtual void onCollide(void *other) {
            onCollision(static_cast<Entity2D*>(other));
        }

    private:
        collider2_id collider;
        std::function<void(Entity2D *other)> onCollision;
    };
}

#endif // D_COLLIDER_COMPONENT_2D_H

