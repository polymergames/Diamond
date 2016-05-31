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

#ifndef D_ANIMATION2D_H
#define D_ANIMATION2D_H

#include <vector>

#include "D_typedefs.h"
#include "D_Texture.h"

namespace Diamond {
    struct Animation2D {
        std::vector<SharedPtr<Texture> > sprites;

        /**
         The length of time in type of tD_delta of one animation frame
        */
        tD_delta frame_length = 100;
    };
}

#endif // D_ANIMATION2D_H

