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

#include "RandomDemo.h"

#include "D_Input.h"
#include "D_RenderComponent2D.h"
#include "D_RigidbodyComponent2D.h"
using namespace Diamond;

RandomDemo::RandomDemo(Engine2D &engine, float movespeed, float spinspeed, float growspeed) 
    : Game2D(engine), movespeed(movespeed), spinspeed(spinspeed), growspeed(growspeed), 
      root(engine.getTransformList()), 
      spike(engine.getTransformList()), 
      spike2(engine.getTransformList()), 
      zapper(engine.getTransformList()), 
      zapper2(engine.getTransformList()) {

    root.addChild(spike2);
    root.addChild(zapper2);
    zapper2.addChild(zapper);
    zapper2.addChild(spike);

    Renderer2D *renderer = engine.getRenderer();

    window = renderer->getResolution();
    Vector2<int> screen = renderer->getScreenResolution();
    std::cout << "Resolution: " << window.x << " by " << window.y << std::endl;
    std::cout << "Screen resolution: " << screen.x << " by " << screen.y << std::endl;

    spike_sprite = std::shared_ptr<Texture>(renderer->loadTexture("spike.png"));
    cloud_sprite = std::shared_ptr<Texture>(renderer->loadTexture("cloud.png"));

    if (!spike_sprite) {
        std::cout << "Couldn't load sprites!" << std::endl;
        engine.quit();
        return;
    }

    //spike.addComponent(new RenderComponent2D(&spike, spike_sprite, 0.1f));
    spike.addComponent<RenderComponent2D>(spike.getWorldTransformID(), renderer, spike_sprite);
    // spike.localTransform().position = Vector2<int>(-150, 200);
    spike.localTransform().position = Vector2<int>(-250, 400);
    spike.localTransform().scale = Vector2<float>(0.2f, 0.2f);
    if (!spike.getComponent<RenderComponent2D>()) {
        std::cout << "NULL!" << std::endl;
    }

    spike2.addComponent<RenderComponent2D>(spike2.getWorldTransformID(), renderer, spike_sprite);
    spike2.localTransform().position = Vector2<int>(100, 100);
    spike2.localTransform().scale = Vector2<float>(0.1f, 0.1f);

    // Animations
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper1.png")));
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper2.png")));
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper3.png")));
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper4.png")));

    zapper.addComponent<RenderComponent2D>(zapper.getWorldTransformID(), renderer, zapper_anim.sprites[0]);
    zapper.addComponent<Animator2D>(zapper.getComponent<RenderComponent2D>(), &zapper_anim);
    // zapper.localTransform().position = Vector2<int>(50, 100);
    zapper.localTransform().position = Vector2<int>(400, 220);

    zapper2_anim.sprite_sheet = std::shared_ptr<Texture>(renderer->loadTexture("zapper.png"));
    //std::cout << "Zapper sheet is " << zapper2_anim.sprite_sheet->width << " by " << zapper2_anim.sprite_sheet->height << std::endl;
    zapper2_anim.rows = 2;
    zapper2_anim.columns = 2;
    zapper2_anim.num_frames = 4;
    float z2scale = 0.5f;
    zapper2.addComponent<RenderComponent2D>(zapper2.getWorldTransformID(), renderer, zapper2_anim.sprite_sheet);
    zapper2.addComponent(new AnimatorSheet(zapper2.getComponent<RenderComponent2D>(), &zapper2_anim));
    //zapper2.getComponent<RenderComponent2D>()->setPivot(Vector2<int>(zapper2_anim.sprite_sheet->getWidth() * z2scale / (2 * zapper2_anim.columns), 
    //    zapper2_anim.sprite_sheet->getHeight() * z2scale / (2 * zapper2_anim.rows)));
    // zapper2.localTransform().position = Vector2<int>(650, 200);
    zapper2.localTransform().position = Vector2<int>(600, 130);
    zapper2.localTransform().scale = Vector2<float>(z2scale, z2scale);

    haha = std::unique_ptr<Sound2D>(engine.getDJ()->loadSound("haha.wav"));

    // Physics
    // body = Quantum2D::QuantumWorld2D::genRigidbody(spike.getWorldTransformID());
    spike.addComponent<RigidbodyComponent2D>(engine.getPhysWorld()->genRigidbody(spike.getWorldTransformID()), 
        engine.getPhysWorld());
    spikerb = spike.getComponent<RigidbodyComponent2D>()->getBody();

    root.updateAllWorldTransforms();
}


