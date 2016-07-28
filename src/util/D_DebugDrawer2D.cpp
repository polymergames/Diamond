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

void Diamond::DebugDrawer::draw(const PointList2D &poly,
                                const RGBA &color) {
    for (int i = 1; i < poly.size(); ++i) {
        m_renderer->renderLine(poly[i-1], poly[i], color);
    }

    m_renderer->renderLine(poly.back(), poly.front(), color);
}


void Diamond::DebugDrawer::draw(const CircleDef &circle,
                                const RGBA &color,
                                float angleInterval) {
    float angleIntervalRad = Math::deg2rad(angleInterval);

    Vector2<float> prev = circle.center + Vector2<float>(circle.radius, 0);
    Vector2<float> next;

    for (float a = angleIntervalRad;
         a < (2 * Math::PI + RAD_EPS);
         a += angleIntervalRad) {
        next = circle.center + Vector2<float>(circle.radius, 0).rotate(a);

        m_renderer->renderLine(prev, next, color);

        prev = next;
    }
}


void Diamond::DebugDrawer::draw(const CircleCollider *circle,
                                const RGBA &color,
                                float angleInterval) {
    CircleDef circleDef = { circle->getRadius(), circle->getWorldPos() };
    draw(circleDef, color, angleInterval);
}
