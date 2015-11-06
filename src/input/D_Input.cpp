/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Input.h"

std::vector<bool> Diamond::Input::keydown(NUMKEYS, 0);
std::vector<bool> Diamond::Input::keyup(NUMKEYS, 0);

void Diamond::Input::reset_keyup() {
	std::fill(keyup.begin(), keyup.end(), 0);
}
