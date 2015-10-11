/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GAME_OBJECT_2D_H
#define GAME_OBJECT_2D_H

#include "Transform2.h"

namespace Diamond {
	class GameObject2D {
		public:
		GameObject2D();
		GameObject2D(Transform2 transform);
		Transform2 transform;
	};
}

#endif // GAME_OBJECT_2D_H
