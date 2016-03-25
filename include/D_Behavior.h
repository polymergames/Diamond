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

#ifndef D_BEHAVIOR_H
#define D_BEHAVIOR_H

#include "D_Component.h"
#include "D_typedefs.h"

namespace Diamond {
    class Entity2D;
    class Behavior : public Component {
    public:
        Behavior(Entity2D *parent) : Component(parent) {}
        virtual ~Behavior() {};

        virtual void update(tD_delta delta) = 0;
    };
}

#endif // D_BEHAVIOR_H
