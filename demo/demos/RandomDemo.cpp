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
#include "D_World2D.h"
using namespace Diamond;

RandomDemo::RandomDemo(float movespeed, float spinspeed, float growspeed) 
    : movespeed(movespeed), spinspeed(spinspeed), growspeed(growspeed), 
      spike(nullptr), spike2(nullptr), zapper(nullptr), zapper2(nullptr) {}

void RandomDemo::init() {
    World2D *world = engine->getWorld();
    Renderer2D *renderer = engine->getRenderer();
    
    spike = world->createEntity("spike");
    spike2 = world->createEntity("spike2");
    zapper = world->createEntity("zapper");
    zapper2 = world->createEntity("zapper2");

    world->addEntity(spike2);
    world->addEntity(zapper2);
    zapper2->addChild(zapper);
    zapper2->addChild(spike);
    
    window = renderer->getResolution();

    Vector2<int> screen = renderer->getScreenResolution();
    std::cout << "Resolution: " << window.x << " by " << window.y << std::endl;
    std::cout << "Screen resolution: " << screen.x << " by " << screen.y << std::endl;

    spike_sprite = std::shared_ptr<Texture>(renderer->loadTexture("spike.png"));
    cloud_sprite = std::shared_ptr<Texture>(renderer->loadTexture("cloud.png"));

    if (!spike_sprite) {
        std::cout << "Couldn't load sprites!" << std::endl;
        engine->quit();
        return;
    }

    //spike.addComponent(new RenderComponent2D(&spike, spike_sprite, 0.1f));
    spike->addComponent<RenderComponent2D>(spike, renderer, spike_sprite, 0.1f);
    spike->setLocalPosition(Vector2<int>(-150, 200));
    if (!spike->getComponent<RenderComponent2D>()) {
        std::cout << "NULL!" << std::endl;
    }

    spike2->addComponent<RenderComponent2D>(spike2, renderer, spike_sprite, 0.1f);
    spike2->setLocalPosition(Vector2<int>(100, 100));

    // Animations
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper1.png")));
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper2.png")));
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper3.png")));
    zapper_anim.sprites.push_back(std::shared_ptr<Texture>(renderer->loadTexture("zapper4.png")));

    zapper->addComponent<RenderComponent2D>(zapper, renderer, zapper_anim.sprites[0], 0.5f);
    zapper->addComponent<Animator2D>(zapper->getComponent<RenderComponent2D>(), &zapper_anim);
    zapper->setLocalPosition(Vector2<int>(50, 100));

    zapper2_anim.sprite_sheet = std::shared_ptr<Texture>(renderer->loadTexture("zapper.png"));
    //std::cout << "Zapper sheet is " << zapper2_anim.sprite_sheet->width << " by " << zapper2_anim.sprite_sheet->height << std::endl;
    zapper2_anim.rows = 2;
    zapper2_anim.columns = 2;
    zapper2_anim.num_frames = 4;
    float z2scale = 0.5f;
    zapper2->addComponent<RenderComponent2D>(zapper2, renderer, zapper2_anim.sprite_sheet, z2scale);
    zapper2->addComponent(new AnimatorSheet(zapper2->getComponent<RenderComponent2D>(), &zapper2_anim));
    zapper2->getComponent<RenderComponent2D>()->setPivot(Vector2<int>(zapper2_anim.sprite_sheet->getWidth() * z2scale / (2 * zapper2_anim.columns), 
        zapper2_anim.sprite_sheet->getHeight() * z2scale / (2 * zapper2_anim.rows)));
    zapper2->setLocalPosition(Vector2<int>(650, 200));

    haha = std::unique_ptr<Sound2D>(engine->getDJ()->loadSound("haha.wav"));

    // Physics
    // body = Quantum2D::QuantumWorld2D::genRigidbody(spike.getTransformID());
    spike->addComponent<RigidbodyComponent2D>(spike, engine->getPhysWorld());
    spikerb = spike->getComponent<RigidbodyComponent2D>()->getBody();
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
        RGBA sc = spike->getComponent<RenderComponent2D>()->getSprite()->getColor();
        sc.a -= 32;
        spike_sprite->setColor(sc);
    }

    // Sprite switching
    if (Input::keyup[Input::K_1]) {
        spike->getComponent<RenderComponent2D>()->setSprite(spike_sprite);
    }
    if (Input::keyup[Input::K_2]) {
        spike->getComponent<RenderComponent2D>()->setSprite(cloud_sprite);
    }

    // Visibility
    if (Input::keyup[Input::K_SPACE]) {
        zapper2->getComponent<RenderComponent2D>()->toggleVisibility();
    }

    // Stretching
    if (Input::keydown[Input::K_LSHIFT]) {
        zapper2->getComponent<RenderComponent2D>()->setScale(zapper2->getComponent<RenderComponent2D>()->getScale() + growspeed * delta);
    }
    if (Input::keydown[Input::K_LCTRL]) {
        zapper2->getComponent<RenderComponent2D>()->setScale(zapper2->getComponent<RenderComponent2D>()->getScale() - growspeed * delta);
    }

    // Flipping and velocity
    if (Input::keyup[Input::K_DOWN]) {
        zapper2->getComponent<RenderComponent2D>()->flipX();
        // Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(0, -movespeed));
    }
    if (Input::keyup[Input::K_UP]) {
        zapper2->getComponent<RenderComponent2D>()->flipY();
        // Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(0, movespeed));
    }

    // Movement
    if (Input::keydown[Input::K_W]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x, pos.y - movespeed * delta));
    }
    if (Input::keydown[Input::K_S]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x, pos.y + movespeed * delta));
    }
    if (Input::keydown[Input::K_A]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x - movespeed * delta, pos.y));
    }
    if (Input::keydown[Input::K_D]) {
        Vector2<float> pos = zapper2->getLocalTransform().position;
        zapper2->setLocalPosition(Vector2<float>(pos.x + movespeed * delta, pos.y));
    }

    // Rotation and velocity
    if (Input::keydown[Input::K_LEFT]) {
        zapper2->setWorldRotation(zapper2->getWorldTransform().rotation - spinspeed * delta);
        // Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(-movespeed, 0));
    }
    if (Input::keydown[Input::K_RIGHT]) {
        zapper2->setWorldRotation(zapper2->getWorldTransform().rotation + spinspeed * delta);
        // Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(movespeed, 0));
    }

    // Velocity
    // TODO: use setVelocity
    if (Input::keyup[Input::K_P4]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(-movespeed, 0)));
    }
    if (Input::keyup[Input::K_P6]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(movespeed, 0)));
    }
    if (Input::keyup[Input::K_P2]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(0, movespeed)));
    }
    if (Input::keyup[Input::K_P8]) {
        spikerb->setVelocity(spikerb->getVelocity().add(Vector2<float>(0, -movespeed)));
    }

    // Sound
    if (Input::keyup[Input::K_F] && haha) {
        haha->play();
    }

    
    // Touch
    if (Input::touch_up) {
        //			std::cout << Input::touch_pos.x << ", " << Input::touch_pos.y << std::endl;
        Entity2D *spawn = engine->getWorld()->createEntity("cloud");
        spawn->addComponent(new RenderComponent2D(spawn, engine->getRenderer(), cloud_sprite, 0.1f));
        spawn->setLocalPosition(Input::touch_pos - spike->getWorldTransform().position);
        //engine->getWorld()->addEntity(spawn);
        spike->addChild(spawn);
    }

    //std::cout << "Delta = " << delta << "ms; FPS = " << Time::fps << std::endl;
}

void RandomDemo::quit() {};
