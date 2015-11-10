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

#ifndef D_TRANSFORM_2I_H
#define D_TRANSFORM_2I_H

#include "D_Vector2i.h"

namespace Diamond {
	class Transform2i {
		public:
		
		Vector2i position;
		Vector2i size;
		
		float rotation;
		
		Transform2i() : position(), size(1, 1), rotation(0) {}
		
		Transform2i(Vector2i position) : position(position), size(1, 1), rotation(0) {}
		
		Transform2i(Vector2i position, float rotation) : position(position), size(1, 1), rotation(rotation) {}
		
		Transform2i(Vector2i position, Vector2i size, float rotation) : position(position), size(size), rotation(rotation) {}
	};
}

#endif // D_TRANSFORM_2I_H
