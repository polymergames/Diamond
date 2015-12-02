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

#ifndef Q_RIGIDBODY_2D_H
#define Q_RIGIDBODY_2D_H

#include "D_Vector2i.h"

#include "Q_typedefs.h"

namespace Quantum2D {
	class Rigidbody2D {
		public:
		
		body2d_id body_id;
		transform2_id transform;
		
		
		Diamond::Vector2i velocity;
		
		
		Rigidbody2D(body2d_id body_id, transform2_id transform);
		
		
		void update(int16_t delta_ms);
	};
}

#endif // Q_RIGIDBODY_2D_H
