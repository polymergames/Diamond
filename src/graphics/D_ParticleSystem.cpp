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
#include "D_Node2D.h"

Diamond::ParticleSystem::ParticleSystem(const ParticleSystemConfig &config,
                                        const InitSpawnFunc &initSpawnedParticle,
                                        const OnSpawnFunc &onSpawnParticle,
                                        const OnDestroyFunc &onDestroyParticle,
                                        const DTransform2 &transform)
    : mConfig(config),
      mTransform(transform),
      mInitSpawnedParticle(initSpawnedParticle),
      mOnSpawnParticle(onSpawnParticle),
      mOnDestroyParticle(onDestroyParticle),
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

    // update the time since the particle system was created
    mTimeElapsed += delta;

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

            mOnDestroyParticle(*i);

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

        // update the time interval until the next emission
        mEmitInterval = Math::random(mConfig.minEmitInterval, mConfig.maxEmitInterval);
    }
}


void Diamond::ParticleSystem::emitParticles() {
    auto numParticles = Math::random(mConfig.maxParticlesPerEmission, mConfig.maxParticlesPerEmission);

    // update the particle system's transformation matrix so it can be used to transform
    // the newly emitted particles.
    mTransMat = Math::transMat((tD_real)Math::deg2rad(mTransform.rotation), 
                               (tD_real)mTransform.scale.x, 
                               (tD_real)mTransform.scale.y);

    // generate and initialize numParticles particles
    for (int i = 0; i < numParticles; ++i) {
        initParticle(generateParticle());
    }

    mLastParticleSpawnTime = mTimeElapsed;
}

Diamond::Particle &Diamond::ParticleSystem::generateParticle() {
    mParticles.emplace_back();
    return mParticles.back();
}

void Diamond::ParticleSystem::initParticle(Particle &particle) {
    // life
    particle.mBirthTime = mTimeElapsed;
    particle.mLifeTime = Math::random((double)mConfig.minParticleLifeTime,
                                      (double)mConfig.maxParticleLifeTime);

    // transform
    if (particle.transform) {
        DTransform2 transform(
            // position
            Vector2<tD_pos>(Math::random(mConfig.minEmitPoint.x, mConfig.maxEmitPoint.x),
                            Math::random(mConfig.minEmitPoint.y, mConfig.maxEmitPoint.y)),
            // rotation
            Math::random(mConfig.minBirthRotation, mConfig.maxBirthRotation),
            // scale
            Vector2<tD_real>(Math::random(mConfig.minBirthScale.x, mConfig.maxBirthScale.x),
                             Math::random(mConfig.minBirthScale.y, mConfig.maxBirthScale.y))
        );

        // particle's transform is relative to the particle system
        // this converts it to a world transform
        *particle.transform = Node2D::localToWorldSpace(transform, mTransform, mTransMat);

        // death scale
        if (mConfig.animateScale) {            
            particle.deathScale.set(Math::random(mConfig.minDeathScale.x, mConfig.maxDeathScale.x),
                                    Math::random(mConfig.minDeathScale.y, mConfig.maxDeathScale.y));
        }
        else {
            particle.deathScale = particle.transform->scale;
        }
        // convert particle system-local scale to world scale
        particle.deathScale = Node2D::localToWorldScale(particle.deathScale, mTransform.scale);
    }

    // physics
    // TODO

    // user customization
    mOnSpawnParticle(particle);
}
