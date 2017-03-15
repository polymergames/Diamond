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

#include <fstream>
#include "D_Benchmark.h"
#include "D_Game2D.h"
#include "D_SDLConfigLoader.h"
#include "D_ParticleManager2D.h"

class ParticleDemo : public Diamond::Game2D {
public:
    ParticleDemo(Diamond::Engine2D &engine,
                 float movespeed = 0.75, float spinspeed = 0.75,
                 bool benchmark = false,
                 const std::string &benchmarkFile = "");
    virtual ~ParticleDemo();

    void update(tD_delta delta) override;

    bool willPlayAgain() const { return again; }

private:
    static constexpr auto PARTICLE_CONFIG_FILE = "particles.cfg";

    float movespeed, spinspeed;
    bool again;

    Diamond::Transform2Ptr     particleSystemTransform;

    Diamond::SDLConfigLoader   configLoader;
    Diamond::TextureFactory    textureFactory;
    Diamond::ParticleManager2D particleManager;
    Diamond::ParticleEmitter2D particleEmitter;

    Diamond::BenchmarkLogger *benchmarkLogger;
    std::ofstream benchmarkStream;
};
