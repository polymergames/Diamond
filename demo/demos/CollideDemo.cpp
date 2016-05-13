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
#include "D_ColliderComponent2D.h"
#include "D_Input.h"
#include "D_RenderComponent2D.h"
#include "D_RigidbodyComponent2D.h"
#include "D_World2D.h"
using namespace Diamond;

CollideDemo::CollideDemo(float movespeed) 
    : movespeed(movespeed), spike1(nullptr), spike2(nullptr), zapper1(nullptr), zapper2(nullptr) {
}

void CollideDemo::init() {
    World2D *world = engine->getWorld();
    Renderer2D *renderer = engine->getRenderer();

    spike1 = world->createEntity("spike1");
    spike2 = world->createEntity("spike2");
    zapper1 = world->createEntity("zapper1");
    zapper2 = world->createEntity("zapper2");

    world->addEntity(spike1);
    world->addEntity(spike2);
    world->addEntity(zapper1);
    world->addEntity(zapper2);

    std::shared_ptr<Texture> spike_sprite = std::shared_ptr<Texture>(renderer->loadTexture("spike.png"));
    
    if (!spike_sprite) {
        std::cout << "Couldn't load sprites!" << std::endl;
        engine->quit();
        return;
    }

    spike1->addComponent<RenderComponent2D>(spike1, renderer, spike_sprite);
    spike1->setLocalPosition(Vector2<int>(500, 400));
    spike1->setLocalScale(Vector2<float>(0.1f, 0.1f));

    spike2->addComponent<RenderComponent2D>(spike2, renderer, spike_sprite);
    spike2->setLocalPosition(Vector2<int>(900, 200));
    spike2->setLocalScale(Vector2<float>(0.1f, 0.1f));

    zapper_anim.sprite_sheet = std::shared_ptr<Texture>(renderer->loadTexture("zapper.png"));
    zapper_anim.rows = 2;
    zapper_anim.columns = 2;
    zapper_anim.num_frames = 4;

    zapper1->addComponent<RenderComponent2D>(zapper1, renderer, spike_sprite);
    zapper1->addComponent<AnimatorSheet>(zapper1->getComponent<RenderComponent2D>(), &zapper_anim);
    zapper1->setLocalPosition(Vector2<int>(300, 100));
    zapper1->setLocalScale(Vector2<float>(0.5f, 0.5f));

    zapper2->addComponent<RenderComponent2D>(zapper2, renderer, spike_sprite);
    zapper2->addComponent<AnimatorSheet>(zapper2->getComponent<RenderComponent2D>(), &zapper_anim);
    zapper2->setLocalPosition(Vector2<int>(700, 300));
    zapper2->setLocalScale(Vector2<float>(0.5f, 0.5f));

    // Setup physics
    PhysicsWorld2D *physworld = engine->getPhysWorld();
    std::function<void(void*)> callback = std::bind(&CollideDemo::m_onCollision, this, std::placeholders::_1);

    spike1->addComponent<RigidbodyComponent2D>(spike1, physworld);
    Rigidbody2D *rbody = spike1->getComponent<RigidbodyComponent2D>()->getBody();
    float scale = spike1->getLocalTransform().scale.x;
    tD_pos radius = spike_sprite->getWidth() * scale / 2.0;
    spike1->addComponent<ColliderComponent2D>(physworld->genCircleCollider(rbody, spike1, 
        callback, radius, Vector2<tD_pos>(radius, radius)), physworld);

    spike2->addComponent<RigidbodyComponent2D>(spike2, physworld);
    rbody = spike2->getComponent<RigidbodyComponent2D>()->getBody();
    scale = spike2->getLocalTransform().scale.x;
    radius = spike_sprite->getWidth() * scale / 2.0;
    spike2->addComponent<ColliderComponent2D>(physworld->genCircleCollider(rbody, spike2, 
        callback, radius, Vector2<tD_pos>(radius, radius)), physworld);

    zapper1->addComponent<RigidbodyComponent2D>(zapper1, physworld);
    rbody = zapper1->getComponent<RigidbodyComponent2D>()->getBody();
    float partial_width = zapper_anim.sprite_sheet->getWidth() / zapper_anim.columns / 5.0;
    scale = zapper1->getLocalTransform().scale.x;
    zapper1->addComponent<ColliderComponent2D>(physworld->genAABBCollider(rbody, zapper1, 
        callback, 
        Vector2<tD_pos>(partial_width * scale, zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale),
        Vector2<tD_pos>(2 * partial_width * scale, 0)), physworld);

    zapper2->addComponent<RigidbodyComponent2D>(zapper2, physworld);
    rbody = zapper2->getComponent<RigidbodyComponent2D>()->getBody();
    scale = zapper2->getLocalTransform().scale.x;
    zapper2->addComponent<ColliderComponent2D>(physworld->genAABBCollider(rbody, zapper2, 
        callback, 
        Vector2<tD_pos>(partial_width * scale, zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale),
        Vector2<tD_pos>(2 * partial_width * scale, 0)), physworld);
}

void CollideDemo::update(tD_delta delta) {
    // zapper1 controls
    if (Input::keydown[Input::K_W]) {
        Vector2<float> pos = zapper1->getLocalTransform().position;
        zapper1->setLocalPosition(Vector2<float>(pos.x, pos.y - movespeed * delta));
    }
    if (Input::keydown[Input::K_S]) {
        Vector2<float> pos = zapper1->getLocalTransform().position;
        zapper1->setLocalPosition(Vector2<float>(pos.x, pos.y + movespeed * delta));
    }
    if (Input::keydown[Input::K_A]) {
        Vector2<float> pos = zapper1->getLocalTransform().position;
        zapper1->setLocalPosition(Vector2<float>(pos.x - movespeed * delta, pos.y));
    }
    if (Input::keydown[Input::K_D]) {
        Vector2<float> pos = zapper1->getLocalTransform().position;
        zapper1->setLocalPosition(Vector2<float>(pos.x + movespeed * delta, pos.y));
    }

    // zapper2 controls
    if (Input::keydown[Input::K_UP]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x, pos.y - movespeed * delta));
    }
    if (Input::keydown[Input::K_DOWN]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x, pos.y + movespeed * delta));
    }
    if (Input::keydown[Input::K_LEFT]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x - movespeed * delta, pos.y));
    }
    if (Input::keydown[Input::K_RIGHT]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x + movespeed * delta, pos.y));
    }

    // spike2 controls
    if (Input::keydown[Input::K_P8]) {
        Vector2<float> pos = spike2->getLocalTransform().position;
        spike2->setLocalPosition(Vector2<float>(pos.x, pos.y - movespeed * delta));
    }
    if (Input::keydown[Input::K_P2]) {
        Vector2<float> pos = spike2->getLocalTransform().position;
        spike2->setLocalPosition(Vector2<float>(pos.x, pos.y + movespeed * delta));
    }
    if (Input::keydown[Input::K_P4]) {
        Vector2<float> pos = spike2->getLocalTransform().position;
        spike2->setLocalPosition(Vector2<float>(pos.x - movespeed * delta, pos.y));
    }
    if (Input::keydown[Input::K_P6]) {
        Vector2<float> pos = spike2->getLocalTransform().position;
        spike2->setLocalPosition(Vector2<float>(pos.x + movespeed * delta, pos.y));
    }
}

void CollideDemo::quit() {
    //
}

void CollideDemo::m_onCollision(void *other) {
    std::cout << "Hit by " << ((Entity2D*)other)->getName() << "!" << std::endl;
}

