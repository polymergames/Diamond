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

#ifndef D_PARTICLE_SYSTEM_H
#define D_PARTICLE_SYSTEM_H

#include <functional>
#include <vector>
#include "D_Component.h"
#include "D_Node2D.h"
#include "D_RenderComponent2D.h"
#include "D_Rigidbody2D.h"
#include "D_Timer.h"
#include "D_Transform2.h"
#include "D_typedefs.h"

namespace Diamond {

    struct ParticleSystemConfig {
        // estimate for the max number of particles that will be live
        // at any one time in this particle system (used for pre-allocating memory).
        size_t particlePoolSize = 0;
        
        // the number of particles that will be emitted at the same time.
        // can give a range for a random number of particles each time,
        // otherwise set both min and max to the same value.
        int minParticlesPerEmission = 1;
        int maxParticlesPerEmission = 1;

        // time between particle emissions.
        // can give a range for random interval each time,
        // otherwise set both min and max to the same value.
        tD_delta minEmitInterval = 1;
        tD_delta maxEmitInterval = 1;

        // how long after each particle is emitted before the particle is destroyed.
        // can give a range for a random lifetime for each particle,
        // otherwise set both min and max to the same value.
        tD_time minParticleLifeTime = 1;
        tD_time maxParticleLifeTime = 1;

        // TODO: allow for various shapes of emission source,
        // like circle, cone, etc. in addition to rectangle.
        //
        // The lower-left and upper-right corners of the rectangle that defines
        // the particle system's emission space.
        // These coordinates are in the particle system's local space.
        Vector2<tD_pos> minEmitPoint = Vector2<tD_pos>(-1, -1);
        Vector2<tD_pos> maxEmitPoint = Vector2<tD_pos>(1, 1);

        // Angle (range) in degrees towards which a particle is emitted from its emission point.
        tD_rot minEmitAngleDeg = 0;
        tD_rot maxEmitAngleDeg = 180;

        // Angle (range) in degrees of particle's local rotation at the beginning of its life.
        tD_rot minBirthRotationDeg = 0;
        tD_rot maxBirthRotationDeg = 0;

        // If animateScale = true, each particle's size will change smoothly
        // through its lifetime from birthScale to deathScale.
        bool animateScale = false;
        Vector2<tD_real> minBirthScale = Vector2<tD_real>(1, 1);
        Vector2<tD_real> maxBirthScale = Vector2<tD_real>(1, 1);
        Vector2<tD_real> minDeathScale = Vector2<tD_real>(1, 1);
        Vector2<tD_real> maxDeathScale = Vector2<tD_real>(1, 1);

        // The speed (range) at which a particle travels after it is emitted.
        // If negative, particle will travel in the opposite direction of its emission angle.
        tD_real minParticleSpeed = -1;
        tD_real maxParticleSpeed = 1;

        // The acceleration (range) of a particle.
        bool accelerate = false;
        Vector2<tD_real> minParticleAcceleration = Vector2<tD_real>(0, 0);
        Vector2<tD_real> maxParticleAcceleration = Vector2<tD_real>(0, 0);

        // The angular speed (range) at which a particle spins after it is emitted.
        tD_real minParticleAngularSpeed = -1;
        tD_real maxParticleAngularSpeed = 1;        

        // If animateColor = true, each particle's color and transparency will change smoothly
        // through its lifetime from birthColor to deathColor.
        bool animateColor = false;
        RGBA minBirthColor = RGBA{ 255, 255, 255, 255 };
        RGBA maxBirthColor = RGBA{ 255, 255, 255, 255 };
        RGBA minDeathColor = RGBA{ 255, 255, 255, 255 };
        RGBA maxDeathColor = RGBA{ 255, 255, 255, 255 };

        // if true, the particle system will emit its first batch of particles
        // as soon as it is constructed. Otherwise, the first emission will happen
        // after the first emit time interval passes.
        bool emitOnWake = false;
    };


    /**
     * Particles use shared pointers to their components so that when a
     * particle is freed by the particle system, its components will
     * automatically be freed if they're not being used elsewhere.
     */
    struct Particle {
        Particle(const Transform2Ptr &transform,
                 const SharedPtr<RenderComponent2D> &renderComp, 
                 const SharedPtr<Rigidbody2D> &rigidBody, 
                 tD_time birthTime, tD_time lifeTime,
                 void *data = nullptr)
            : transform(transform), renderComp(renderComp), rigidBody(rigidBody), 
              data(data), mBirthTime(birthTime), mLifeTime(lifeTime), origTransform(*transform) {}


        bool isAlive(tD_time currentTime) const { return currentTime - mBirthTime <= mLifeTime; }


        // members

        Transform2Ptr transform  = nullptr;        

        /**
         * The particle system will only modify effects on a render component, and will not change
         * the texture itself. Therefore, the texture can be externally set and animated.
         */
        SharedPtr<RenderComponent2D> renderComp = nullptr;

        SharedPtr<Rigidbody2D> rigidBody  = nullptr;                

        /**
         * Anything can be stored here by the particle system's user
         * ex. an Entity object that holds the components of this particle
         * and is destroyed when this particle is destroyed.
         */        
        void *data = nullptr;


        tD_time mBirthTime; // when this particle was born
        tD_time mLifeTime; // how long this particle should live

        // a copy of the particle's transform value when it was first created.
        // used as the base for things like animating the particle's scale.
        DTransform2 origTransform;
    };


    /**
     * Construct an object of this class to create a configurable particle system.
     * The system will follow a transform that you provide, allowing you to play 
     * with the particle system as you please. It will do fancy things for you.
     */
    class ParticleSystem : public Component {
    public:
        // callback function typedefs
        
        using SpawnFunc = std::function<
            Particle(tD_time particleBirthTime, tD_time particleLifeTime)
        >;

        using DestroyFunc = std::function<
            void(Particle &particle)
        >;


        ParticleSystem(const ParticleSystemConfig &config,
                       const ConstTransform2Ptr &transform,
                       const SpawnFunc &spawnParticle,
                       const DestroyFunc &destroyParticle = [] (Particle &particle) {});


        void update(tD_delta delta) override;

        // can access and change particle system configuration at any time.
        ParticleSystemConfig &config() { return mConfig; }
        const ParticleSystemConfig &config() const { return mConfig; }

        // Returns the number of particles currently spawned in this particle system.
        // This could be used, for example, to smoothly destroy a particle system
        // at a moment when there are no particles (ie. this function returns 0).
        size_t particleCount() const { return mParticles.size(); }

    private:
        ParticleSystemConfig mConfig;
        ConstTransform2Ptr   mTransform;
        // holds a temporary non-const copy of mTransform for use with mNode
        DTransform2          mTempTransform;
        Node2D               mNode;

        SpawnFunc   mSpawnParticle;
        DestroyFunc mDestroyParticle;

        tD_time  mTimeElapsed;
        tD_time  mLastParticleSpawnTime;
        tD_delta mEmitInterval;

        std::vector<Particle> mParticles;


        void emitParticles();
        Particle &generateParticle(tD_time particleLifeTime);
        void initParticle(Particle &particle);
    };
}

#endif // D_PARTICLE_SYSTEM_H
