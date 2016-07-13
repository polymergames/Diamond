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

#ifndef D_QUANTUM_POLY_POINTS_H
#define D_QUANTUM_POLY_POINTS_H

#include "D_PolyColPoints.h"
#include "Q_CWPoints.h"
#include "D_typedefs.h"

namespace Diamond {
    class QuantumPolyPoints : public PolyColPoints {
    public:
        QuantumPolyPoints(const PointList &points) : m_points(points) {}
        
        const Quantum2D::CWPoints<PointList> &get() const { return m_points; }
        
    private:
        Quantum2D::CWPoints<PointList> m_points;
    };
}

#endif // D_QUANTUM_POLY_POINTS_H
