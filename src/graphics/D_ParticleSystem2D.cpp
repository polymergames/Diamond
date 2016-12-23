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


// Particle system config

Diamond::ParticleSystem2DConfig::ParticleSystem2DConfig(const ConfigTable &configTable,
                                                        TextureFactory &textureFactory)
    : ParticleSystem2DConfig(configTable, textureFactory.loadTexture(configTable.get("particleTexture"))) {}

Diamond::ParticleSystem2DConfig::ParticleSystem2DConfig(const ConfigTable &configTable,
                                                        const SharedPtr<Texture> &particleTexture) 
    : particleTexture(particleTexture) {

    if (configTable.hasKey("particlePoolSize"))
        particlePoolSize = configTable.getInt("particlePoolSize");


    if (configTable.hasKey("minParticlesPerEmission"))
        minParticlesPerEmission = configTable.getInt("minParticlesPerEmission");

    if (configTable.hasKey("maxParticlesPerEmission"))
        maxParticlesPerEmission = configTable.getInt("maxParticlesPerEmission");


    if (configTable.hasKey("minEmitInterval"))
        minEmitInterval = configTable.getFloat("minEmitInterval");

    if (configTable.hasKey("maxEmitInterval"))
        maxEmitInterval = configTable.getFloat("maxEmitInterval");


    if (configTable.hasKey("minParticleLifeTime"))
        minParticleLifeTime = configTable.getFloat("minParticleLifeTime");

    if (configTable.hasKey("maxParticleLifeTime"))
        maxParticleLifeTime = configTable.getFloat("maxParticleLifeTime");


    if (configTable.hasKey("minEmitPointX"))
        minEmitPoint.x = configTable.getFloat("minEmitPointX");

    if (configTable.hasKey("minEmitPointY"))
        minEmitPoint.y = configTable.getFloat("minEmitPointY");


    if (configTable.hasKey("maxEmitPointX"))
        maxEmitPoint.x = configTable.getFloat("maxEmitPointX");

    if (configTable.hasKey("maxEmitPointY"))
        maxEmitPoint.y = configTable.getFloat("maxEmitPointY");


    if (configTable.hasKey("minEmitAngleDeg"))
        minEmitAngleDeg = configTable.getFloat("minEmitAngleDeg");

    if (configTable.hasKey("maxEmitAngleDeg"))
        maxEmitAngleDeg = configTable.getFloat("maxEmitAngleDeg");


    if (configTable.hasKey("minBirthRotation"))
        minBirthRotation = configTable.getFloat("minBirthRotation");

    if (configTable.hasKey("maxBirthRotation"))
        maxBirthRotation = configTable.getFloat("maxBirthRotation");


    if (configTable.hasKey("animateScale"))
        animateScale = configTable.getBool("animateScale");


    if (configTable.hasKey("minBirthScale"))
        minBirthScale = configTable.getFloat("minBirthScale");

    if (configTable.hasKey("maxBirthScale"))
        maxBirthScale = configTable.getFloat("maxBirthScale");


    if (configTable.hasKey("minDeathScale"))
        minDeathScale = configTable.getFloat("minDeathScale");

    if (configTable.hasKey("maxDeathScale"))
        maxDeathScale = configTable.getFloat("maxDeathScale");


    if (configTable.hasKey("minParticleSpeed"))
        minParticleSpeed = configTable.getFloat("minParticleSpeed");

    if (configTable.hasKey("maxParticleSpeed"))
        maxParticleSpeed = configTable.getFloat("maxParticleSpeed");


    if (configTable.hasKey("accelerate"))
        accelerate = configTable.getBool("accelerate");


    if (configTable.hasKey("minParticleAccelerationX"))
        minParticleAcceleration.x = configTable.getFloat("minParticleAccelerationX");

    if (configTable.hasKey("minParticleAccelerationY"))
        minParticleAcceleration.y = configTable.getFloat("minParticleAccelerationY");

    if (configTable.hasKey("maxParticleAccelerationX"))
        maxParticleAcceleration.x = configTable.getFloat("maxParticleAccelerationX");

    if (configTable.hasKey("maxParticleAccelerationY"))
        maxParticleAcceleration.y = configTable.getFloat("maxParticleAccelerationY");


    if (configTable.hasKey("minParticleAngularSpeed"))
        minParticleAngularSpeed = configTable.getFloat("minParticleAngularSpeed");

    if (configTable.hasKey("maxParticleAngularSpeed"))
        maxParticleAngularSpeed = configTable.getFloat("maxParticleAngularSpeed");


    if (configTable.hasKey("animateColor"))
        animateColor = configTable.getBool("animateColor");


    if (configTable.hasKey("minBirthColorR"))
        minBirthColor.r = configTable.getInt("minBirthColorR");

    if (configTable.hasKey("minBirthColorG"))
        minBirthColor.g = configTable.getInt("minBirthColorG");

    if (configTable.hasKey("minBirthColorB"))
        minBirthColor.b = configTable.getInt("minBirthColorB");

    if (configTable.hasKey("minBirthColorA"))
        minBirthColor.a = configTable.getInt("minBirthColorA");


    if (configTable.hasKey("maxBirthColorR"))
        maxBirthColor.r = configTable.getInt("maxBirthColorR");

    if (configTable.hasKey("maxBirthColorG"))
        maxBirthColor.g = configTable.getInt("maxBirthColorG");

    if (configTable.hasKey("maxBirthColorB"))
        maxBirthColor.b = configTable.getInt("maxBirthColorB");

    if (configTable.hasKey("maxBirthColorA"))
        maxBirthColor.a = configTable.getInt("maxBirthColorA");


    if (configTable.hasKey("minDeathColorR"))
        minDeathColor.r = configTable.getInt("minDeathColorR");

    if (configTable.hasKey("minDeathColorG"))
        minDeathColor.g = configTable.getInt("minDeathColorG");

    if (configTable.hasKey("minDeathColorB"))
        minDeathColor.b = configTable.getInt("minDeathColorB");

    if (configTable.hasKey("minDeathColorA"))
        minDeathColor.a = configTable.getInt("minDeathColorA");


    if (configTable.hasKey("maxDeathColorR"))
        maxDeathColor.r = configTable.getInt("maxDeathColorR");

    if (configTable.hasKey("maxDeathColorG"))
        maxDeathColor.g = configTable.getInt("maxDeathColorG");

    if (configTable.hasKey("maxDeathColorB"))
        maxDeathColor.b = configTable.getInt("maxDeathColorB");

    if (configTable.hasKey("maxDeathColorA"))
        maxDeathColor.a = configTable.getInt("maxDeathColorA");


    if (configTable.hasKey("emitOnWake"))
        emitOnWake = configTable.getBool("emitOnWake");
}


