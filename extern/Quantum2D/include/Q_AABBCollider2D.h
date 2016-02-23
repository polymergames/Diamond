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
		Diamond::Vector2<int> min;
		Diamond::Vector2<int> max;
		
		AABBCollider2D(collider2_id my_id, body2d_id body, Diamond::Vector2<int> &min, Diamond::Vector2<int> &max);
	};
}

#endif // Q_AABB_COLLIDER_2D_H
