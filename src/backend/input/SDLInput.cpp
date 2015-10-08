/*
 Copyright (c) 2015 Polymer Games
 */

#include "SDLInput.h"
#include "Launcher.h"

void Diamond::SDLInput::handle(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        //
    }
    else if (e.type == SDL_QUIT) {
        Diamond::Launcher::is_open = false;
    }
}