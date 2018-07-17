#pragma once
#include "vector";
#include "duSwapVector.h"
#include "D_SDLRenderObj2D.h"


namespace Diamond {
	class SDLRenderObjectPool
	{
	public:
		std::vector<SwapVector<SDLRenderObj2D>> m_render_objects;


		SDLRenderObj2D &renderObj(RenderLayer layer,
			SDLrenderobj_id robj) {
			return m_render_objects[layer][robj];
		}

		const SDLRenderObj2D &renderObj(RenderLayer layer,
			SDLrenderobj_id robj) const {
			return m_render_objects[layer][robj];
		}

		void destroyRenderObj(RenderLayer layer,
			SDLrenderobj_id robj) {
			m_render_objects[layer].erase(robj);
		}

		SDLrenderobj_id changeLayer(RenderLayer curLayer,
			SDLrenderobj_id robj,
			RenderLayer newLayer) {
			// Make room for a new layer if necessary
			if (newLayer + 1 > m_render_objects.size()) {
				m_render_objects.resize(newLayer + 1);
			}

			SDLrenderobj_id newID = m_render_objects[newLayer].insert(
				std::move(m_render_objects[curLayer][robj]));
			m_render_objects[curLayer].erase(robj);

			return newID;
		}


		SDLRenderObjectPool() {}
		~SDLRenderObjectPool() {}
	};

}

