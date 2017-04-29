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

#include <functional>
#include <unordered_map>
#include "SDL.h"

#include "D_EventHandler.h"
#include "D_Input.h"

namespace Diamond {
    class SDLEventHandler : public EventHandler {
    public:
        SDLEventHandler(const Vector2<int> &screenResolution,
                        const std::function<void(void)> &onQuit);
        
        void update() override;
        
        void setResolution(const Vector2<int> &screenResolution)
        { screen = screenResolution; }

    private:
        std::unordered_map<SDL_Keycode, Input::KEY> keymap;
        Vector2<int> screen;
        std::function<void(void)> onQuit;
    };
}

#endif // D_SDL_EVENT_HANDLER_H
