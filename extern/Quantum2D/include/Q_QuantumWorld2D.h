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

#ifndef Q_QUANTUM_WORLD_2D_H
#define Q_QUANTUM_WORLD_2D_H

#include <vector>

#include "D_Transform2.h"

#include "Q_RigidBody2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
	namespace QuantumWorld2D {
		
		extern std::vector<Diamond::Transform2<int, float>> transforms;
		extern std::vector<Quantum2D::Rigidbody2D> bodies;

		extern std::vector<tD_index> body_id_index_map;

		/**
		 Returns a reference to the transform with the given id.
		 Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
		 Only use this reference immediately after calling this function! (ie, call this function again every time you want access)
		*/
		inline Diamond::Transform2<int, float> &getTransform(transform2_id transform) {
			return transforms[transform];
		}
		
		/**
		 Returns a reference to the rigidbody with the given id.
		 Note: the reference returned is only guaranteed to be valid until the next time a new rigidbody is created.
		 Only use this reference immediately after calling this function! (ie, call this function again every time you want access)
		*/
		inline Rigidbody2D &getRigidbody(body2d_id body) {
			return bodies[body_id_index_map[body]];
		}
		
		/**
		 Creates a Transform2i object and returns its index in the transforms vector.
		*/
		transform2_id genTransform();
		
		/**
		 Frees the given index in transforms as available for a new Transform2i
		*/
		void freeTransform(transform2_id transform);
		
		/**
		 Creates a Rigidbody2D object attached to the given transform and returns its id.
		 The returned id can be used to access the rigidbody with getRigidbody().
		*/
		body2d_id genRigidbody(transform2_id transform);
		
		/**
		 Marks the given id as available for a new Rigidbody2D, and removes its currently associated rigidbody.
		*/
		void freeRigidbody(body2d_id body);
		
		
		/**
		 Steps the physics simulation by the number of milliseconds given.
		*/
		void step(int16_t delta_ms);
	}
}

#endif // Q_QUANTUM_WORLD_2D_H
