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

#ifndef D_LAUNCHER_H
#define D_LAUNCHER_H

#ifdef __ANDROID__
#include "SDL.h" // Has to be included with game's main function for SDL_main to work
#endif

#include "D_Config.h"
#include "D_Game.h"

namespace Diamond {
    namespace Launcher {
        // TODO: make these private and add accessor functions
        extern bool is_open;
        extern Config config;

        /**
         Call only once, at beginning of game!
        */
        void launch(Game &game);

        void quit();
    };
}

#endif // D_LAUNCHER_H