Diamond::ConfigTable Diamond::ParticleSystem2DConfig::genTable(const std::string &particleTexturePath) const {
    ConfigTable config;

    config.set("particlePoolSize", (int)particlePoolSize);


    config.set("particleTexture", particleTexturePath);


    config.set("minParticlesPerEmission", minParticlesPerEmission);
    config.set("maxParticlesPerEmission", maxParticlesPerEmission);


    config.set("minEmitInterval", minEmitInterval);
    config.set("maxEmitInterval", maxEmitInterval);


    config.set("minParticleLifeTime", (float)minParticleLifeTime);
    config.set("maxParticleLifeTime", (float)maxParticleLifeTime);


    config.set("minEmitPointX", minEmitPoint.x);
    config.set("minEmitPointY", minEmitPoint.y);


    config.set("maxEmitPointX", maxEmitPoint.x);
    config.set("maxEmitPointY", maxEmitPoint.y);


    config.set("minEmitAngleDeg", minEmitAngleDeg);
    config.set("maxEmitAngleDeg", maxEmitAngleDeg);


    config.set("minBirthRotation", minBirthRotation);
    config.set("maxBirthRotation", maxBirthRotation);


    config.set("animateScale", animateScale);


    config.set("minBirthScale", minBirthScale);
    config.set("maxBirthScale", maxBirthScale);

    config.set("minDeathScale", minDeathScale);
    config.set("maxDeathScale", maxDeathScale);


    config.set("minParticleSpeed", minParticleSpeed);
    config.set("maxParticleSpeed", maxParticleSpeed);


    config.set("accelerate", accelerate);


    config.set("minParticleAccelerationX", minParticleAcceleration.x);
    config.set("minParticleAccelerationY", minParticleAcceleration.y);

    config.set("maxParticleAccelerationX", maxParticleAcceleration.x);
    config.set("maxParticleAccelerationY", maxParticleAcceleration.y);


    config.set("minParticleAngularSpeed", minParticleAngularSpeed);
    config.set("maxParticleAngularSpeed", maxParticleAngularSpeed);


    config.set("animateColor", animateColor);


    config.set("minBirthColorR", minBirthColor.r);
    config.set("minBirthColorG", minBirthColor.g);
    config.set("minBirthColorB", minBirthColor.b);
    config.set("minBirthColorA", minBirthColor.a);

    config.set("maxBirthColorR", maxBirthColor.r);
    config.set("maxBirthColorG", maxBirthColor.g);
    config.set("maxBirthColorB", maxBirthColor.b);
    config.set("maxBirthColorA", maxBirthColor.a);

    config.set("minDeathColorR", minDeathColor.r);
    config.set("minDeathColorG", minDeathColor.g);
    config.set("minDeathColorB", minDeathColor.b);
    config.set("minDeathColorA", minDeathColor.a);
    
    config.set("maxDeathColorR", maxDeathColor.r);
    config.set("maxDeathColorG", maxDeathColor.g);
    config.set("maxDeathColorB", maxDeathColor.b);
    config.set("maxDeathColorA", maxDeathColor.a);


    config.set("emitOnWake", emitOnWake);

    return config;
}



