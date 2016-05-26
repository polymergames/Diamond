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

    typedef Diamond::SwapVector<Rigidbody2D> BodyList;
    typedef Diamond::SwapVector<std::unique_ptr<Collider2D> > ColliderList;
}

#endif // Q_TYPEDEFS_H
