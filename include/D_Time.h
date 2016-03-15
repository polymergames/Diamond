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

#ifndef D_TIME_H
#define D_TIME_H

#include "D_typedefs.h"

namespace Diamond {
    class Timer;
    namespace Time {
        
        extern float fps;
        extern tD_delta delta;

        /**
         Returns the number of milliseconds elapsed since the game was launched.
        */
        tD_time msElapsed();

        /**
        Get the time in milliseconds since the last frame.
        */
        inline tD_delta getDelta() { return delta; }

        inline void setDelta(tD_delta d) { delta = d; }

        inline float getFPS() { return fps; }

        inline void setFPS(float f) { fps = f; }

        /**
         Called by Diamond launcher to set the platform-specific timing implementation.
        */
        void setTimer(Timer *timer);
    }
}

#endif // D_TIME_H
