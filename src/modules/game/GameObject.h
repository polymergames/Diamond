/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Transform2.h"

namespace Diamond {
	class GameObject {
		public:
		GameObject();
		GameObject(Transform2 transform);
		Transform2 transform;
	};
}

#endif // GAME_OBJECT_H
