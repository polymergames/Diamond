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
#include "D_Config.h"
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

        // Angle (range) of particle's local rotation at the beginning of its life.
        tD_rot minBirthRotation = 0;
        tD_rot maxBirthRotation = 0;

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



    struct Particle {
        /**
         * Anything can be stored in data by the particle system's user
         * ex. an Entity object that holds the components of this particle
         * and is destroyed when this particle is destroyed.
         */
        void init(void *data, const Transform2Ptr &transform)
        { this->data = data; this->transform = transform; }


        void *data = nullptr;

        Transform2Ptr transform = nullptr;


        // ======= These are used by the particle engine =======
        
        bool isAlive(tD_time currentTime) const { return currentTime - mBirthTime <= mLifeTime; }


        Vector2<tD_real> acceleration = Vector2<tD_real>(0, 0);

        tD_time mBirthTime = 0; // when this particle was born
        tD_time mLifeTime = 0; // how long this particle should live

        Vector2<tD_real> deathScale = Vector2<tD_real>(1, 1);
    };



    /**
     * Construct an object of this class to create a configurable particle system.
     * It will do fancy things for you.
     */
    class ParticleSystem : public Component {
    public:
        // callback function typedefs
        
        using InitSpawnFunc = std::function<
            void(Particle &particle)
        >;

        using OnSpawnFunc = std::function<
            void(Particle &particle)
        >;

        using OnDestroyFunc = std::function<
            void(Particle &particle)
        >;


        /**
         The initSpawnedParticle function is called after a particle is constructed but before setup,
         and is responsible for calling the particle's init function (see Particle.init comment).

         The onSpawnParticle function is called after a particle is setup, and can be used
         to customize the particle and perform whatever other mischief the user desires.
         Don't use this callback if you don't know what you're doing.

         The onDestroyParticle function is called when a particle is about to be destroyed.
         This allows the user to, for example, free any resources associated with the particle
         (as indicated by the particle's user-set data pointer), or anything else that the user
         wants to do when a particle is destroyed.
        */
        ParticleSystem(const ParticleSystemConfig &config,
                       const InitSpawnFunc &initSpawnedParticle,
                       const OnSpawnFunc &onSpawnParticle = [] (Particle &particle) {},
                       const OnDestroyFunc &onDestroyParticle = [] (Particle &particle) {},
                       const DTransform2 &transform = DTransform2() );


        void update(tD_delta delta) override;

        // access and change particle system configuration at any time.
        ParticleSystemConfig &config() { return mConfig; }
        const ParticleSystemConfig &config() const { return mConfig; }

        // the particle system's transform (which is the parent of all of its particles in a scene graph)
        DTransform2 &transform() { return mTransform; }
        const DTransform2 &transform() const { return mTransform; }

        // Returns the number of particles currently spawned in this particle system.
        // This could be used, for example, to smoothly destroy a particle system
        // at a moment when there are no particles (ie. this function returns 0).
        size_t particleCount() const { return mParticles.size(); }

        std::vector<Particle> &particles() { return mParticles; }
        const std::vector<Particle> &particles() const { return mParticles; }

    private:
        ParticleSystemConfig  mConfig;
        DTransform2           mTransform;
        Matrix<tD_real, 2, 2> mTransMat;

        InitSpawnFunc mInitSpawnedParticle;
        OnSpawnFunc   mOnSpawnParticle;
        OnDestroyFunc mOnDestroyParticle;

        tD_time  mTimeElapsed;
        tD_time  mLastParticleSpawnTime;
        tD_delta mEmitInterval;

        std::vector<Particle> mParticles;


        void emitParticles();
        Particle &generateParticle();
        void initParticle(Particle &particle);
    };
}

#endif // D_PARTICLE_SYSTEM_H
