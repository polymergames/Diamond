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

#include "D_ComponentNames.h"
#include "D_Input.h"
using namespace Diamond;

enum : RenderLayer { LOWEST, DEFAULT, HIGHER, HIGHEST } Layer;

RandomDemo::RandomDemo(Engine2D &engine, float movespeed, float spinspeed,
                       float growspeed)
    : Game2D(engine), movespeed(movespeed), spinspeed(spinspeed),
      growspeed(growspeed), root(engine.makeTransform()),
      spike(engine.makeTransform()), spike2(engine.makeTransform()),
      zapper(engine.makeTransform()), zapper2(engine.makeTransform()) {

  root.addChild(spike2);
  root.addChild(zapper2);
  zapper2.addChild(zapper);
  zapper2.addChild(spike);

  Renderer2D *renderer = engine.getRenderer();

  window = renderer->getResolution();
  Vector2<int> screen = renderer->getScreenResolution();
  std::cout << "Resolution: " << window.x << " by " << window.y << std::endl;
  std::cout << "Screen resolution: " << screen.x << " by " << screen.y
            << std::endl;

  spike_sprite = renderer->loadTexture("spike.png");
  cloud_sprite = renderer->loadTexture("cloud.png");
  zapper_sprite = renderer->loadTexture("zapper.png");

  if (!spike_sprite) {
    std::cout << "Couldn't load sprites!" << std::endl;
    engine.quit();
    return;
  }

  // spike.addComponent(makeShared<RenderComponent2D>(&spike, spike_sprite,
  // 0.1f));
  spike.addComponent(RENDERCOMPONENT,
                     renderer->makeRenderComponent(
                         spike.worldTransform(), spike_sprite.get(), HIGHEST));
  // spike.localTransform().position = Vector2<int>(-150, 200);
  spike.localTransform().position = Vector2<int>(-250, 400);
  spike.localTransform().scale = Vector2<float>(0.2f, 0.2f);
  if (!spike.getComponent(RENDERCOMPONENT)) {
    std::cout << "NULL render component!" << std::endl;
    engine.quit();
    return;
  }

  spike2.addComponent(RENDERCOMPONENT,
                      renderer->makeRenderComponent(
                          spike2.worldTransform(), spike_sprite.get(), HIGHER));
  spike2.localTransform().position = Vector2<int>(100, 100);
  spike2.localTransform().scale = Vector2<float>(0.1f, 0.1f);

  // Animations
  // TODO: these sprites are memory leaked
  zapper_anim.sprites.push_back(renderer->loadTexture("zapper1.png").get());
  zapper_anim.sprites.push_back(renderer->loadTexture("zapper2.png").get());
  zapper_anim.sprites.push_back(renderer->loadTexture("zapper3.png").get());
  zapper_anim.sprites.push_back(renderer->loadTexture("zapper4.png").get());

  zapper.addComponent(RENDERCOMPONENT,
                      renderer->makeRenderComponent(zapper.worldTransform(),
                                                    zapper_anim.sprites[0]));
  zapper.getComponent<RenderComponent2D>(RENDERCOMPONENT)->setLayer(DEFAULT);

  zapper.addComponent(
      ANIMATOR,
      new Animator2D(zapper.getComponent<RenderComponent2D>(RENDERCOMPONENT),
                     &zapper_anim));

  // zapper.localTransform().position = Vector2<int>(50, 100);
  zapper.localTransform().position = Vector2<int>(400, 220);

  zapper2_anim.sprite_sheet = zapper_sprite.get();
  // std::cout << "Zapper sheet is " << zapper2_anim.sprite_sheet->width << " by
  // " << zapper2_anim.sprite_sheet->height << std::endl;
  zapper2_anim.rows = 2;
  zapper2_anim.columns = 2;
  zapper2_anim.num_frames = 4;
  float z2scale = 0.5f;
  zapper2.addComponent(RENDERCOMPONENT, renderer->makeRenderComponent(
                                            zapper2.worldTransform(),
                                            zapper2_anim.sprite_sheet, LOWEST));

  zapper2.addComponent(
      ANIMATOR, new AnimatorSheet(
                    zapper2.getComponent<RenderComponent2D>(RENDERCOMPONENT),
                    &zapper2_anim));

  // zapper2.getComponent<RenderComponent2D>()->setPivot(Vector2<int>(zapper2_anim.sprite_sheet->getWidth()
  // * z2scale / (2 * zapper2_anim.columns),
  //    zapper2_anim.sprite_sheet->getHeight() * z2scale / (2 *
  //    zapper2_anim.rows)));
  // zapper2.localTransform().position = Vector2<int>(650, 200);
  zapper2.localTransform().position = Vector2<int>(600, 130);
  zapper2.localTransform().scale = Vector2<float>(z2scale, z2scale);

  haha = engine.getDJ()->loadSound("haha.wav");

  // Physics
  // body = Quantum2D::QuantumWorld2D::genRigidbody(spike.worldTransform());
  spikerb = engine.getPhysWorld()->makeRigidbody(spike.worldTransform());
  spike.addComponent(RIGIDBODY, spikerb);

  root.updateAllWorldTransforms();
}

