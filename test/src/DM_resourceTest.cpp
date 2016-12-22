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

#include <algorithm>
#include "gtest/gtest.h"
#include "D_ParticleSystem2D.h"
#include "D_ResourceLoader2D.h"

using namespace Diamond;


TEST(Resource2DTest, RenderDef) {
    ResourceLoader2D resources;

    RenderDef2D renderDefA;
    renderDefA.layer = 3;
    renderDefA.pivot = Vector2<float>(12, 6.2);
    std::string textureA = "bigboss";
    Vector2<float> scaleA(2.5f, 3.0f);

    ConfigTable config = resources.genRenderConfig(renderDefA, textureA, scaleA);

    RenderDef2D renderDefB;
    std::string textureB;
    Vector2<float> scaleB;

    ASSERT_TRUE(resources.loadRenderDef(config, renderDefB, textureB, scaleB));

    EXPECT_EQ(renderDefB.layer, renderDefA.layer);
    EXPECT_FLOAT_EQ(renderDefB.pivot.x, renderDefA.pivot.x);
    EXPECT_FLOAT_EQ(renderDefB.pivot.y, renderDefA.pivot.y);
    EXPECT_EQ(textureB, textureA);
    EXPECT_FLOAT_EQ(scaleB.x, scaleA.x);
    EXPECT_FLOAT_EQ(scaleB.y, scaleA.y);
}

TEST(Resource2DTest, AABBDef) {
    ResourceLoader2D resources;

    AABBDef2D aabbA;
    aabbA.dims = Vector2<float>(12, 14);
    aabbA.origin = Vector2<float>(-2, 1);

    ConfigTable config = resources.genAABBConfig(aabbA);

    AABBDef2D aabbB;

    ASSERT_TRUE(resources.loadAABBDef(config, aabbB));

    EXPECT_FLOAT_EQ(aabbB.dims.x, aabbA.dims.x);
    EXPECT_FLOAT_EQ(aabbB.dims.y, aabbA.dims.y);
    EXPECT_FLOAT_EQ(aabbB.origin.x, aabbA.origin.x);
    EXPECT_FLOAT_EQ(aabbB.origin.y, aabbA.origin.y);
}

TEST(Resource2DTest, CircleDef) {
    ResourceLoader2D resources;

    CircleDef circleA;
    circleA.radius = 3.6;
    circleA.center = Vector2<float>(7, 11);

    ConfigTable config = resources.genCircleConfig(circleA);

    CircleDef circleB;

    ASSERT_TRUE(resources.loadCircleDef(config, circleB));

    EXPECT_FLOAT_EQ(circleB.radius, circleA.radius);
    EXPECT_FLOAT_EQ(circleB.center.x, circleA.center.x);
    EXPECT_FLOAT_EQ(circleB.center.y, circleA.center.y);
}

TEST(Resource2DTest, PointList) {
    ResourceLoader2D resources;

    PointList2D pointsA;
    pointsA.push_back(Vector2<float>(54, -51));
    pointsA.push_back(Vector2<float>(-92, -95));
    pointsA.push_back(Vector2<float>(-57, 9));
    pointsA.push_back(Vector2<float>(81, 2.3));
    pointsA.push_back(Vector2<float>(64, 24));

    ConfigTable config = resources.genPointsConfig(pointsA);

    PointList2D pointsB = resources.loadPoints(config);

    ASSERT_EQ(pointsB.size(), pointsA.size());

    for (Vector2<float> point : pointsB) {
        EXPECT_TRUE(std::find(pointsA.begin(), pointsA.end(), point) != pointsA.end());
    }
}

