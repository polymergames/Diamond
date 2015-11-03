/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_RENDER_OBJ_2D_H
#define D_RENDER_OBJ_2D_H

#include "D_GameObject2D.h"

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
		virtual int is_flipped_x() const = 0;
		virtual int is_flipped_y() const = 0;

		virtual ~RenderObj2D();
	};
}

#endif // D_RENDER_OBJ_2D_H
