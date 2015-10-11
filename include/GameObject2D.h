/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GAME_OBJECT_2D_H
#define GAME_OBJECT_2D_H

#include <memory>
#include "Texture.h"
#include "Transform2.h"

namespace Diamond {
	class GameObject2D {
		public:
		GameObject2D();
		GameObject2D(std::shared_ptr<Texture> sprite, Transform2 transform);

		std::shared_ptr<Texture> sprite;
		Transform2 transform;
	};
}

#endif // GAME_OBJECT_2D_H
