/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef TRANSFORM_2_H
#define TRANSFORM_2_H

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

#endif // TRANSFORM_2_H
