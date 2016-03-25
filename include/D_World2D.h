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

#ifndef D_WORLD_2D_H
#define D_WORLD_2D_H

#include "D_Entity2D.h"

namespace Diamond {
    class World2D {
    public:
        World2D(PhysicsWorld2D *phys_world);

        // TODO: implement custom allocator!
        Entity2D *createEntity(const std::string &name);

        void addEntity(Entity2D *entity);

        void kill(Entity2D *entity);

        void killAll();

        void update(tD_delta delta_ms);

        Entity2D *getRoot() const { return root; }

    private:
        PhysicsWorld2D *phys_world;
        Entity2D *root;

        void killTree(Entity2D *root);
    };
}

#endif // D_WORLD_2D_H
