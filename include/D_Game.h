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

#ifndef D_GAME_H
#define D_GAME_H

#include <stdint.h>
#include "D_typedefs.h"

namespace Diamond {
    class Game {
    public:
        virtual ~Game() {}

        /**
         Called at beginning of game, after Diamond backend systems have initialized.
         Put game initialization code here.
        */
        virtual void init() = 0;

        /**
         Called once every frame, where delta is the time in seconds since the last frame.
         Update game logic here.
        */
        virtual void update(tD_delta delta) = 0;

        /**
         Called when game ends.
         Put cleanup code here.
        */
        virtual void quit() = 0;
    };
}

#endif // D_GAME_H
