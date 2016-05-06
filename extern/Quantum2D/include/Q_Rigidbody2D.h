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

#include "D_Vector2.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    class Rigidbody2D {
    public:
        Rigidbody2D() : rotation(0) {}

        const Diamond::Vector2<tQ_pos> &getPosition() const { return position; }
        Diamond::Vector2<tQ_pos> &getPosition() { return position; }
        void setPosition(const Diamond::Vector2<tQ_pos> &newpos) { position = newpos; }

        tQ_rot getRotation() const { return rotation; }
        tQ_rot &getRotation() { return rotation; }
        void setRotation(tQ_rot newrot) { rotation = newrot; }

        const Diamond::Vector2<tQ_pos> &getVelocity() const { return velocity; }
        Diamond::Vector2<tQ_pos> &getVelocity() { return velocity; }
        void setVelocity(const Diamond::Vector2<tQ_pos> &newvel) { velocity = newvel; }

    private:
        Diamond::Vector2<tQ_pos> position;
        tQ_rot rotation;
        Diamond::Vector2<tQ_pos> velocity;
    };
}

#endif // Q_RIGIDBODY_2D_H
