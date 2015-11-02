/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_VECTOR_2_H
#define D_VECTOR_2_H

namespace Diamond {
	class Vector2 {
		public:
		float x, y;

		Vector2();
		Vector2(float x, float y);

		Vector2 &add(Vector2 b);
		Vector2 &sub(Vector2 b);
		Vector2 &scalar(float scalar);
	};
}

#endif // D_VECTOR_2_H
