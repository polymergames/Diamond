/*
    Copyright 2016 Ahnaf Siddiqui

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

#include "ParticleDemo.h"

#include "D_Input.h"
using namespace Diamond;

ParticleDemo::ParticleDemo(Engine2D &engine, float movespeed, float spinspeed) 
    : Game2D(engine),
      movespeed(movespeed), spinspeed(spinspeed), again(false),
      configLoader(),
      textureFactory(engine.getRenderer()), 
      particleSystem(ParticleSystem2DConfig(configLoader.load(PARTICLE_CONFIG_FILE), textureFactory), 
                     engine.makeTransform(engine.getRenderer()->getResolution().scalar(0.5)),
                     [&] (Particle2D &particle, const ParticleSystem2DConfig &config) {
    auto transform = engine.makeTransform();
    particle.init(transform, engine.getRenderer()->makeRenderComponent(transform, config.particleTexture));
}) {}


void ParticleDemo::update(tD_delta delta) {
    // particle system movement
    if (Input::keydown[Input::K_W]) {
        particleSystem.transform().position.y -= movespeed * delta;
    }
    if (Input::keydown[Input::K_S]) {
        particleSystem.transform().position.y += movespeed * delta;
    }
    if (Input::keydown[Input::K_A]) {
        particleSystem.transform().position.x -= movespeed * delta;
    }
    if (Input::keydown[Input::K_D]) {
        particleSystem.transform().position.x += movespeed * delta;
    }

    // particle system rotation
    if (Input::keydown[Input::K_LEFT]) {
        particleSystem.transform().rotation -= spinspeed * delta;
    }
    if (Input::keydown[Input::K_RIGHT]) {
        particleSystem.transform().rotation += spinspeed * delta;
    }

    particleSystem.update(delta);

    // restart
    if (Input::keyup[Input::K_R])
    {
        again = true;
        engine.quit();
    }
}
