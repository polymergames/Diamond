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

#ifndef D_TYPEDEFS_H
#define D_TYPEDEFS_H

#include <stdint.h>

// transform typedefs
typedef int32_t tD_pos; // position coordinate type
typedef int64_t tD_long_pos; // long position coordinate type
typedef float tD_rot; // rotation value type

// time typedefs
typedef uint32_t tD_time; // time type
typedef int32_t tD_delta; // delta time type

// ID/index typedefs
typedef uint16_t tD_index; // array index type
typedef tD_index tD_id; // general identification type (ex. Entity ID)
typedef tD_id renderobj_id; // render object id type

namespace Diamond {
    const tD_index INVALID = 0xffff; // represents an invalid id or array index. can't use negative if tD_index is unsigned type
}

#endif // D_TYPEDEFS_H
