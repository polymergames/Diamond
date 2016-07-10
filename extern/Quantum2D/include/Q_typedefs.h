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

#ifndef Q_TYPEDEFS_H
#define Q_TYPEDEFS_H

#include <stdint.h>
#include <memory>
#include "duMath.h"
#include "duSwapvector.h"
#include "duTypedefs.h"

// ID/index typedefs
typedef tD_id body2d_id; // 2d rigidbody object id type
typedef tD_id collider2_id; // 2d collider object id type

// typedefs used in physics data and calculations
typedef tD_real tQ_num;
typedef tQ_num tQ_pos;
typedef tQ_num tQ_rot;
typedef tQ_num tQ_delta;

namespace Quantum2D {
    class Rigidbody2D;
    class Collider2D;

    using BodyList = Diamond::SwapVector<Rigidbody2D>;
    using ColliderList = Diamond::SwapVector<std::unique_ptr<Collider2D> >;
    using PointList = std::vector<Diamond::Vector2<tQ_pos> >;
    
    // change based on the unit you are using for angles
    // ex. if you are storing radians in rigidbodies,
    // then this should just return its input rotation.
    // If you are storing degrees, this should convert the input
    // to radians.
    inline tQ_rot Qrot2rad(tQ_rot rot) { return Diamond::Math::deg2rad(rot); }
}

#endif // Q_TYPEDEFS_H
