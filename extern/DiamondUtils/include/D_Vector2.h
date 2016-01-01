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

#ifndef D_VECTOR_2_H
#define D_VECTOR_2_H

namespace Diamond {
	template <class T>
	class Vector2 {
		public:
		T x, y;

		Vector2() {}
		
		Vector2(T x, T y) : x(x), y(y) {}

		inline void set(T x, T y) {
			this->x = x, this->y = y;
		}

		inline Vector2 &add(Vector2 b) {
			x += b.x, y += b.y;
			return *this;
		}
		
		inline Vector2 &sub(Vector2 b) {
			x -= b.x, y -= b.y;
			return *this;
		}
		
		inline Vector2 &scalar(float scalar) {
			x *= scalar, y *= scalar;
			return *this;
		}
	};
}

#endif // D_VECTOR_2_H
