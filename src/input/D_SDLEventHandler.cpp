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

#include "D_Log.h"
#include "D_Renderer2D.h"
#include "D_SDLEventHandler.h"

Diamond::SDLEventHandler::SDLEventHandler(const Vector2<int> &screenResolution,
                                          const std::function<void(void)> &onQuit)
    : screen(screenResolution), onQuit(onQuit) {
    keymap = {
        { SDLK_0, Input::K_0 },
        { SDLK_1, Input::K_1 },
        { SDLK_2, Input::K_2 },
        { SDLK_3, Input::K_3 },
        { SDLK_4, Input::K_4 },
        { SDLK_5, Input::K_5 },
        { SDLK_6, Input::K_6 },
        { SDLK_7, Input::K_7 },
        { SDLK_8, Input::K_8 },
        { SDLK_9, Input::K_9 },
        { SDLK_KP_0, Input::K_P0 },
        { SDLK_KP_1, Input::K_P1 },
        { SDLK_KP_2, Input::K_P2 },
        { SDLK_KP_3, Input::K_P3 },
        { SDLK_KP_4, Input::K_P4 },
        { SDLK_KP_5, Input::K_P5 },
        { SDLK_KP_6, Input::K_P6 },
        { SDLK_KP_7, Input::K_P7 },
        { SDLK_KP_8, Input::K_P8 },
        { SDLK_KP_9, Input::K_P9 },
        { SDLK_a, Input::K_A },
        { SDLK_b, Input::K_B },
        { SDLK_c, Input::K_C },
        { SDLK_d, Input::K_D },
        { SDLK_e, Input::K_E },
        { SDLK_f, Input::K_F },
        { SDLK_g, Input::K_G },
        { SDLK_h, Input::K_H },
        { SDLK_i, Input::K_I },
        { SDLK_j, Input::K_J },
        { SDLK_k, Input::K_K },
        { SDLK_l, Input::K_L },
        { SDLK_m, Input::K_M },
        { SDLK_n, Input::K_N },
        { SDLK_o, Input::K_O },
        { SDLK_p, Input::K_P },
        { SDLK_q, Input::K_Q },
        { SDLK_r, Input::K_R },
        { SDLK_s, Input::K_S },
        { SDLK_t, Input::K_T },
        { SDLK_u, Input::K_U },
        { SDLK_v, Input::K_V },
        { SDLK_w, Input::K_W },
        { SDLK_x, Input::K_X },
        { SDLK_y, Input::K_Y },
        { SDLK_z, Input::K_Z },
        { SDLK_SPACE, Input::K_SPACE },
        { SDLK_LCTRL, Input::K_LCTRL },
        { SDLK_RCTRL, Input::K_RCTRL },
        { SDLK_LALT, Input::K_LALT },
        { SDLK_RALT, Input::K_RALT },
        { SDLK_LSHIFT, Input::K_LSHIFT },
        { SDLK_RSHIFT, Input::K_RSHIFT },
        { SDLK_TAB, Input::K_TAB },
        { SDLK_RETURN, Input::K_RETURN },
        { SDLK_ESCAPE, Input::K_ESCAPE },
        { SDLK_DOWN, Input::K_DOWN },
        { SDLK_LEFT, Input::K_LEFT },
        { SDLK_RIGHT, Input::K_RIGHT },
        { SDLK_UP, Input::K_UP },
    };
}

void Diamond::SDLEventHandler::update() {
    Input::resetKeyup();
    Input::touch_down = false;
    Input::touch_drag = false;
    Input::touch_up = false;

    // TODO: try using SDL get state for keys instead of event polling
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_KEYDOWN:
            Input::keydown[keymap[e.key.keysym.sym]] = true;
            break;
        case SDL_KEYUP:
            Input::keyup[keymap[e.key.keysym.sym]] = true;
            Input::keydown[keymap[e.key.keysym.sym]] = false;
            break;
        case SDL_FINGERDOWN:
            Input::touch_down = true;
            Input::touch_pos.set(e.tfinger.x * screen.x, e.tfinger.y * screen.y);
            // DEBUG
//#ifdef __ANDROID__
//            __android_log_print(ANDROID_LOG_VERBOSE,
//                                "POLYMER", "Finger pos x: %f y: %f\n", e.tfinger.x, e.tfinger.y);
//            __android_log_print(ANDROID_LOG_VERBOSE,
//                                "POLYMER", "Screen x: %d y: %d\n", screen.x, screen.y);
//            __android_log_print(ANDROID_LOG_VERBOSE,
//                                "POLYMER", "Touch pos x: %d y: %d\n", Input::touch_pos.x, Input::touch_pos.y);
//#endif
            break;
        case SDL_FINGERMOTION:
            Input::touch_drag = true;
            Input::touch_pos.set(e.tfinger.x * screen.x, e.tfinger.y * screen.y);
            break;
        case SDL_FINGERUP:
            Input::touch_up = true;
            Input::touch_pos.set(e.tfinger.x * screen.x, e.tfinger.y * screen.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            Input::touch_down = true;
            SDL_GetMouseState(&(Input::touch_pos.x), &(Input::touch_pos.y));
            break;
        case SDL_MOUSEBUTTONUP:
            Input::touch_up = true;
            SDL_GetMouseState(&(Input::touch_pos.x), &(Input::touch_pos.y));
            break;
        case SDL_QUIT:
            if (onQuit) onQuit();
            break;
        }
    }
}
