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

#ifndef D_PARTICLE_ENGINE_H
#define D_PARTICLE_ENGINE_H

#include <functional>
#include <vector>
#include "duMatrix.h"
#include "D_Component.h"
#include "D_Config.h"
#include "D_ConfigTable.h"
#include "D_RenderComponent2D.h"
#include "D_TextureFactory.h"
#include "D_Transform2.h"
#include "D_typedefs.h"

namespace Diamond {

    struct ParticleSystem2DConfig {
        ParticleSystem2DConfig() {}

        ParticleSystem2DConfig(const ConfigTable &configTable,
                               TextureFactory &textureFactory);

        ParticleSystem2DConfig(const ConfigTable &configTable,
                               const Texture *particleTexture);

        ConfigTable genTable(const std::string &particleTexturePath) const;


        // estimate for the max number of particles that will be live
        // at any one time in this particle system (used for pre-allocating memory).
        size_t particlePoolSize = 0;

        // the texture used to render each particle
        const Texture *particleTexture = nullptr;

        // the layer that particles will be rendered on
        RenderLayer layer = 0;

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
        tD_real minBirthScale = 1;
        tD_real maxBirthScale = 1;
        tD_real minDeathScale = 1;
        tD_real maxDeathScale = 1;

        // The speed (range) at which a particle travels after it is emitted.
         // If negative, particle will travel in the opposite direction of its emission angle.
        tD_real minParticleSpeed = -1;
        tD_real maxParticleSpeed = 1;

        // The acceleration (range) of a particle.
        bool accelerate = false;
        Vector2<tD_real> minParticleAcceleration = Vector2<tD_real>(0, 0);
        Vector2<tD_real> maxParticleAcceleration = Vector2<tD_real>(0, 0);

        // The angular speed (range) at which a particle spins after it is emitted.
        tD_real minParticleAngularSpeed = 0;
        tD_real maxParticleAngularSpeed = 0;

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



    class Particle2D : public Component {
    public:

        /**
         * All parameters are optional.
         */
        Particle2D(const Transform2Ptr &transform = nullptr,
                   const DumbPtr<RenderComponent2D> &renderComponent = nullptr,
                   void *data = nullptr)
            : transform(transform), renderComponent(renderComponent), data(data) {}

        ~Particle2D() { transform.free(); renderComponent.free(); }

        /**
         * If update is called every frame, this function can be used to determine
         * if the particle is still alive and should be updated again.
         * When this returns false, the particle and its associated resources
         * should be destroyed.
         */
        bool isAlive() const { return age <= lifeTime; }

        /**
         * Update is called by whoever is managing updates for particles,
         * ex. ParticleSystem2D or however the user wants to do it.
         */
        void update(tD_delta delta) override;


        /**
         * Particle updates its transform in an external transform object.
         */
        Transform2Ptr transform = nullptr;

        /**
         * The particle system will only modify effects on a render component, and will not change
         * the texture itself. Therefore, the texture can be externally set and animated.
         */
        DumbPtr<RenderComponent2D> renderComponent = nullptr;

        /**
         * Anything can be stored in data by the particle system's user
         * ex. an Entity object that holds the components of this particle
         * and is destroyed when this particle is destroyed.
         */
        void *data = nullptr;



        // ======= These are used by the particle engine or the particle itself =======

        // life
        tD_time age = 0;
        tD_time lifeTime = 0;

        // physics
        Vector2<tD_real> velocity = Vector2<tD_real>(0, 0);
        Vector2<tD_real> acceleration = Vector2<tD_real>(0, 0);
        tD_real angularSpeed = 0;

        // scale
        bool animateScale = false;
        Vector2<tD_real> deathScale = Vector2<tD_real>(1, 1);

        // colors
        bool animateColor = false;
        RGBA deathColor = RGBA{ 255, 255, 255, 255 };
    };



    /**
     * An object of this class emits particles from its origin transform.
     * It will do fancy things for you.
     * User is responsible for allocating, storing, updating, and destroying the emitted particles.
     */
    class ParticleEmitter2D : public Diamond::Component {
    public:
        // callback function typedefs

        using SpawnParticleFunc = std::function<
            Particle2D&(const ParticleSystem2DConfig &config)
        >;

        using InitParticleFunc = std::function<
            void(Particle2D &particle, const ParticleSystem2DConfig &config)
        >;


        /**
         * The required spawnParticle function should construct a particle and return
         * a reference to it.
         *
         * The optional onInitParticle function is called after a particle is initialized and setup for emission,
         * and can be used to customize the particle and perform whatever other mischief the user desires.
         */
        ParticleEmitter2D(const ParticleSystem2DConfig &config,
                          const DTransform2 &transform,
                          const SpawnParticleFunc &spawnParticle,
                          const InitParticleFunc &onInitParticle = nullptr);


        /**
         * If this is called every frame, it will emit particles
         * after each time interval (as configured in the emitter's ParticleSystem2DConfig).
         */
        void update(tD_delta delta) override;

        /**
         * Calling this will immediately emit particles.
         */
        void emitParticles();


        // access and change particle emitter configuration at any time.
        ParticleSystem2DConfig &config() { return mConfig; }
        const ParticleSystem2DConfig &config() const { return mConfig; }


        // the particle emitter's transform (which is the source of all of its particles in a scene graph)
        const DTransform2        &transform()       const { return *mTransform; }


    private:
        void initParticle(Particle2D &particle);


        ParticleSystem2DConfig mConfig;
        const DTransform2      *mTransform;
        Matrix<tD_real, 2, 2>  mTransMat;

        SpawnParticleFunc mSpawnParticle;
        InitParticleFunc  mOnInitParticle;

    // DEBUGGING
    public:
        tD_time  mTimeElapsed;
        tD_time  mLastParticleSpawnTime;
        tD_delta mEmitInterval;
    };
}

#endif // D_PARTICLE_ENGINE_H
