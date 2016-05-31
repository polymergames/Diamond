/*
    Copyright 2016 Ahnaf Siddiqui
 
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

#ifndef D_SDL_TYPEDEFS_H
#define D_SDL_TYPEDEFS_H

#include "duSwapVector.h"
#include "D_typedefs.h"

namespace Diamond {
    // transform typedefs
    using tSDLrender_pos =  int32_t;    // position coordinate type for rendering
    using tSDLrender_rot =  float;      // rotation value type for rendering

    // ID/index typedefs
    using SDLrenderobj_id = tD_id;      // render object id type


    // Container for render objects
    class SDLRenderObj2D;
    using SDLRenderObjList = SwapVector<SDLRenderObj2D>;
}

#endif // D_SDL_TYPEDEFS_H
