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
#include "D_ComponentNames.h"
#include "D_Input.h"

#include "Q_DynamicWorld2D.h"
#include "Q_PolyCollider.h"
using namespace Diamond;

CollideDemo::CollideDemo(Engine2D &engine, float movespeed) 
    : Game2D(engine), movespeed(movespeed), 
      spike1(engine.makeTransform()),
      spike2(engine.makeTransform()), 
      zapper1(engine.makeTransform()), 
      zapper2(engine.makeTransform()),
      indicator_spike(engine.makeTransform()),
      m_debug(engine.getRenderer()) {
    Renderer2D *renderer = engine.getRenderer();

    SharedPtr<Texture> spike_sprite = renderer->loadTexture("spike.png");
    
    if (!spike_sprite) {
        std::cout << "Couldn't load sprites!" << std::endl;
        engine.quit();
        return;
    }
          
    Vector2<int> window = renderer->getResolution();

    spike1.addComponent(RENDERCOMPONENT, 
        renderer->makeRenderComponent(spike1.transform(), spike_sprite));
    spike1.transform().position = Vector2<int>(500, 400);
    spike1.transform().scale = Vector2<float>(SPIKE_SCALE, SPIKE_SCALE);

    spike2.addComponent(RENDERCOMPONENT, 
        renderer->makeRenderComponent(spike2.transform(), spike_sprite));
    spike2.transform().position = Vector2<int>(900, 200);
    spike2.transform().scale = Vector2<float>(SPIKE_SCALE, SPIKE_SCALE);

    float spike_pivot = spike_sprite->getWidth() * SPIKE_SCALE / 2.0f;
    indicator_spike.addComponent(RENDERCOMPONENT,
    renderer->makeRenderComponent(indicator_spike.transform(),
                                  spike_sprite,
                                  0,
                                  Vector2<float>(spike_pivot, spike_pivot)));
    indicator_spike.transform().position = Vector2<int>(window.x - 100, 100);
    indicator_spike.transform().scale = Vector2<float>(SPIKE_SCALE, SPIKE_SCALE);
          
    zapper_anim.sprite_sheet = renderer->loadTexture("zapper.png");
    zapper_anim.rows = 2;
    zapper_anim.columns = 2;
    zapper_anim.num_frames = 4;

    zapper1.addComponent(RENDERCOMPONENT, 
        renderer->makeRenderComponent(zapper1.transform(), spike_sprite));
    zapper1.addComponent(ANIMATOR, 
        makeShared<AnimatorSheet>(zapper1.getComponent<RenderComponent2D>(RENDERCOMPONENT), &zapper_anim));
    zapper1.transform().position = Vector2<int>(300, 100);
    zapper1.transform().scale = Vector2<float>(ZAPPER_SCALE, ZAPPER_SCALE);

    zapper2.addComponent(RENDERCOMPONENT, 
        renderer->makeRenderComponent(zapper2.transform(), spike_sprite));
    zapper2.addComponent(ANIMATOR, 
        makeShared<AnimatorSheet>(zapper2.getComponent<RenderComponent2D>(RENDERCOMPONENT), &zapper_anim));
    zapper2.transform().position = Vector2<int>(700, 300);
    zapper2.transform().scale = Vector2<float>(ZAPPER_SCALE, ZAPPER_SCALE);

    // Setup physics
    PhysicsWorld2D *physworld = engine.getPhysWorld();
    std::function<void(void*)> callback = std::bind(&CollideDemo::m_onCollision, this, std::placeholders::_1);

    SharedPtr<Rigidbody2D> rbody = physworld->makeRigidbody(spike1.transform());
    spike1.addComponent(RIGIDBODY, rbody);

    float scale = spike1.transform().scale.x;
    tD_pos radius = spike_sprite->getWidth() * scale / 2.0;
    spike1.addComponent(COLLIDER, 
        physworld->makeCircleCollider(rbody, &spike1, callback, radius, Vector2<tD_pos>(radius, radius)));

    rbody = physworld->makeRigidbody(spike2.transform());
    spike2.addComponent(RIGIDBODY, rbody);
    scale = spike2.transform().scale.x;
    radius = spike_sprite->getWidth() * scale / 2.0;
    spike2.addComponent(COLLIDER, 
        physworld->makeCircleCollider(rbody, &spike2, callback, radius, Vector2<tD_pos>(radius, radius)));

    
    scale = zapper1.transform().scale.x;
    // using partial width because the sprite file is 5 times as wide as the actual zapper sprite
    float partial_width = zapper_anim.sprite_sheet->getWidth() / zapper_anim.columns / 5.0;
          
    PointList2D zapperColPoints;
    
    float zheight = zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale;
    zapperColPoints.push_back(Vector2<float>(2 * partial_width * scale, 0));
    zapperColPoints.push_back(Vector2<float>(3 * partial_width * scale, 0));
    zapperColPoints.push_back(Vector2<float>(5 * partial_width * scale, zheight / 2.0));
    zapperColPoints.push_back(Vector2<float>(3 * partial_width * scale, zheight));
    zapperColPoints.push_back(Vector2<float>(2 * partial_width * scale, zheight));
    zapperColPoints.push_back(Vector2<float>(0, zheight / 2.0));
    
    ptrZapperPolyPoints = physworld->makePolyColPoints(zapperColPoints);
          
    rbody = physworld->makeRigidbody(zapper1.transform());
    zapper1.addComponent(RIGIDBODY, rbody);
    /*
    zapper1.addComponent(COLLIDER, 
        physworld->makeAABBCollider(rbody, &zapper1, callback, 
        Vector2<tD_pos>(partial_width * scale, zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale),
        Vector2<tD_pos>(2 * partial_width * scale, 0)));
    */
    zapper1.addComponent(COLLIDER,
                         physworld->makePolyCollider(rbody, &zapper1, callback, ptrZapperPolyPoints));

    rbody = physworld->makeRigidbody(zapper2.transform());
    zapper2.addComponent(RIGIDBODY, rbody);
    /*
    zapper2.addComponent(COLLIDER,
        physworld->makeAABBCollider(rbody, &zapper2, callback, 
        Vector2<tD_pos>(partial_width * scale, zapper_anim.sprite_sheet->getHeight() / zapper_anim.rows * scale),
        Vector2<tD_pos>(2 * partial_width * scale, 0)));
    */
    zapper2.addComponent(COLLIDER,
                         physworld->makePolyCollider(rbody, &zapper2, callback, ptrZapperPolyPoints));
}

