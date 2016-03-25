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

#include "D_ColliderComponent2D.h"
#include "D_RigidbodyComponent2D.h"


Diamond::ColliderComponent2D::ColliderComponent2D(Entity2D *parent, 
                                                  std::function<void(Entity2D *other)> &onCollision,
                                                  PhysicsWorld2D *phys_world)
    : Component(parent), onCollision(onCollision), phys_world(phys_world) {
    
    RigidbodyComponent2D *rbcomp = parent->getComponent<RigidbodyComponent2D>();
    if (!rbcomp) {
        // TODO: throw exception and log error
        std::cout << "ColliderComponent2D: No rigidbody component found for parent " << parent->getName() << "!" << std::endl;
    }
        
    body = rbcome->getBody();
}

Diamond::ColliderComponent2D::~ColliderComponent2D() {}
