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

#ifndef COLLIDE_DEMO_H
#define COLLIDE_DEMO_H

#include "D_AnimatorSheet.h"
#include "D_Entity2D.h"
#include "D_Game2D.h"

class CollideDemo : public Diamond::Game2D {
public:
    CollideDemo(float movespeed = 0.75f);

    void init() override;

    void update(tD_delta delta) override;

    void quit() override;

private:
    const float movespeed;

    Diamond::Entity2D spike1, spike2, zapper1, zapper2;
    Diamond::AnimationSheet zapper_anim;

    void m_onCollision(Diamond::Entity2D *other);
};

#endif // COLLIDE_DEMO_H
