/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"

bool Diamond::Launcher::is_open = true;
std::unique_ptr<Diamond::Launcher> Diamond::Launcher::launcher;

Diamond::Launcher::~Launcher() {
}
