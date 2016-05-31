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

#include <memory>
#include <stdint.h>
#include "duSparseVector.h"
#include "duTypedefs.h"
#include "D_Transform2.h"

// transform typedefs
using tD_pos =          tD_real;    // position coordinate type
using tD_rot =          tD_real;    // rotation value type

// ID/index typedefs
using transform2_id =   tD_id;      // 2d transform object id type


namespace Diamond {
    // Container for Transforms
    using TransformList = SparseVector<Transform2<tD_pos, tD_rot> >;


    // Smart pointer stuff

    template <typename T>
    using SharedPtr =       std::shared_ptr<T>;

    template<typename T, class... Args>
    inline SharedPtr<T> makeShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    // TODO: create a allocateShared function that uses std::allocate_shared and takes an Allocator argument. 
    // This can be used by Diamond systems with allocators for memory management.
}

#endif // D_TYPEDEFS_H