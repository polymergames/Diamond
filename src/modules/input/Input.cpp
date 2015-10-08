/*
 Copyright (c) 2015 Polymer Games
 */

#include "Input.h"

std::vector<bool> Diamond::Input::keydown(NUMKEYS, 0);
std::vector<bool> Diamond::Input::keyup(NUMKEYS, 0);

void Diamond::Input::reset() {
    std::fill(keydown.begin(), keydown.end(), 0);
    std::fill(keyup.begin(), keyup.end(), 0);
}