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
	template <typename T>
	class Vector2 {
		public:
		T x, y;

		Vector2() : x(), y() {}
		
		Vector2(T x, T y) : x(x), y(y) {}

		void set(T x, T y) {
			this->x = x, this->y = y;
		}

		Vector2 &add(const Vector2 &b) {
			x += b.x, y += b.y;
			return *this;
		}
		
		Vector2 &sub(const Vector2 &b) {
			x -= b.x, y -= b.y;
			return *this;
		}
		
		Vector2 &scalar(float scalar) {
			x *= scalar, y *= scalar;
			return *this;
		}

		// static functions

		template <typename A>
		static Vector2<T> scalar(const Vector2<A> &v, float scalar) {
			return Vector2<T>(v.x * scalar, v.y * scalar);
		}
	};
}

#endif // D_VECTOR_2_H
