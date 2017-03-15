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

#include "D_ParticleManager2D.h"


Diamond::ParticleManager2D::ParticleManager2D(const ParticleFunc &onDestroyParticle,
                                              size_t particlePoolSize)
    : mOnDestroyParticle(onDestroyParticle) {

    mParticles.reserve(particlePoolSize);
}


Diamond::ParticleEmitter2D Diamond::ParticleManager2D::makeEmitter(const ParticleSystem2DConfig &config,
                                                                   const DTransform2 &transform,
                                                                   const ParticleConfigFunc &onConstructParticle,
                                                                   const ParticleEmitter2D::InitParticleFunc &onInitParticle) {
    return ParticleEmitter2D(
        config,
        transform,
        [this, onConstructParticle](const ParticleSystem2DConfig &configB) -> Particle2D& {
            mParticles.emplace_back();
            if (onConstructParticle) onConstructParticle(mParticles.back(), configB);
            return mParticles.back();
        },
        onInitParticle
    );
}


void Diamond::ParticleManager2D::update(tD_delta delta) {
    // Update particles and remove dead particles.
    // Using indexes instead of iterators because of iterator invalidation problems
    // (this is also why we're using an explicit vector instead of a template
    // argument that lets the user customize the container type).
    for (int i = 0; i < mParticles.size();) {
        if (!mParticles[i].isAlive()) {

            // If the current particle is dead, it is replaced
            // by the last particle in the list, which is then destroyed.
            // This allows O(1) removal from the middle of the vector, at the
            // expense of changing the order of the vector. However, changing the order
            // is ok, and the iterator is not advanced in this case so that the
            // replacement particle now at this position can also be processed before moving on.

            if (mOnDestroyParticle)
                mOnDestroyParticle(mParticles[i]);

            if (i + 1 < mParticles.size())
                mParticles[i] = std::move(mParticles.back());

            mParticles.pop_back();
        }
        else {
            mParticles[i].update(delta);

            // since no particle has been removed in this case,
            // we can advance the iterator.
            ++i;
        }
    }
}
