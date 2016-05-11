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

#ifndef D_MATRIX_H
#define D_MATRIX_H

namespace Diamond {
    namespace Matrix {
        
        /**
         Multiplies two matrices and stores the result in out.
         Out should be initialized to zero!
        */
        template <typename M, int dim1, int dim2, int dim3>
        inline void mul(M m1[dim1][dim2], M m2[dim2][dim3], M out[dim1][dim3]) {
            for (int r = 0; r < dim1; ++r) {
                for (int r2 = 0; r2 < dim2; ++r2) {
                    for (int c = 0; c < dim3; ++c) {
                        out[r][c] += m1[r][r2] * m2[r2][c];
                    }
                }
            }
        }

    }
}

#endif // D_MATRIX_H
