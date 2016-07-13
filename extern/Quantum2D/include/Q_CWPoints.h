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

#ifndef Q_CW_POINTS_H
#define Q_CW_POINTS_H

#include <algorithm>
#include "duMath.h"

namespace Quantum2D {
    /**
     This class contains a set of points and ensures that the points
     are in clockwise order.
    */
    template <typename T>
    class CWPoints {
    public:
        // TODO: make this check more than just the first three points!
        // Look up efficient algorithm for determining if a set of points
        // is clockwise
        CWPoints(const T &points) : m_points(points) {
            if (m_points.size() >= 3 &&
                Diamond::Math::leftOf(points[2], points[0], points[1])) {
                
                std::reverse(m_points.begin(), m_points.end());
                
            }
        }
        
        const T &get() const { return m_points; }
        
    private:
        T m_points;
    };
}

#endif // Q_CW_POINTS_H
