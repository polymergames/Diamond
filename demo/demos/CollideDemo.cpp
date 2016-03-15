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

#include "CollideDemo.h"
#include "D_Graphics2D.h"
#include "D_Input.h"
#include "D_Launcher.h"
#include "D_RenderComponent2D.h"
#include "D_RigidbodyComponent2D.h"
#include "D_World2D.h"
#include "Q_AABBCollider2D.h"
using namespace Diamond;
using namespace Quantum2D;

CollideDemo::CollideDemo(float movespeed) : movespeed(movespeed) {
    Launcher::config.vsync = true;
}

void CollideDemo::init() {
    std::shared_ptr<Texture> spike_sprite = Graphics2D::loadTexture("spike.png");

    if (!spike_sprite) {
        std::cout << "Couldn't load sprites!" << std::endl;
        Launcher::quit();
        return;
    }

    // Setup entities
    spike.addComponent<RenderComponent2D>(&spike, spike_sprite, 0.1f);
    spike.setTransform(500, 400);
    World2D::addEntity(&spike);

    zapper_anim.sprite_sheet = Graphics2D::loadTexture("zapper.png");
    zapper_anim.rows = 2;
    zapper_anim.columns = 2;
    zapper_anim.num_frames = 4;

    zapper1.addBehavior<AnimatorSheet>(&zapper1, &zapper_anim);
    zapper1.getComponent<RenderComponent2D>()->setScale(0.5f);
    zapper1.setTransform(300, 100);
    World2D::addEntity(&zapper1);

    zapper2.addBehavior<AnimatorSheet>(&zapper2, &zapper_anim);
    zapper2.getComponent<RenderComponent2D>()->setScale(0.5f);
    zapper2.setTransform(700, 300);
    World2D::addEntity(&zapper2);

    // Setup physics
    float scale = spike.getComponent<RenderComponent2D>()->getScale();
    spike.addComponent<RigidbodyComponent2D>(&spike);
    spike_col = QuantumWorld2D::genCollider<AABBCollider2D>(spike.getComponent<RigidbodyComponent2D>()->getID(), 
        Vector2<tD_pos>(0, 0), Vector2<tD_pos>(spike_sprite->getWidth() * scale, spike_sprite->getHeight() * scale));

    scale = zapper1.getComponent<RenderComponent2D>()->getScale();
    zapper1.addComponent<RigidbodyComponent2D>(&zapper1);
    zapper1_col = QuantumWorld2D::genCollider<AABBCollider2D>(zapper1.getComponent<RigidbodyComponent2D>()->getID(),
        Vector2<tD_pos>(0, 0), Vector2<tD_pos>(zapper_anim.sprite_sheet->getWidth() / zapper_anim.columns * scale, 
        zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale));

    scale = zapper2.getComponent<RenderComponent2D>()->getScale();
    zapper2.addComponent<RigidbodyComponent2D>(&zapper2);
    zapper2_col = QuantumWorld2D::genCollider<AABBCollider2D>(zapper2.getComponent<RigidbodyComponent2D>()->getID(),
        Vector2<tD_pos>(0, 0), Vector2<tD_pos>(zapper_anim.sprite_sheet->getWidth() / zapper_anim.columns * scale,
        zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale));
}

void CollideDemo::update(tD_delta delta) {
    if (Input::keydown[Input::K_W]) {
        zapper1.getTransform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_S]) {
        zapper1.getTransform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_A]) {
        zapper1.getTransform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_D]) {
        zapper1.getTransform().position.x += movespeed * delta;
    }

    if (Input::keydown[Input::K_UP]) {
        zapper2.getTransform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_DOWN]) {
        zapper2.getTransform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_LEFT]) {
        zapper2.getTransform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_RIGHT]) {
        zapper2.getTransform().position.x += movespeed * delta;
    }
}

void CollideDemo::quit() {
    //
}
