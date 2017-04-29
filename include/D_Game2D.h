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

#ifndef D_GAME_2D_H
#define D_GAME_2D_H

#include "D_Engine2D.h"
#include "D_typedefs.h"

namespace Diamond {
    class Game2D {
    public:
        /**
         Put game initialization code in subclass constructor.
        */
        Game2D(Engine2D &engine) : engine(engine) {}
        virtual ~Game2D() {}

        /**
         Called once every frame, where delta is the time in seconds since the last frame.
         Update game logic here.
        */
        virtual void update(tD_delta delta) {};

        /**
         Called once every frame, where delta is the time in seconds since the last frame
         (same as the delta that's passed into update).
         Update any post-physics game logic here
         (ex. if using a scene graph, you might want to update its transforms here 
         as well as after game logic in update)
        */
        virtual void postPhysicsUpdate(tD_delta delta) {};
        
        /**
         Called every frame when the game is paused.
        */
        virtual void pausedUpdate(tD_delta delta) {};

        /**
         Called when game ends.
         Put cleanup code here.
        */
        virtual void quit() {};

    protected:
        Engine2D &engine;
    };
}

#endif // D_GAME_2D_H
