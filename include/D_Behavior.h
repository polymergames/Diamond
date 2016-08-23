/*
    Copyright 2016 Ahnaf Siddiqui

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

#include "D_typedefs.h"

namespace Diamond {
    /**
     * The update functions should return whether
     * the behavior should continue being updated,
     * (true), or destroyed (false)
     */
    class Behavior {
    public:
        virtual ~Behavior() {}

        virtual bool update(tD_delta delta) { return true; }

        virtual bool postPhysicsUpdate(tD_delta delta) { return true; }
    };
}

#endif // D_BEHAVIOR_H
