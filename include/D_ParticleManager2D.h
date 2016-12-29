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

#ifndef D_PARTICLE_MANAGER_H
#define D_PARTICLE_MANAGER_H

#include <vector>
#include "D_Component.h"
#include "D_ParticleEngine2D.h"

namespace Diamond {
    /**
     * This class sets up particle emitters and manages their emitted particles.
     *
     * It stores a pool of all generated particles, updates them,
     * and destroys them when they're dead.
     *
     * User is responsible for updating particle emitters. After a user destroys
     * an emitter/stops updating it, any particles already emitted by that
     * emitter will continue being updated by this particle manager.
     */
    class ParticleManager2D : public Diamond::Component {
    public:
        // callback typedefs

        using ParticleConfigFunc = std::function<
            void(Particle2D &particle, const ParticleSystem2DConfig &config)
        >;

        using ParticleFunc = std::function<
            void(Particle2D &particle)
        >;


        /**
         * The optional onDestroyParticle callback is called
         * every time a particle is about to be destroyed.
         *
         * particlePoolSize is an estimate for the max number of particles
         * that will be live among this manager's emitters
         * at any one time.
         */
        ParticleManager2D(const ParticleFunc &onDestroyParticle = nullptr,
                          size_t particlePoolSize = 100);


        /**
         * Constructs an emitter using the given config, transform, and optional
         * onInitParticle callback (see particle emitter constructor).
         *
         * The ParticleManager2D passes in its own function as the spawnParticle callback
         * to the emitter's constructor to allocate particles from the
         * particle manager's memory pool.
         *
         * Particles are constructed without providing
         * a transform or render component to each particle- these should be
         * set in onConstructParticle, which is called after a particle
         * is constructed by the particle manager but before it is passed 
         * to the particle emitter for initialization.
         */
        ParticleEmitter2D makeEmitter(const ParticleSystem2DConfig &config,
                                      const Transform2Ptr &transform,
                                      const ParticleConfigFunc &onConstructParticle = nullptr,
                                      const ParticleEmitter2D::InitParticleFunc &onInitParticle = nullptr);

        void update(tD_delta delta) override;

        /**
         * The returned list of particles is not grouped/ordered in any
         * way based on source emitters.
         */
        std::vector<Particle2D> &particles() { return mParticles; }
        const std::vector<Particle2D> &particles() const { return mParticles; }

    private:
        std::vector<Particle2D> mParticles;
        ParticleFunc mOnDestroyParticle;
    };
}

#endif // D_PARTICLE_MANAGER_H
