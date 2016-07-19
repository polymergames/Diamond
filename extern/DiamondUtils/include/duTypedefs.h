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

#ifndef DU_TYPEDEFS_H
#define DU_TYPEDEFS_H

#include <stdint.h>

typedef float tD_real; // real number type

// time typedefs
typedef uint32_t tD_time; // time type
typedef int32_t tD_delta; // delta time type

// ID/index typedefs
typedef uint32_t tD_index; // array index type
typedef tD_index tD_id; // general identification type

namespace Diamond {
    const tD_index INVALID = ~0; // represents an invalid id or array index.
    const tD_real EPS = 0.0001;
}

#endif // DU_TYPEDEFS_H
