/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include <map>
#include "Input.h"
#include "SDL.h"

namespace Diamond {
    namespace SDLInput {
        extern std::map<SDL_Keycode, Input::KEY> keymap;
        void handle(SDL_Event &e);
    }
}

#endif // SDL_INPUT_H
