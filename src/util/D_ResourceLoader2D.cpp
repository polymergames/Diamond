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

#include "D_ResourceLoader2D.h"
#include "D_Log.h"


bool Diamond::ResourceLoader2D::loadRenderDef(const ConfigTable &config,
                                              RenderDef2D &renderDef,
                                              std::string &texturePath,
                                              Vector2<tD_real> &scale) const {
    texturePath = config.get("texture");

    if (texturePath.empty()) {
        Log::log("Required path to texture is missing in config");
        return false;
    }

    if (config.hasKey("renderLayer"))
        renderDef.layer = config.getInt("renderLayer");

    if (config.hasKey("pivotX"))
        renderDef.pivot.x = config.getFloat("pivotX");
    if (config.hasKey("pivotY"))
        renderDef.pivot.y = config.getFloat("pivotY");


    // Default scale
    scale.set(1, 1);

    if (config.hasKey("scaleX"))
        scale.x = config.getFloat("scaleX");
    if (config.hasKey("scaleY"))
        scale.y = config.getFloat("scaleY");

    return true;
}


bool Diamond::ResourceLoader2D::loadColliderDef(const ConfigTable &config,
                                                ColliderDef2D &collider) const {
    if (config.hasKey("collisionLayer"))
        collider.layer = config.getInt("collisionLayer");
    
    return true;
}


bool Diamond::ResourceLoader2D::loadAABBDef(const ConfigTable &config,
                                            AABBDef2D &aabb) const {
    if (!loadColliderDef(config, aabb))
        return false;
    
    if (!config.hasKey("dimX") || !config.hasKey("dimY")) {
        Log::log("Required AABB dimensions are missing in config");
        return false;
    }

    aabb.dims.x = config.getFloat("dimX");
    aabb.dims.y = config.getFloat("dimY");

    if (config.hasKey("originX"))
        aabb.origin.x = config.getFloat("originX");
    if (config.hasKey("originY"))
        aabb.origin.y = config.getFloat("originY");

    return true;

}


bool Diamond::ResourceLoader2D::loadCircleDef(const ConfigTable &config,
                                              CircleDef &circle) const {
    if (!loadColliderDef(config, circle))
        return false;
    
    if (!config.hasKey("radius")) {
        Log::log("Required circle radius is missing in config");
        return false;
    }

    circle.radius = config.getFloat("radius");

    if (config.hasKey("centerX"))
        circle.center.x = config.getFloat("centerX");
    if (config.hasKey("centerY"))
        circle.center.y = config.getFloat("centerY");

    return true;
}


bool Diamond::ResourceLoader2D::loadAnimationSheet(const ConfigTable &config,
                                                   TextureFactory &textureFactory,
                                                   AnimationSheet &animationSheet) const {
    if (!config.hasKey("texture")) {
        Log::log("Required animation sheet texture is missing in config");
        return false;
    }
    
    animationSheet.sprite_sheet = textureFactory.loadTexture(config.get("texture"));

    if (!animationSheet.sprite_sheet)
    {
        Log::log("Failed to load texture " + config.get("texture"));
        return false;
    }

    if (config.hasKey("frameLength"))
        animationSheet.frame_length = config.getFloat("frameLength");

    if (config.hasKey("numFrames"))
        animationSheet.num_frames = config.getInt("numFrames");

    if (config.hasKey("numRows"))
        animationSheet.rows = config.getInt("numRows");

    if (config.hasKey("numColumns"))
        animationSheet.columns = config.getInt("numColumns");

    return true;
}


