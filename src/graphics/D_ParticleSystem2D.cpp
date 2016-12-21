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

#include "D_ParticleSystem2D.h"

#include "duMath.h"
#include "D_Node2D.h"

Diamond::ParticleSystem2D::ParticleSystem2D(const ParticleSystem2DConfig &config,
                                            const Transform2Ptr &transform,
                                            const InitSpawnFunc &initSpawnedParticle,
                                            const OnSpawnFunc &onSpawnParticle,
                                            const OnDestroyFunc &onDestroyParticle)
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



void Diamond::ParticleSystem2D::update(tD_delta delta) {
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

            if (mOnDestroyParticle)
                mOnDestroyParticle(*i, mConfig);

            if (i < mParticles.end() - 1)
                *i = std::move(mParticles.back());

            mParticles.pop_back();
        }
        else {
            // lerp factor
            // auto lifeProgress = (mTimeElapsed - i->mBirthTime) / (float)i->mLifeTime;
            auto t = delta / (float)(i->mDeathTime - mTimeElapsed + delta);

            if (i->transform) {
                // animate scale
                if (i->animateScale) {
                    // i->transform->scale = Math::lerp(i->startScale, i->deathScale, lifeProgress);
                    i->transform->scale = Math::lerp(i->transform->scale, i->deathScale, t);
                }

                // accelerate and move
                i->velocity.add(delta * i->acceleration);
                i->transform->position.add(delta * i->velocity);
                i->transform->rotation += delta * i->angularSpeed;
            }

            if (i->animateColor && i->renderComponent) {
                // TODO: lerp render component's color
            }

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



void Diamond::ParticleSystem2D::emitParticles() {
    auto numParticles = Math::random(mConfig.maxParticlesPerEmission, mConfig.maxParticlesPerEmission);

    // update the particle system's transformation matrix so it can be used to transform
    // the newly emitted particles.
    mTransMat = Math::transMat(
        (tD_real)Math::deg2rad(mTransform->rotation), 
        (tD_real)mTransform->scale.x, 
        (tD_real)mTransform->scale.y
    );

    // generate and initialize numParticles particles
    for (int i = 0; i < numParticles; ++i) {
        initParticle(generateParticle());
    }

    mLastParticleSpawnTime = mTimeElapsed;
}



Diamond::Particle2D &Diamond::ParticleSystem2D::generateParticle() {
    mParticles.emplace_back();
    return mParticles.back();
}



void Diamond::ParticleSystem2D::initParticle(Particle2D &particle) {
    // let user init particle (ie with transform, rendercomponent, and custom data)
    if (mInitSpawnedParticle)
        mInitSpawnedParticle(particle, mConfig);

    // life
    particle.mBirthTime = mTimeElapsed;
    particle.mDeathTime = mTimeElapsed + Math::random(
        (double)mConfig.minParticleLifeTime,
        (double)mConfig.maxParticleLifeTime
    );

    // transform
    if (particle.transform) {
        // position
        particle.transform->position.set(
            Math::random(mConfig.minEmitPoint.x, mConfig.maxEmitPoint.x),
            Math::random(mConfig.minEmitPoint.y, mConfig.maxEmitPoint.y)
        );

        // rotation
        particle.transform->rotation = 
            Math::random(mConfig.minBirthRotation, mConfig.maxBirthRotation);

        // scale
        particle.transform->scale.set(
            Math::random(mConfig.minBirthScale.x, mConfig.maxBirthScale.x),
            Math::random(mConfig.minBirthScale.y, mConfig.maxBirthScale.y)
        );

        // particle's transform is relative to the particle system
        // this converts it to a world transform
        *particle.transform = Node2D::localToWorldSpace(*particle.transform, *mTransform, mTransMat);

        // scale animation
        if (mConfig.animateScale) {
            particle.animateScale = true;

            particle.deathScale.set(
                Math::random(mConfig.minDeathScale.x, mConfig.maxDeathScale.x),
                Math::random(mConfig.minDeathScale.y, mConfig.maxDeathScale.y)
            );

            // convert particle system-local scale to world scale
            particle.deathScale = Node2D::localToWorldScale(particle.deathScale, mTransform->scale);
        }
        else {
            particle.deathScale = particle.transform->scale;
        }
        
    }

    // physics

    // point velocity right with magnitude particleSpeed, then rotate it by emitAngle
    particle.velocity.set(
        Math::random(mConfig.minParticleSpeed, mConfig.maxParticleSpeed), 0
    ).rotate(
        Math::deg2rad(Math::random(mConfig.minEmitAngleDeg, mConfig.maxEmitAngleDeg))
    );

    // transform the particle's local-space velocity by the rotation and scale of the particle system
    // (but not by translation, because this is velocity, shouldn't change with origin position)
    particle.velocity = Node2D::localToWorldSpace(particle.velocity, Vector2<tD_real>(0, 0), mTransMat);

    // same thing with acceleration
    particle.acceleration.set(
        Math::random(mConfig.minParticleAcceleration.x, mConfig.maxParticleAcceleration.x),
        Math::random(mConfig.minParticleAcceleration.y, mConfig.maxParticleAcceleration.y)
    );
    particle.acceleration = Node2D::localToWorldSpace(particle.acceleration, Vector2<tD_real>(0, 0), mTransMat);

    // angular speed
    particle.angularSpeed = Math::random(mConfig.minParticleAngularSpeed, mConfig.maxParticleAngularSpeed);

    // pretty colors!
    if (particle.renderComponent) {

        // TODO: initialize render component's color to birth color

        if (mConfig.animateColor) {
            particle.animateColor = true;

            particle.deathColor.r = (uint8_t)Math::random(mConfig.minDeathColor.r, mConfig.maxDeathColor.r);
            particle.deathColor.g = (uint8_t)Math::random(mConfig.minDeathColor.g, mConfig.maxDeathColor.g);
            particle.deathColor.b = (uint8_t)Math::random(mConfig.minDeathColor.b, mConfig.maxDeathColor.b);
            particle.deathColor.a = (uint8_t)Math::random(mConfig.minDeathColor.a, mConfig.maxDeathColor.a);
        }
        else {
            // TODO: set particle's death color to the render component's current color
        }
    }

    // user customization
    if (mOnSpawnParticle)
        mOnSpawnParticle(particle, mConfig);
}
