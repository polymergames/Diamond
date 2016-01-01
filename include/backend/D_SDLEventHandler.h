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

#ifndef D_SDL_EVENT_HANDLER_H
#define D_SDL_EVENT_HANDLER_H

#include <map>
#include "SDL.h"

#include "D_EventHandler.h"
#include "D_Input.h"

namespace Diamond {
	class SDLEventHandler : public EventHandler {
	public:
		SDLEventHandler();
		void update() override;

	private:
		std::map<SDL_Keycode, Input::KEY> keymap;
	};
}

#endif // D_SDL_EVENT_HANDLER_H

