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

#include "D_DebugDrawer2D.h"
#include "duMath.h"

static const float RAD_EPS = 0.002f;

Diamond::DebugDrawer::DebugDrawer(Renderer2D *renderer)
    : m_renderer(renderer) {}


void Diamond::DebugDrawer::draw(const Diamond::PolyCollider *poly,
                                const RGBA &color) {
    PointList2D points = poly->worldPoints();
    
    for (int i = 1; i < points.size(); ++i) {
        m_renderer->renderLine(points[i-1], points[i], color);
    }
    
    m_renderer->renderLine(points.back(), points.front(), color);
}


void Diamond::DebugDrawer::draw(const CircleCollider *circle,
                                const RGBA &color,
                                float angleInterval) {
    float angleIntervalRad = Math::deg2rad(angleInterval);
    Vector2<float> center = circle->getWorldPos();
    float radius = circle->getRadius();

    Vector2<float> prev = center + Vector2<float>(radius, 0);
    Vector2<float> next;

    for (float a = angleIntervalRad;
         a < (2 * Math::PI + RAD_EPS);
         a += angleIntervalRad) {
        next = center + Vector2<float>(radius, 0).rotate(a);

        m_renderer->renderLine(prev, next, color);

        prev = next;
    }
}
