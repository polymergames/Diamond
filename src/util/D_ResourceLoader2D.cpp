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
                                              Vector2<tD_real> &scale) {
    texturePath = config.get("texturePath");

    if (texturePath.empty()) {
        Log::log("Required path to texture is missing in config");
        return false;
    }


    renderDef.layer = config.getInt("layer");

    renderDef.pivot.x = config.getFloat("pivotX");
    renderDef.pivot.y = config.getFloat("pivotY");


    // Default scale
    scale.set(1, 1);

    if (config.hasKey("scaleX"))
        scale.x = config.getFloat("scaleX");
    if (config.hasKey("scaleY"))
        scale.y = config.getFloat("scaleY");

    return true;
}

bool Diamond::ResourceLoader2D::loadAABBDef(const ConfigTable &config,
                                            AABBDef2D &aabb) {
    if (!config.hasKey("dimX") || !config.hasKey("dimY")) {
        Log::log("Required AABB dimensions are missing in config");
        return false;
    }

    aabb.dims.x = config.getFloat("dimX");
    aabb.dims.y = config.getFloat("dimY");

    aabb.origin.x = config.getFloat("originX");
    aabb.origin.y = config.getFloat("originY");

    return true;

}

bool Diamond::ResourceLoader2D::loadCircleDef(const ConfigTable &config,
                                              CircleDef &circle) {
    circle.center.x = config.getFloat("centerX");
    circle.center.y = config.getFloat("centerY");

    circle.radius = config.getFloat("radius");

    return true;
}

Diamond::PointList2D Diamond::ResourceLoader2D::loadPoints(
        const ConfigTable &config
) {
    PointList2D points;
    int n = 1;

    std::string xstr("x" + std::to_string(n));
    std::string ystr("y" + std::to_string(n));

    while(config.hasKey(xstr) && config.hasKey(ystr)) {
        points.push_back(Vector2<tD_pos>(config.getFloat(xstr),
                                         config.getFloat(ystr)));

        xstr = "x" + std::to_string(++n);
        ystr = "y" + std::to_string(n);
    }

    return points;
}


Diamond::ConfigTable Diamond::ResourceLoader2D::genRenderConfig(
        const RenderDef2D &renderDef,
        const std::string &texturePath,
        const Vector2<tD_real> &scale
) {
    ConfigTable config;

    config.set("texturePath", texturePath);

    config.set("layer", renderDef.layer);

    config.set("pivotX", renderDef.pivot.x);
    config.set("pivotY", renderDef.pivot.y);

    config.set("scaleX", scale.x);
    config.set("scaleY", scale.y);

    return config;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genAABBConfig(
        const AABBDef2D &aabb
) {
    ConfigTable config;

    config.set("dimX", aabb.dims.x);
    config.set("dimY", aabb.dims.y);

    config.set("originX", aabb.origin.x);
    config.set("originY", aabb.origin.y);

    return config;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genCircleConfig(
        const CircleDef &circle
) {
    ConfigTable config;

    config.set("centerX", circle.center.x);
    config.set("centerY", circle.center.y);

    config.set("radius", circle.radius);

    return config;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genPointsConfig(
        const PointList2D &points
) {
    ConfigTable config;

    for (int i = 0; i < points.size(); ++i) {
        std::string xstr("x" + std::to_string(i+1));
        std::string ystr("y" + std::to_string(i+1));

        config.set(xstr, points[i].x);
        config.set(ystr, points[i].y);
    }

    return config;
}