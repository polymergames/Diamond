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

#ifndef Q_POLY_COLLIDER_H
#define Q_POLY_COLLIDER_H

#include "Q_Collider2D.h"

namespace Quantum2D {
    /**
     Points must contain at least three vectors forming
     the boundary of a convex polygon. Consecutive points
     should be adjacent on the polygon in a consistent order
     (clockwise or counterclockwise).
    */
    class PolyCollider : public Collider2D {
    public:
        PolyCollider(const BodyList &bodylist,
                     body2d_id body,
                     void *parent,
                     const std::function<void(void *other)> &onCollision,
                     const PointList2D &points);
        
        /**
         Get the coordinates of this polygon's vertices
         in the parent rigidbody's local space.
         Points are in clockwise order.
        */
        const PointList2D &points() const { return m_points; }
        
        /**
         Get the current coordinates of this polygon's vertices
         in world space.
        */
        const PointList2D &worldPoints() const { return m_worldPoints; }
        
        void update(tQ_delta delta) override;
        
    private:
        PointList2D m_points;
        PointList2D m_worldPoints;
    };
}

#endif // Q_POLY_COLLIDER_H