bool Diamond::ResourceLoader2D::loadParticleSystem(const ConfigTable &config,
                                                   TextureFactory &textureFactory,
                                                   ParticleSystem2DConfig &particleSystemConfig) const {
    if (config.hasKey("particlePoolSize"))
        particleSystemConfig.particlePoolSize = config.getInt("particlePoolSize");
    
    
    if (config.hasKey("particleTexture"))
        particleSystemConfig.particleTexture = textureFactory.loadTexture(config.get("particleTexture"));


    if (config.hasKey("minParticlesPerEmission"))
        particleSystemConfig.minParticlesPerEmission = config.getInt("minParticlesPerEmission");

    if (config.hasKey("maxParticlesPerEmission"))
        particleSystemConfig.maxParticlesPerEmission = config.getInt("maxParticlesPerEmission");


    if (config.hasKey("minEmitInterval"))
        particleSystemConfig.minEmitInterval = config.getFloat("minEmitInterval");

    if (config.hasKey("maxEmitInterval"))
        particleSystemConfig.maxEmitInterval = config.getFloat("maxEmitInterval");


    if (config.hasKey("minParticleLifeTime"))
        particleSystemConfig.minParticleLifeTime = config.getFloat("minParticleLifeTime");

    if (config.hasKey("maxParticleLifeTime"))
        particleSystemConfig.maxParticleLifeTime = config.getFloat("maxParticleLifeTime");


    if (config.hasKey("minEmitPointX"))
        particleSystemConfig.minEmitPoint.x = config.getFloat("minEmitPointX");

    if (config.hasKey("minEmitPointY"))
        particleSystemConfig.minEmitPoint.y = config.getFloat("minEmitPointY");


    if (config.hasKey("maxEmitPointX"))
        particleSystemConfig.maxEmitPoint.x = config.getFloat("maxEmitPointX");

    if (config.hasKey("maxEmitPointY"))
        particleSystemConfig.maxEmitPoint.y = config.getFloat("maxEmitPointY");


    if (config.hasKey("minEmitAngleDeg"))
        particleSystemConfig.minEmitAngleDeg = config.getFloat("minEmitAngleDeg");

    if (config.hasKey("maxEmitAngleDeg"))
        particleSystemConfig.maxEmitAngleDeg = config.getFloat("maxEmitAngleDeg");


    if (config.hasKey("minBirthRotation"))
        particleSystemConfig.minBirthRotation = config.getFloat("minBirthRotation");

    if (config.hasKey("maxBirthRotation"))
        particleSystemConfig.maxBirthRotation = config.getFloat("maxBirthRotation");


    if (config.hasKey("animateScale"))
        particleSystemConfig.animateScale = config.getBool("animateScale");


    if (config.hasKey("minBirthScaleX"))
        particleSystemConfig.minBirthScale.x = config.getFloat("minBirthScaleX");

    if (config.hasKey("minBirthScaleY"))
        particleSystemConfig.minBirthScale.y = config.getFloat("minBirthScaleY");

    if (config.hasKey("maxBirthScaleX"))
        particleSystemConfig.maxBirthScale.x = config.getFloat("maxBirthScaleX");

    if (config.hasKey("maxBirthScaleY"))
        particleSystemConfig.maxBirthScale.y = config.getFloat("maxBirthScaleY");


    if (config.hasKey("minDeathScaleX"))
        particleSystemConfig.minDeathScale.x = config.getFloat("minDeathScaleX");

    if (config.hasKey("minDeathScaleY"))
        particleSystemConfig.minDeathScale.y = config.getFloat("minDeathScaleY");

    if (config.hasKey("maxDeathScaleX"))
        particleSystemConfig.maxDeathScale.x = config.getFloat("maxDeathScaleX");

    if (config.hasKey("maxDeathScaleY"))
        particleSystemConfig.maxDeathScale.y = config.getFloat("maxDeathScaleY");


    if (config.hasKey("minParticleSpeed"))
        particleSystemConfig.minParticleSpeed = config.getFloat("minParticleSpeed");

    if (config.hasKey("maxParticleSpeed"))
        particleSystemConfig.maxParticleSpeed = config.getFloat("maxParticleSpeed");


    if (config.hasKey("accelerate"))
        particleSystemConfig.accelerate = config.getBool("accelerate");


    if (config.hasKey("minParticleAccelerationX"))
        particleSystemConfig.minParticleAcceleration.x = config.getFloat("minParticleAccelerationX");

    if (config.hasKey("minParticleAccelerationY"))
        particleSystemConfig.minParticleAcceleration.y = config.getFloat("minParticleAccelerationY");

    if (config.hasKey("maxParticleAccelerationX"))
        particleSystemConfig.maxParticleAcceleration.x = config.getFloat("maxParticleAccelerationX");

    if (config.hasKey("maxParticleAccelerationY"))
        particleSystemConfig.maxParticleAcceleration.y = config.getFloat("maxParticleAccelerationY");


    if (config.hasKey("minParticleAngularSpeed"))
        particleSystemConfig.minParticleAngularSpeed = config.getFloat("minParticleAngularSpeed");

    if (config.hasKey("maxParticleAngularSpeed"))
        particleSystemConfig.maxParticleAngularSpeed = config.getFloat("maxParticleAngularSpeed");


    if (config.hasKey("animateColor"))
        particleSystemConfig.animateColor = config.getBool("animateColor");


    if (config.hasKey("minBirthColorR"))
        particleSystemConfig.minBirthColor.r = config.getInt("minBirthColorR");

    if (config.hasKey("minBirthColorG"))
        particleSystemConfig.minBirthColor.g = config.getInt("minBirthColorG");

    if (config.hasKey("minBirthColorB"))
        particleSystemConfig.minBirthColor.b = config.getInt("minBirthColorB");

    if (config.hasKey("minBirthColorA"))
        particleSystemConfig.minBirthColor.a = config.getInt("minBirthColorA");


    if (config.hasKey("maxBirthColorR"))
        particleSystemConfig.maxBirthColor.r = config.getInt("maxBirthColorR");

    if (config.hasKey("maxBirthColorG"))
        particleSystemConfig.maxBirthColor.g = config.getInt("maxBirthColorG");

    if (config.hasKey("maxBirthColorB"))
        particleSystemConfig.maxBirthColor.b = config.getInt("maxBirthColorB");

    if (config.hasKey("maxBirthColorA"))
        particleSystemConfig.maxBirthColor.a = config.getInt("maxBirthColorA");


    if (config.hasKey("minDeathColorR"))
        particleSystemConfig.minDeathColor.r = config.getInt("minDeathColorR");

    if (config.hasKey("minDeathColorG"))
        particleSystemConfig.minDeathColor.g = config.getInt("minDeathColorG");

    if (config.hasKey("minDeathColorB"))
        particleSystemConfig.minDeathColor.b = config.getInt("minDeathColorB");

    if (config.hasKey("minDeathColorA"))
        particleSystemConfig.minDeathColor.a = config.getInt("minDeathColorA");


    if (config.hasKey("maxDeathColorR"))
        particleSystemConfig.maxDeathColor.r = config.getInt("maxDeathColorR");

    if (config.hasKey("maxDeathColorG"))
        particleSystemConfig.maxDeathColor.g = config.getInt("maxDeathColorG");

    if (config.hasKey("maxDeathColorB"))
        particleSystemConfig.maxDeathColor.b = config.getInt("maxDeathColorB");

    if (config.hasKey("maxDeathColorA"))
        particleSystemConfig.maxDeathColor.a = config.getInt("maxDeathColorA");


    if (config.hasKey("emitOnWake"))
        particleSystemConfig.emitOnWake = config.getBool("emitOnWake");

    return true;
}


