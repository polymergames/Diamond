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

#include "D_Input.h"

std::vector<bool> Diamond::Input::keydown(NUMKEYS, 0);
std::vector<bool> Diamond::Input::keyup(NUMKEYS, 0);

bool Diamond::Input::touch_down = false;
bool Diamond::Input::touch_drag = false;
bool Diamond::Input::touch_up = false;

Diamond::Vector2<int> Diamond::Input::touch_pos;

void Diamond::Input::resetKeyup() {
	std::fill(keyup.begin(), keyup.end(), 0);
}
