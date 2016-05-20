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

#include "D_World2D.h"


Diamond::World2D::World2D(DataCenter *data) : data(data), root(createEntity("root")) {}

void Diamond::World2D::killAll() {
    killTree(root);
}

void Diamond::World2D::update(tD_delta delta_ms) {
    updateComponents(delta_ms);
    updateTransforms();
}

void Diamond::World2D::updateComponents(tD_delta delta_ms) {
    root->updateComponents(delta_ms);
}

void Diamond::World2D::updateTransforms() {
    root->updateChildrenTransforms();
}

void Diamond::World2D::killTree(Entity2D *root) {
    if (root) {
        for (Entity2D *child : root->getChildren()) {
            killTree(child);
        }
        delete root;
    }
}
