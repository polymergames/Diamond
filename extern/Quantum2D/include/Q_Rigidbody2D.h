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

#ifndef Q_RIGIDBODY_2D_H
#define Q_RIGIDBODY_2D_H

#include "duVector2.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    class Rigidbody2D {
    public:
        Rigidbody2D() : m_rotation(0), m_angVelocity(0) {}

        const Diamond::Vector2<tQ_pos>  &position() const { return m_position; }
        Diamond::Vector2<tQ_pos>        &position() { return m_position; }

        tQ_rot                          rotation() const { return m_rotation; }
        tQ_rot                          &rotation() { return m_rotation; }

        const Diamond::Vector2<tQ_pos>  &velocity() const { return m_velocity; }
        Diamond::Vector2<tQ_pos>        &velocity() { return m_velocity; }

        tQ_rot                          angVelocity() const { return m_angVelocity; }
        tQ_rot                          &angVelocity() { return m_angVelocity; }
        
        
        void update(tQ_delta delta) {
            integrate(delta);
        }
        
        void integrate(tQ_delta delta) {
            m_position += m_velocity * delta;
            m_rotation += m_angVelocity * delta;
        }

    private:
        Diamond::Vector2<tQ_pos> m_position;
        tQ_rot m_rotation;

        Diamond::Vector2<tQ_pos> m_velocity;
        tQ_rot m_angVelocity;
    };
}

#endif // Q_RIGIDBODY_2D_H
