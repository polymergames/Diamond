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

namespace Diamond {
    namespace World2D {
        Entity2D root;
    }
}

void Diamond::World2D::addEntity(Diamond::Entity2D *entity) {
    root.addChild(entity);
}

void Diamond::World2D::update(tD_delta delta_ms) {
    root.updateBehaviors(delta_ms);
}

Diamond::Entity2D *Diamond::World2D::getRoot() {
    return &root;
}
