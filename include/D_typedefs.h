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
#include <vector>
#include "duTypedefs.h"
#include "duVector2.h"

// transform typedefs
using tD_pos =          tD_real;    // position coordinate type
using tD_rot =          tD_real;    // rotation value type


namespace Diamond {
    // Smart pointer stuff
    template <typename T>
    using SharedPtr =   std::shared_ptr<T>;

    template<typename T, class... Args>
    inline SharedPtr<T> makeShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    // TODO: create a allocateShared function that uses std::allocate_shared and takes an Allocator argument. 
    // This can be used by Diamond systems with allocators for memory management.


    // Transform typedefs for convenience
    template <typename P, typename R, typename S> class Transform2;

    using DTransform2 =         Transform2<tD_pos, tD_rot, tD_real>;
    using Transform2Ptr =       SharedPtr<DTransform2 >;
    using ConstTransform2Ptr =  SharedPtr<const DTransform2 >;
    
    using PointList2D = std::vector<Vector2<tD_pos> >;
}

#endif // D_TYPEDEFS_H
