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

#include "duMath.h"

Diamond::ParticleSystem::ParticleSystem(const ParticleSystemConfig &config,
                                        const ConstTransform2Ptr &transform,
                                        const SpawnFunc &spawnParticle,
                                        const DestroyFunc &destroyParticle)
    : mConfig(config),
      mTransform(transform), 
      mSpawnParticle(spawnParticle), 
      mDestroyParticle(destroyParticle), 
      mTimeElapsed(0), 
      mLastParticleSpawnTime(0) { 
    
    mParticles.reserve(config.particlePoolSize);

    mEmitInterval = Math::random(mConfig.minEmitInterval, mConfig.maxEmitInterval);

    // immediately emit some particles if configured to do so
    if (mConfig.emitOnWake)
        emitParticles();
}


void Diamond::ParticleSystem::update(tD_delta delta) {
    // do fancy particul effx!    

    // update particles based on the particle system's settings
    // and remove dead particles.
    for (auto i = mParticles.begin(); i != mParticles.end();) {
        if (!i->isAlive(mTimeElapsed)) {

            // If the current particle is dead, it is replaced
            // by the last particle in the list, which is then destroyed.
            // This allows O(1) removal from the middle of the vector, at the
            // expense of changing the order of the vector. However, changing the order
            // is ok, and the iterator is not advanced in this case so that the
            // replacement particle now at this position can also be processed before moving on.

            mDestroyParticle(*i);

            if (i < mParticles.end() - 1)
                *i = std::move(mParticles.back());

            mParticles.pop_back();
        }
        else {
            // TODO: update particle according to settings

            // since no particle has been removed in this case, 
            // we can advance the iterator. 
            ++i;
        }
    }

    // emit new particles
    if (mTimeElapsed - mLastParticleSpawnTime >= mEmitInterval) {
        emitParticles();
        mEmitInterval = Math::random(mConfig.minEmitInterval, mConfig.maxEmitInterval);
    }

    // update the time since the particle system was created
    mTimeElapsed += delta;
}


void Diamond::ParticleSystem::emitParticles() {
    Particle& particle = generateParticle(Math::random((double)mConfig.minParticleLifeTime, 
                                                       (double)mConfig.maxParticleLifeTime));
    initParticle(particle);
    mLastParticleSpawnTime = mTimeElapsed;
}

Diamond::Particle &Diamond::ParticleSystem::generateParticle(tD_time particleLifeTime) {
    mParticles.emplace_back(mSpawnParticle(mTimeElapsed, particleLifeTime));
    return mParticles.back();
}

void Diamond::ParticleSystem::initParticle(Particle &particle) {
    // TODO: set particle's transform, velocity, etc. according to settings
}
