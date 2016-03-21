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

#ifndef D_ENGINE_H
#define D_ENGINE_H

#include "D_DiskJockey2D.h"
#include "D_Logger.h"
#include "D_Renderer2D.h"

namespace Diamond {
    struct Engine {
        Logger *logger;
        Renderer2D *renderer;
        DiskJockey2D *dj;
    };
}

#endif // D_ENGINE_H
