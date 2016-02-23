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

#ifndef Q_COLLIDER2D_H
#define Q_COLLIDER2D_H

#include "Q_typedefs.h"

namespace Quantum2D {
	class Collider2D {
	public:
		Collider2D(collider2_id my_id, body2d_id body) : my_id(my_id), body(body) {};
		virtual ~Collider2D() {};
		
		collider2_id ID() {
			return my_id;
		}
		
	private:
		body2d_id body;
		collider2_id my_id;
	};
}

#endif // Q_COLLIDER2D_H