void CollideDemo::update(tD_delta delta) {
    // draw colliders
    m_debug.draw(zapper1.getComponent<PolyCollider>(COLLIDER), colliderColor);
    m_debug.draw(zapper2.getComponent<PolyCollider>(COLLIDER), colliderColor);
    
    // zapper1 controls
    if (Input::keydown[Input::K_W]) {
        zapper1.transform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_S]) {
        zapper1.transform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_A]) {
        zapper1.transform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_D]) {
        zapper1.transform().position.x += movespeed * delta;
    }
    if (Input::keydown[Input::K_1]) {
        zapper1.transform().rotation -= spinspeed * delta;
    }
    if (Input::keydown[Input::K_2]) {
        zapper1.transform().rotation += spinspeed * delta;
    }

    // zapper2 controls
    if (Input::keydown[Input::K_UP]) {
        zapper2.transform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_DOWN]) {
        zapper2.transform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_LEFT]) {
        zapper2.transform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_RIGHT]) {
        zapper2.transform().position.x += movespeed * delta;
    }
    if (Input::keydown[Input::K_3]) {
        zapper2.transform().rotation -= spinspeed * delta;
    }
    if (Input::keydown[Input::K_4]) {
        zapper2.transform().rotation += spinspeed * delta;
    }

    // spike2 controls
    if (Input::keydown[Input::K_P8]) {
        spike2.transform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_P2]) {
        spike2.transform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_P4]) {
        spike2.transform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_P6]) {
        spike2.transform().position.x += movespeed * delta;
    }


    // update entities
    spike1.updateComponents(delta);
    spike2.updateComponents(delta);
    zapper1.updateComponents(delta);
    zapper2.updateComponents(delta);
}

void CollideDemo::quit() {
    //
}

void CollideDemo::m_onCollision(void *other) {
    indicator_spike.transform().rotation += 5;
    
    std::cout << "Hit by " << other << std::endl;
}

