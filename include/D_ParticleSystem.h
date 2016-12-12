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

#include <deque>
#include <functional>
#include "D_Component.h"
#include "D_RenderComponent2D.h"
#include "D_Rigidbody2D.h"
#include "D_Timer.h"
#include "D_Transform2.h"
#include "D_typedefs.h"

namespace Diamond {

    struct ParticleSystemDef {
        //
    };


    /**
     * Particles use shared pointers to their components so that when a
     * particle is freed by the particle system, its components will
     * automatically be freed if they're not being used elsewhere.
     */
    class Particle {
    public:
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


        Particle(const Transform2Ptr &transform,
                 const SharedPtr<RenderComponent2D> &renderComp, 
                 const SharedPtr<Rigidbody2D> &rigidBody, 
                 void *data = nullptr)
            : transform(transform), renderComp(renderComp), rigidBody(rigidBody), data(data),  
              mLifeTime(0), mBirthTime(0) {}
        

        // These functions are used by the particle system

        void setLifeTime(tD_time lifeTime) { mLifeTime = lifeTime; }

        void initTime(tD_time currentTime) { mBirthTime = currentTime; }

        bool isAlive(tD_time currentTime) { return currentTime - mBirthTime <= mLifeTime; }


    private:
        tD_time mLifeTime; // how long this particle should live
        tD_time mBirthTime; // when this particle was born
    };



    class ParticleSystem : public Component {
    public:
        // callback function typedefs
        
        using SpawnFunc = std::function<
            Particle(void)
        >;

        using DestroyFunc = std::function<
            void(const Particle &particle)
        >;


        ParticleSystem(const ParticleSystemDef &def,
                       const ConstTransform2Ptr &transform,
                       const SpawnFunc &spawnParticle,
                       const DestroyFunc &destroyParticle);


        void update(tD_delta delta) override;

    private:
        ParticleSystemDef  mDef;
        ConstTransform2Ptr mTransform;

        SpawnFunc         mSpawnParticle;
        DestroyFunc       mDestroyParticle;

        tD_time mTimeElapsed;
        std::deque<Particle> mParticles;


        Particle &generateParticle(tD_delta delta);
        void initParticle(Particle &particle, tD_delta delta);
    };
}

#endif // D_PARTICLE_SYSTEM_H
