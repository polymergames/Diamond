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

#ifndef D_QUANTUM_BODY_2D_H
#define D_QUANTUM_BODY_2D_H

#include "D_Rigidbody2D.h"
#include "Q_QuantumWorld2D.h"

namespace Diamond {
    class QuantumBody2D : public DRigidbody2D {
    public:
        QuantumBody2D(transform2_id transform) {
            body = Quantum2D::QuantumWorld2D::genRigidbody(transform);
        }

        ~QuantumBody2D() {
            Quantum2D::QuantumWorld2D::freeRigidbody(body);
        }
        
        body2d_id getID() const { return body; }

        Vector2<tD_pos> getVelocity() override {
            return Quantum2D::QuantumWorld2D::getRigidbody(body).getVelocity();
        }

        void setVelocity(Vector2<tD_pos> &newvel) override {
            Quantum2D::QuantumWorld2D::getRigidbody(body).getVelocity() = newvel;
        }

    private:
        body2d_id body;
    };
}

#endif // D_QUANTUM_BODY_2D_H
