/*
    Copyright 2015 Ahnaf Siddiqui

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

#ifndef DU_MATH_H
#define DU_MATH_H

#include <algorithm>
#include <cstdlib>
#include "duVector2.h"
#include "duMatrix.h"
#include "duTypedefs.h"

namespace Diamond {
    namespace Math {
        const double PI = 3.14159265f;
        const double RAD2DEG = 180 / PI;
        const double DEG2RAD = PI / 180;

        inline double rad2deg(double rad) { return rad * RAD2DEG; }

        inline double deg2rad(double deg) { return deg * DEG2RAD; }

        inline int random(int min, int max) {
            return min + (std::rand() % (max - min + 1));
        }

        inline double random(double min, double max) {
            return min + ((double)std::rand() / RAND_MAX) * (max - min);
        }

        // Geometry
        template <typename A, typename B, typename C>
        inline bool leftOf(const Vector2<C> &x,
                           const Vector2<A> &ea,
                           const Vector2<B> &eb) {
            return (eb.x - ea.x) * (x.y - ea.y) - (eb.y - ea.y) * (x.x - ea.x) > 0;
        }

        template <typename T>
        inline T dist2SegmentPoint(const Vector2<T> &ea,
                                   const Vector2<T> &eb,
                                   const Vector2<T> &x) {
            auto length2 = ea.distanceSq(eb);
            if (length2 < EPS && length2 > -EPS)
                return ea.distanceSq(x);

            auto t = std::max(0.0f, std::min(1.0f, (T)((x - ea).dot(eb - ea) / length2)));
            return x.distanceSq(ea + t * (eb - ea));
        }



        // Generates a transformation matrix for rotation and scale, storing it in out
        template <typename T>
        void transMat(T rot_rad, T scale_x, T scale_y, T out[2][2]) {
            auto cosrot = std::cos(rot_rad);
            auto sinrot = std::sin(rot_rad);

            // [Scale] * [rotation] matrix multiplication in that order
            out[0][0] = scale_x * cosrot;
            out[0][1] = scale_x * sinrot;
            out[1][0] = -scale_y * sinrot;
            out[1][1] = scale_y * cosrot;
        }

        template <typename T>
        Matrix<T, 2, 2> transMat(T rot_rad, T scale_x, T scale_y) {
            auto cosrot = std::cos(rot_rad);
            auto sinrot = std::sin(rot_rad);

            return Matrix<T, 2, 2>{
                {
                    {scale_x * cosrot, scale_x * sinrot},
                    {-scale_y * sinrot, scale_y * cosrot}
                }
            };
        }
    }
}

#endif // DU_MATH_H