TEST(Resource2DTest, ParticleSystem) {
    ParticleSystem2DConfig particlesA;

    particlesA.particlePoolSize = 100;
    particlesA.maxParticlesPerEmission = 10;
    particlesA.minEmitInterval = 50;
    particlesA.maxEmitInterval = 115;
    particlesA.minParticleLifeTime = 1000;
    particlesA.maxParticleLifeTime = 2345;
    particlesA.minEmitPoint.scalar(32);
    particlesA.maxEmitPoint.scalar(43);
    particlesA.maxBirthRotation = 50;
    particlesA.maxBirthScale.scalar(10);
    particlesA.maxParticleSpeed = 20;
    particlesA.accelerate = true;
    particlesA.maxParticleAcceleration.set(9, 9);
    particlesA.maxParticleAngularSpeed = 20;
    particlesA.minBirthColor = RGBA{ 120, 22, 230, 0 };
    particlesA.maxDeathColor = RGBA{ 255, 255, 255, 30 };
    particlesA.emitOnWake = true;

    auto config = particlesA.genTable("swagTexture");

    auto particlesB = ParticleSystem2DConfig(config, nullptr);

    EXPECT_EQ(particlesB.particlePoolSize, particlesA.particlePoolSize);
    EXPECT_EQ(particlesB.maxParticlesPerEmission, particlesA.maxParticlesPerEmission);
    EXPECT_FLOAT_EQ(particlesB.minEmitInterval, particlesA.minEmitInterval);
    EXPECT_FLOAT_EQ(particlesB.maxEmitInterval, particlesA.maxEmitInterval);
    EXPECT_FLOAT_EQ(particlesB.minParticleLifeTime, particlesA.minParticleLifeTime);
    EXPECT_FLOAT_EQ(particlesB.maxParticleLifeTime, particlesA.maxParticleLifeTime);
    EXPECT_FLOAT_EQ(particlesB.minEmitPoint.x, particlesA.minEmitPoint.x);
    EXPECT_FLOAT_EQ(particlesB.minEmitPoint.y, particlesA.minEmitPoint.y);
    EXPECT_FLOAT_EQ(particlesB.maxEmitPoint.x, particlesA.maxEmitPoint.x);
    EXPECT_FLOAT_EQ(particlesB.maxEmitPoint.y, particlesA.maxEmitPoint.y);
    EXPECT_FLOAT_EQ(particlesB.maxBirthRotation, particlesA.maxBirthRotation);
    EXPECT_FLOAT_EQ(particlesB.maxBirthScale.x, particlesA.maxBirthScale.x);
    EXPECT_FLOAT_EQ(particlesB.maxBirthScale.y, particlesA.maxBirthScale.y);
    EXPECT_FLOAT_EQ(particlesB.maxParticleSpeed, particlesA.maxParticleSpeed);
    EXPECT_EQ(particlesB.accelerate, particlesA.accelerate);
    EXPECT_FLOAT_EQ(particlesB.maxParticleAcceleration.x, particlesA.maxParticleAcceleration.x);
    EXPECT_FLOAT_EQ(particlesB.maxParticleAcceleration.y, particlesA.maxParticleAcceleration.y);
    EXPECT_FLOAT_EQ(particlesB.maxParticleAngularSpeed, particlesA.maxParticleAngularSpeed);
    EXPECT_EQ(particlesB.minBirthColor.r, particlesA.minBirthColor.r);
    EXPECT_EQ(particlesB.minBirthColor.g, particlesA.minBirthColor.g);
    EXPECT_EQ(particlesB.minBirthColor.b, particlesA.minBirthColor.b);
    EXPECT_EQ(particlesB.minBirthColor.a, particlesA.minBirthColor.a);
    EXPECT_EQ(particlesB.maxDeathColor.r, particlesA.maxDeathColor.r);
    EXPECT_EQ(particlesB.maxDeathColor.g, particlesA.maxDeathColor.g);
    EXPECT_EQ(particlesB.maxDeathColor.b, particlesA.maxDeathColor.b);
    EXPECT_EQ(particlesB.maxDeathColor.a, particlesA.maxDeathColor.a);
    EXPECT_EQ(particlesB.emitOnWake, particlesA.emitOnWake);
}