// Particle system

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
    for (int i = 0; i < mParticles.size();) {
        if (!mParticles[i].isAlive(mTimeElapsed)) {

            // If the current particle is dead, it is replaced
            // by the last particle in the list, which is then destroyed.
            // This allows O(1) removal from the middle of the vector, at the
            // expense of changing the order of the vector. However, changing the order
            // is ok, and the iterator is not advanced in this case so that the
            // replacement particle now at this position can also be processed before moving on.

            if (mOnDestroyParticle)
                mOnDestroyParticle(mParticles[i], mConfig);

            if (i + 1 < mParticles.size())
                mParticles[i] = std::move(mParticles.back());

            mParticles.pop_back();
        }
        else {
            // lerp factor
            // auto lifeProgress = (mTimeElapsed - mParticles[i].mBirthTime) / (float)mParticles[i].mLifeTime;
            auto t = delta / (float)(mParticles[i].mDeathTime - mTimeElapsed + delta);

            if (mParticles[i].transform) {
                // animate scale
                if (mParticles[i].animateScale) {
                    // mParticles[i].transform->scale = Math::lerp(mParticles[i].startScale, mParticles[i].deathScale, lifeProgress);
                    mParticles[i].transform->scale = Math::lerp(mParticles[i].transform->scale, mParticles[i].deathScale, t);
                }

                // accelerate and move
                mParticles[i].velocity.add(delta * mParticles[i].acceleration);
                mParticles[i].transform->position.add(delta * mParticles[i].velocity);
                mParticles[i].transform->rotation += delta * mParticles[i].angularSpeed;
            }

            if (mParticles[i].animateColor && mParticles[i].renderComponent) {
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
        auto scale = Math::random(mConfig.minBirthScale, mConfig.maxBirthScale);
        particle.transform->scale.set(scale, scale);

        // particle's transform is relative to the particle system
        // this converts it to a world transform
        *particle.transform = Node2D::localToWorldSpace(*particle.transform, *mTransform, mTransMat);

        // scale animation
        if (mConfig.animateScale) {
            particle.animateScale = true;

            scale = Math::random(mConfig.minDeathScale, mConfig.maxDeathScale);
            particle.deathScale.set(scale, scale);

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
