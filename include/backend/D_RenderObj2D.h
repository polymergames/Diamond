/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_RENDER_OBJ_2D_H
#define D_RENDER_OBJ_2D_H

#include "D_GameObject2D.h"
#include "D_Texture.h"
#include "D_Transform2.h"

namespace Diamond {

	class RenderObj2D {
		public:
		unsigned long index;
		GameObject2D *parent;
		Transform2 transform;

		RenderObj2D(GameObject2D *parent);

		virtual void setTexture(Texture *texture) = 0;

		virtual void flipX() = 0;
		virtual void flipY() = 0;
		virtual int isFlippedX() const = 0;
		virtual int isFlippedY() const = 0;

		virtual ~RenderObj2D();
	};
}

#endif // D_RENDER_OBJ_2D_H
