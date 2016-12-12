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

#include "D_ParticleSystem.h"

Diamond::ParticleSystem::ParticleSystem(const ParticleSystemDef &def,
                                        const ConstTransform2Ptr &transform,
                                        const SpawnFunc &spawnParticle,
                                        const DestroyFunc &destroyParticle)
    : mDef(def), 
      mTransform(transform), 
      mSpawnParticle(spawnParticle), 
      mDestroyParticle(destroyParticle), 
      mTimeElapsed(0) {};


void Diamond::ParticleSystem::update(tD_delta delta) {
    // do fancy particul effx!    

    // update particles based on the particle system's settings
    for (auto particle : mParticles) {
        // TODO
    }

    // TODO: only generate particles at certain times depending on settings
    Particle& particle = generateParticle(delta);
    initParticle(particle, delta);

    // remove dead particles.
    // assumes that particles are ordered from oldest to newest
    // and all have the same lifetime.
    // TODO: consider non-consistent lifetimes? ex. what if each particle has a random lifetime?
    while (!mParticles.front().isAlive(mTimeElapsed)) {
        mParticles.pop_front();
    }

    mTimeElapsed += delta;
}


Diamond::Particle &Diamond::ParticleSystem::generateParticle(tD_delta delta) {
    mParticles.emplace_back(mSpawnParticle());
    return mParticles.back();
}

void Diamond::ParticleSystem::initParticle(Particle &particle, tD_delta delta) {
    // TODO: set particle's transform, velocity, etc. according to settings
}
