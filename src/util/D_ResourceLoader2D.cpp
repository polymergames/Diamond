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

  if (config.hasKey("pivotX")) renderDef.pivot.x = config.getFloat("pivotX");
  if (config.hasKey("pivotY")) renderDef.pivot.y = config.getFloat("pivotY");

  // Default scale
  scale.set(1, 1);

  if (config.hasKey("scaleX")) scale.x = config.getFloat("scaleX");
  if (config.hasKey("scaleY")) scale.y = config.getFloat("scaleY");

  return true;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genRenderConfig(
    const RenderDef2D &renderDef, const std::string &texturePath,
    const Vector2<tD_real> &scale) const {
  ConfigTable config;

  config.set("texture", texturePath);

  config.set("renderLayer", renderDef.layer);

  config.set("pivotX", renderDef.pivot.x);
  config.set("pivotY", renderDef.pivot.y);

  config.set("scaleX", scale.x);
  config.set("scaleY", scale.y);

  return config;
}

bool Diamond::ResourceLoader2D::loadColliderDef(const ConfigTable &config,
                                                ColliderDef2D &collider) const {
  if (config.hasKey("collisionLayer"))
    collider.layer = config.getInt("collisionLayer");

  return true;
}

bool Diamond::ResourceLoader2D::loadAABBDef(const ConfigTable &config,
                                            AABBDef2D &aabb) const {
  if (!loadColliderDef(config, aabb)) return false;

  if (!config.hasKey("dimX") || !config.hasKey("dimY")) {
    Log::log("Required AABB dimensions are missing in config");
    return false;
  }

  aabb.dims.x = config.getFloat("dimX");
  aabb.dims.y = config.getFloat("dimY");

  if (config.hasKey("originX")) aabb.origin.x = config.getFloat("originX");
  if (config.hasKey("originY")) aabb.origin.y = config.getFloat("originY");

  return true;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genAABBConfig(
    const AABBDef2D &aabb) const {
  ConfigTable config;

  config.set("collisionLayer", aabb.layer);

  config.set("dimX", aabb.dims.x);
  config.set("dimY", aabb.dims.y);

  config.set("originX", aabb.origin.x);
  config.set("originY", aabb.origin.y);

  return config;
}

bool Diamond::ResourceLoader2D::loadCircleDef(const ConfigTable &config,
                                              CircleDef &circle) const {
  if (!loadColliderDef(config, circle)) return false;

  if (!config.hasKey("radius")) {
    Log::log("Required circle radius is missing in config");
    return false;
  }

  circle.radius = config.getFloat("radius");

  if (config.hasKey("centerX")) circle.center.x = config.getFloat("centerX");
  if (config.hasKey("centerY")) circle.center.y = config.getFloat("centerY");

  return true;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genCircleConfig(
    const CircleDef &circle) const {
  ConfigTable config;

  config.set("collisionLayer", circle.layer);

  config.set("centerX", circle.center.x);
  config.set("centerY", circle.center.y);

  config.set("radius", circle.radius);

  return config;
}

bool Diamond::ResourceLoader2D::loadAnimationSheet(
    const ConfigTable &config, TextureFactory &textureFactory,
    AnimationSheet &animationSheet) const {
  if (!config.hasKey("texture")) {
    Log::log("Required animation sheet texture is missing in config");
    return false;
  }

  animationSheet.sprite_sheet =
      textureFactory.loadTexture(config.get("texture"));

  if (!animationSheet.sprite_sheet) {
    Log::log("Failed to load texture " + config.get("texture"));
    return false;
  }

  if (config.hasKey("frameLength"))
    animationSheet.frame_length = config.getFloat("frameLength");

  if (config.hasKey("numFrames"))
    animationSheet.num_frames = config.getInt("numFrames");

  if (config.hasKey("numRows")) animationSheet.rows = config.getInt("numRows");

  if (config.hasKey("numColumns"))
    animationSheet.columns = config.getInt("numColumns");

  if (config.hasKey("loop"))
    animationSheet.loop = config.getBool("loop");

  return true;
}

Diamond::PointList2D Diamond::ResourceLoader2D::loadPoints(
    const ConfigTable &config) const {
  PointList2D points;
  int n = 1;

  std::string xstr("x" + toString(n));
  std::string ystr("y" + toString(n));

  while (config.hasKey(xstr) && config.hasKey(ystr)) {
    points.push_back(
        Vector2<tD_pos>(config.getFloat(xstr), config.getFloat(ystr)));

    xstr = "x" + toString(++n);
    ystr = "y" + toString(n);
  }

  return points;
}

Diamond::ConfigTable Diamond::ResourceLoader2D::genPointsConfig(
    const PointList2D &points) const {
  ConfigTable config;

  for (int i = 0; i < points.size(); ++i) {
    std::string xstr("x" + toString(i + 1));
    std::string ystr("y" + toString(i + 1));

    config.set(xstr, points[i].x);
    config.set(ystr, points[i].y);
  }

  return config;
}
