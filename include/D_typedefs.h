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
#include "duSparseVector.h"
#include "duTypedefs.h"
#include "D_Transform2.h"

// transform typedefs
typedef tD_real tD_pos; // position coordinate type
typedef tD_real tD_rot; // rotation value type
typedef int32_t tDrender_pos; // position coordinate type for rendering
typedef float tDrender_rot; // rotation value type for rendering

// ID/index typedefs
typedef tD_id renderobj_id; // render object id type
typedef tD_id transform2_id; // 2d transform object id type

namespace Diamond {
    typedef SparseVector<Transform2<tD_pos, tD_rot> > TransformList;
}

#endif // D_TYPEDEFS_H