void RandomDemo::update(tD_delta delta) {
  // Quantum2D::Rigidbody2D rbody =
  // Quantum2D::QuantumWorld2D::getRigidbody(body); std::cout << "Velocity: " <<
  // rbody.velocity.x << ", " << rbody.velocity.y << std::endl;

  // Coloring
  if (Input::keydown[Input::K_R]) {
    spike.getComponent<RenderComponent2D>(RENDERCOMPONENT)
        ->setColor({100, 0, 0});
  }
  if (Input::keydown[Input::K_G]) {
    spike.getComponent<RenderComponent2D>(RENDERCOMPONENT)
        ->setColor({100, 255, 50});
  }
  if (Input::keydown[Input::K_B]) {
    spike.getComponent<RenderComponent2D>(RENDERCOMPONENT)
        ->setColor({100, 0, 255});
  }
  if (Input::keydown[Input::K_T]) {
    spike.getComponent<RenderComponent2D>(RENDERCOMPONENT)->setColor({0, 0, 0});
  }
  if (Input::keyup[Input::K_Y]) {
    auto renderComp = spike.getComponent<RenderComponent2D>(RENDERCOMPONENT);
    renderComp->setAlpha(renderComp->getAlpha() - 32);
  }

  // Drawing
  auto renderer = engine.getRenderer();
  RGBA renderColor = {0, 255, 0, 255};

  renderer->renderPoint(spike.worldTransform().position, renderColor);
  renderer->renderPoint(spike2.worldTransform().position, renderColor);
  renderer->renderPoint(zapper.worldTransform().position, renderColor);
  renderer->renderPoint(zapper2.worldTransform().position, renderColor);

  renderer->renderLine(spike.worldTransform().position,
                       zapper2.worldTransform().position, renderColor);

  // Layer
  if (Input::keyup[Input::K_L]) {
    auto rcomp = zapper.getComponent<RenderComponent2D>(RENDERCOMPONENT);
    RenderLayer curLayer = rcomp->getLayer();
    if (curLayer == LOWEST) {
      rcomp->setLayer(HIGHEST);
    } else {
      rcomp->setLayer(LOWEST);
    }
  }

  // Sprite switching
  if (Input::keyup[Input::K_1]) {
    spike.getComponent<RenderComponent2D>(RENDERCOMPONENT)
        ->setSprite(spike_sprite);
  }
  if (Input::keyup[Input::K_2]) {
    spike.getComponent<RenderComponent2D>(RENDERCOMPONENT)
        ->setSprite(cloud_sprite);
  }

  // Visibility
  // TODO: implement visibility in renderer system, not in rendercomponent
  /*
  if (Input::keyup[Input::K_SPACE]) {
      zapper2.getComponent<RenderComponent2D>()->toggleVisibility();
  }*/

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
    zapper2.getComponent<RenderComponent2D>(RENDERCOMPONENT)->flipX();
  }
  if (Input::keyup[Input::K_UP]) {
    zapper2.getComponent<RenderComponent2D>(RENDERCOMPONENT)->flipY();
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
    spikerb->setVelocity(
        spikerb->getVelocity().add(Vector2<float>(-movespeed, 0)));
  }
  if (Input::keydown[Input::K_K]) {
    spikerb->setVelocity(
        spikerb->getVelocity().add(Vector2<float>(movespeed, 0)));
  }
  if (Input::keydown[Input::K_I]) {
    spikerb->setVelocity(
        spikerb->getVelocity().add(Vector2<float>(0, -movespeed)));
  }
  if (Input::keydown[Input::K_M]) {
    spikerb->setVelocity(
        spikerb->getVelocity().add(Vector2<float>(0, movespeed)));
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
    // std::cout << Input::touch_pos.x << ", " << Input::touch_pos.y <<
    // std::endl;
    clouds.emplace_back(engine.makeTransform());
    EntityNode2D *cloud = &(clouds.back());

    auto rcomp = engine.getRenderer()->makeRenderComponent(
        cloud->worldTransform(), cloud_sprite.get());
    cloud->addComponent(RENDERCOMPONENT, rcomp);
    rcomp->setLayer(DEFAULT);

    cloud->worldTransform().position = Input::touch_pos;
    cloud->worldTransform().scale = Vector2<float>(0.1f, 0.1f);

    spike.addChild(cloud);
  }

  // std::cout << "Delta = " << delta << "ms; FPS = " << Time::fps << std::endl;

  // update entities
  root.updateComponents(delta);
  spike.updateComponents(delta);
  spike2.updateComponents(delta);
  zapper.updateComponents(delta);
  zapper2.updateComponents(delta);

  root.updateAllWorldTransforms();
}

void RandomDemo::postPhysicsUpdate(tD_delta delta) {
  // Because physics engine externally changed world transforms,
  // we have to manually sync local transforms to the new world transforms.
  root.updateAllLocalTransforms();

  root.postPhysicsUpdateComponents(delta);
  spike.postPhysicsUpdateComponents(delta);
  spike2.postPhysicsUpdateComponents(delta);
  zapper.postPhysicsUpdateComponents(delta);
  zapper2.postPhysicsUpdateComponents(delta);

  root.updateAllWorldTransforms();
}

void RandomDemo::quit() {
  // free resources
  spike_sprite.free();
  cloud_sprite.free();
  zapper_sprite.free();
  haha.free();
};
