/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef RENDER_OBJ_2D_H
#define RENDER_OBJ_2D_H

#include "GameObject2D.h"

namespace Diamond {
	class RenderObj2D {
		public:
		unsigned long index;
		GameObject2D *parent;
		Transform2 transform;

		RenderObj2D(GameObject2D *parent);

		virtual void set_texture(Texture *texture) = 0;

		virtual void flip_x() = 0;
		virtual void flip_y() = 0;
		virtual bool is_flipped_x() = 0;
		virtual bool is_flipped_y() = 0;

		virtual ~RenderObj2D();
	};
}

#endif // RENDER_OBJ_2D_H
