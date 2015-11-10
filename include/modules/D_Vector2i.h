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

#ifndef D_VECTOR_2I_H
#define D_VECTOR_2I_H

namespace Diamond {
	class Vector2i {
		public:
		int x, y;

		Vector2i() : x(0), y(0) {}
		
		Vector2i(int x, int y) : x(x), y(y) {}

		inline Vector2i &add(Vector2i b) {
			x += b.x, y += b.y;
			return *this;
		}
		
		inline Vector2i &sub(Vector2i b) {
			x -= b.x, y -= b.y;
			return *this;
		}
		
		inline Vector2i &scalar(int scalar) {
			x *= scalar, y *= scalar;
			return *this;
		}
	};
}

#endif // D_VECTOR_2I_H