Diamond::PointList2D Diamond::ResourceLoader2D::loadPoints(
        const ConfigTable &config
) const {
    PointList2D points;
    int n = 1;

    std::string xstr("x" + toString(n));
    std::string ystr("y" + toString(n));

    while(config.hasKey(xstr) && config.hasKey(ystr)) {
        points.push_back(Vector2<tD_pos>(config.getFloat(xstr),
                                         config.getFloat(ystr)));

        xstr = "x" + toString(++n);
        ystr = "y" + toString(n);
    }

    return points;
}


Diamond::ConfigTable Diamond::ResourceLoader2D::genRenderConfig(
        const RenderDef2D &renderDef,
        const std::string &texturePath,
        const Vector2<tD_real> &scale
) const {
    ConfigTable config;

    config.set("texture", texturePath);

    config.set("renderLayer", renderDef.layer);

    config.set("pivotX", renderDef.pivot.x);
    config.set("pivotY", renderDef.pivot.y);

    config.set("scaleX", scale.x);
    config.set("scaleY", scale.y);

    return config;
}


Diamond::ConfigTable Diamond::ResourceLoader2D::genAABBConfig(
        const AABBDef2D &aabb
) const {
    ConfigTable config;
    
    config.set("collisionLayer", aabb.layer);

    config.set("dimX", aabb.dims.x);
    config.set("dimY", aabb.dims.y);

    config.set("originX", aabb.origin.x);
    config.set("originY", aabb.origin.y);

    return config;
}


Diamond::ConfigTable Diamond::ResourceLoader2D::genCircleConfig(
        const CircleDef &circle
) const {
    ConfigTable config;
    
    config.set("collisionLayer", circle.layer);

    config.set("centerX", circle.center.x);
    config.set("centerY", circle.center.y);

    config.set("radius", circle.radius);

    return config;
}


Diamond::ConfigTable Diamond::ResourceLoader2D::genPointsConfig(
        const PointList2D &points
) const {
    ConfigTable config;

    for (int i = 0; i < points.size(); ++i) {
        std::string xstr("x" + toString(i+1));
        std::string ystr("y" + toString(i+1));

        config.set(xstr, points[i].x);
        config.set(ystr, points[i].y);
    }

    return config;
}