void RandomDemo::update(tD_delta delta) {
    // Quantum2D::Rigidbody2D rbody = Quantum2D::QuantumWorld2D::getRigidbody(body);
    // std::cout << "Velocity: " << rbody.velocity.x << ", " << rbody.velocity.y << std::endl;

    // Coloring
    if (Input::keydown[Input::K_R]) {
        spike_color = { 255, 0, 0, 255 };
        spike_sprite->setColor(spike_color);
    }
    if (Input::keydown[Input::K_T]) {
        spike_color = { 255, 255, 255, 255 };
        spike_sprite->setColor(spike_color);
    }
    if (Input::keyup[Input::K_Y]) {
        RGBA sc = spike.getComponent<RenderComponent2D>()->getSprite()->getColor();
        sc.a -= 32;
        spike_sprite->setColor(sc);
    }

    // Sprite switching
    if (Input::keyup[Input::K_1]) {
        spike.getComponent<RenderComponent2D>()->setSprite(spike_sprite);
    }
    if (Input::keyup[Input::K_2]) {
        spike.getComponent<RenderComponent2D>()->setSprite(cloud_sprite);
    }

    // Visibility
    if (Input::keyup[Input::K_SPACE]) {
        zapper2.getComponent<RenderComponent2D>()->toggleVisibility();
    }

    // Stretching
    if (Input::keydown[Input::K_LSHIFT]) {
        float ds = growspeed * delta;
        zapper2.localTransform().scale.x += ds;
        zapper2.localTransform().scale.y += ds;
    }
    if (Input::keydown[Input::K_LCTRL]) {
        float ds = growspeed * delta;
        zapper2.localTransform().scale.add(Vector2<float>(-ds, -ds));
    }

    // Flipping and velocity
    if (Input::keyup[Input::K_DOWN]) {
        zapper2.getComponent<RenderComponent2D>()->flipX();
    }
    if (Input::keyup[Input::K_UP]) {
        zapper2.getComponent<RenderComponent2D>()->flipY();
    }

    // Zapper movement
    if (Input::keydown[Input::K_W]) {
        zapper2.localTransform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_S]) {
        zapper2.localTransform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_A]) {
        zapper2.localTransform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_D]) {
        zapper2.localTransform().position.x += movespeed * delta;
    }

    // Zapper rotation
    if (Input::keydown[Input::K_LEFT]) {
        zapper2.localTransform().rotation -= spinspeed * delta;
    }
    if (Input::keydown[Input::K_RIGHT]) {
        zapper2.localTransform().rotation += spinspeed * delta;
    }

    // Spike rotation
    if (Input::keydown[Input::K_P7]) {
        spike.localTransform().rotation -= spinspeed * delta;
    }
    if (Input::keydown[Input::K_P9]) {
        spike.localTransform().rotation += spinspeed * delta;
    }

    // Spike velocity
    if (Input::keydown[Input::K_J]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(-movespeed, 0)));
    }
    if (Input::keydown[Input::K_K]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(movespeed, 0)));
    }
    if (Input::keydown[Input::K_I]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(0, -movespeed)));
    }
    if (Input::keydown[Input::K_M]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(0, movespeed)));
    }

    // Spike Movement
    if (Input::keydown[Input::K_P4]) {
        spike.localTransform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_P6]) {
        spike.localTransform().position.x += movespeed * delta;
    }
    if (Input::keydown[Input::K_P2]) {
        spike.localTransform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_P8]) {
        spike.localTransform().position.y -= movespeed * delta;
    }

    // Sound
    if (Input::keyup[Input::K_F] && haha) {
        haha->play();
    }

    
    // Touch
    if (Input::touch_up) {
        //			std::cout << Input::touch_pos.x << ", " << Input::touch_pos.y << std::endl;
        clouds.emplace_back(engine.getTransformList());
        EntityNode2D *cloud = &(clouds.back());
        cloud->addComponent(
            new RenderComponent2D(cloud->getWorldTransformID(), engine.getRenderer(), cloud_sprite)
        );
        cloud->worldTransform().position = Input::touch_pos;
        cloud->worldTransform().scale = Vector2<float>(0.1f, 0.1f);
        spike.addChild(cloud);
    }

    //std::cout << "Delta = " << delta << "ms; FPS = " << Time::fps << std::endl;

    root.updateAllWorldTransforms();
}

void RandomDemo::postPhysicsUpdate(tD_delta delta) {
    root.updateAllLocalTransforms();
    root.updateAllWorldTransforms();
}

void RandomDemo::quit() {};
