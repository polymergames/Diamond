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

#ifndef D_RIGIDBODY_COMPONENT_2D_H
#define D_RIGIDBODY_COMPONENT_2D_H

#include "Q_QuantumWorld2D.h"
#include "Q_typedefs.h"

#include "D_Component.h"

namespace Diamond {
	class RigidbodyComponent2D : public Component {
	public:
		RigidbodyComponent2D(Entity2D *parent);
		~RigidbodyComponent2D();

		Diamond::Vector2<float> &getVelocity() {
			return Quantum2D::QuantumWorld2D::getRigidbody(body).getVelocity();
		}

	private:
		body2d_id body;
	};
}

#endif // D_DRIGIDBODY_2D_H

