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

#ifndef D_INPUT_H
#define D_INPUT_H

#include <vector>
#include "D_Vector2.h"

namespace Diamond {
    // TODO: turn into class!
    namespace Input {
        
        enum KEY {
            K_UNDEFINED, // location for when an undefined key is detected
            K_0, K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9,
            K_P0, K_P1, K_P2, K_P3, K_P4, K_P5, K_P6, K_P7, K_P8, K_P9,
            K_A, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M,
            K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z,
            K_SPACE, K_LCTRL, K_RCTRL, K_LALT, K_RALT, K_LSHIFT, K_RSHIFT, K_TAB, K_RETURN, K_ESCAPE,
            K_DOWN, K_LEFT, K_RIGHT, K_UP,
            NUMKEYS
        };
        
        extern std::vector<bool> keydown;
        extern std::vector<bool> keyup;
        
        extern bool touch_down, touch_drag, touch_up;
        extern Vector2<int> touch_pos; // using int instead of tD_pos to prevent bugs with SDL int parameters
        
        void resetKeyup();
    }
}

#endif // D_INPUT_H
