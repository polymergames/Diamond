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
    /**
     This is the World Tree, the Tree of Life.
     The purpose of this class is to connect the heavens, the earth, and the underworld.
    */
    class World2D {
    public:
        World2D(DataCenter *data) : data(data), root(createEntity("root")) {}

        // TODO: implement custom allocator!
        /**
         Allocates memory for and constructs an Entity with the given name.
        */
        Entity2D *createEntity(const std::string &name) { return new Entity2D(name, data); }

        /**
         Adds the given entity to the world tree.
        */
        void addEntity(Entity2D *entity) { root->addChild(entity); }

        /**
        */
        void kill(Entity2D *entity) {
            entity->removeSelf();
            delete entity;
        }

        void killAll();

        void update(tD_delta delta_ms);

        Entity2D *getRoot() const { return root; }

    private:
        DataCenter *data;
        Entity2D *root;

        void killTree(Entity2D *root);
    };
}

#endif // D_WORLD_2D_H
