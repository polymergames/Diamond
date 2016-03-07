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

#ifndef Q_AABB_COLLIDER_2D_H
#define Q_AABB_COLLIDER_2D_H

#include "Q_Collider2D.h"

#include "D_Vector2.h"

namespace Quantum2D {
	class AABBCollider2D : public Collider2D {
	public:
		AABBCollider2D(body2d_id body, Diamond::Vector2<tD_pos> &origin, Diamond::Vector2<tD_pos> &dims);

        /**
         Get the current coordinates of this AABB's bottom left corner in world space.
        */
        const Diamond::Vector2<tD_pos> &getMin() const {
            return min;
        }

        /**
         Get the current coordinates of this AABB's top right corner in world space.
        */
        const Diamond::Vector2<tD_pos> &getMax() const {
            return max;
        }

        /**
         Get the origin point of this AABB in the parent transform's local space.
        */
        Diamond::Vector2<tD_pos> &getOrigin() { 
            return origin;
        };

        /**
         Get the horizontal x vertical dimensions of this AABB.
        */
        Diamond::Vector2<tD_pos> &getDims() {
            return dims;
        }

        /**
         Update world coordinates once per frame.
        */
        void update(tD_delta delta_ms) override;

    private:
        Diamond::Vector2<tD_pos> origin;
        Diamond::Vector2<tD_pos> dims;

        Diamond::Vector2<tD_pos> min;
        Diamond::Vector2<tD_pos> max;
	};
}

#endif // Q_AABB_COLLIDER_2D_H
