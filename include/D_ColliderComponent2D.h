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
        enum Coltype {
            AABB, CIRCLE, POLY, NUMCOLTYPES
        };
        
        template <typename... Args>
        ColliderComponent2D(Entity2D *parent,
                            std::function<void(Entity2D *other)> &onCollision,
                            PhysicsWorld2D *phys_world,
                            Coltype type,
                            Args&&... args)
            : Component(parent), onCollision(onCollision), type(type) {
            RigidbodyComponent2D *rbcomp = parent->getComponent<RigidbodyComponent2D>();
            if (!rbcomp) {
                // TODO: throw exception and log error
                std::cout << "ColliderComponent2D: No rigidbody component found for parent " << parent->getName() << "!" << std::endl;
            }
            
            DRigidbody2D body = rbcomp->getBody();
            std::function<void(void*)> callback = std::bind(&ColliderComponent2D::onCollide, this, std::placeholders::_1);
            
            switch (type) {
                case AABB:
                    collider = phys_world->genAABBCollider(body, parent, callback, std::forward<Args>(args)...);
                    break;
                case CIRCLE:
                    collider = phys_world->genCircleCollider(body, parent, callback, std::forward<Args>(args)...);
                    break;
                case POLY:
                    // TODO
                    // collider = ;
                    break;
                default:
                    // TODO: throw exception and log error
                    std::cout << "ColliderComponent2D: invalid collider type " << type << std::endl;
                    break;
            }
        }
                            
        
        ~ColliderComponent2D() {
            // TODO: should be managed by physics world?
            delete collider;
        }
        
        Coltype getType() const { return type; }
        
        void *getCollider() const { return collider; }

        void onCollide(void *other) { onCollision(static_cast<Entity2D*>(other)); }
    
    private:
        Coltype type;
        Collider2D *collider;
        
        std::function<void(Entity2D *other)> onCollision;
    };
}

#endif // D_COLLIDER_COMPONENT_2D_H

