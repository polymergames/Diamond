/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TRANSFORM_2_H
#define D_TRANSFORM_2_H

#include "Vector2.h"

namespace Diamond {
	class Transform2 {
		public:
		Transform2();
		Transform2(Vector2 position, float rotation, float scale);
		Vector2 position;
		float rotation;
		float scale;
	};
}

#endif // D_TRANSFORM_2_H
