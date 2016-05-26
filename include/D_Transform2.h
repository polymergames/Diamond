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

#ifndef D_TRANSFORM_2_H
#define D_TRANSFORM_2_H

#include "duVector2.h"
#include "duTypedefs.h"

namespace Diamond {
    template <typename PTYPE, typename RTYPE, typename STYPE = tD_real>
    class Transform2 {
        public:
        Vector2<PTYPE> position;
        RTYPE rotation;
        Vector2<STYPE> scale;
        
        Transform2() : position(), rotation(), scale(1, 1) {}
        Transform2(const Vector2<PTYPE> &position) 
            : position(position), rotation(), scale(1, 1) {}
        Transform2(const Vector2<PTYPE> &position, RTYPE rotation)
            : position(position), rotation(rotation), scale(1, 1) {}
        Transform2(const Vector2<PTYPE> &position, RTYPE rotation, const Vector2<STYPE> &scale)
            : position(position), rotation(rotation), scale(scale) {}


        void reset() {
            position = Vector2<PTYPE>();
            rotation = RTYPE();
            scale = Vector2<STYPE>(1, 1);
        }

        // Conversion operator
        template <typename P, typename R, typename S>
        operator Transform2<P, R, S>() const { 
            return Transform2<P, R, S>(position, rotation, scale);
        }
    };
}

#endif // D_TRANSFORM_2_H
