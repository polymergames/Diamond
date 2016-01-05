/*
	Copyright 2015 Ahnaf Siddiqui

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef D_ANIMATOR_2D_H
#define D_ANIMATOR_2D_H

#include "D_typedefs.h"
#include "D_Behavior.h"
#include "D_Animation2D.h"

namespace Diamond {
	class RenderComponent2D;
	class Animator2D : public Behavior {
	public:
		Animator2D(Entity2D *parent, Animation2D *anim);

		inline void setAnimation(Animation2D *anim) {
			this->anim = anim;
		}

		inline Animation2D *getAnimation() const {
			return anim;
		}

		void update(tD_delta delta) override;
	private:
		Animation2D *anim;
		RenderComponent2D *renderer;
		tD_index cur_frame;
		tD_delta elapsed;
	};
}

#endif // D_ANIMATOR_2D_H

