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

#include <iostream>
#include "D_Vector2.h"

namespace Diamond {
    namespace MatrixMath {
        /**
         Calculates the inverse of the given 2x2 matrix and stores the result in out.
         Does NOT check if the matrix is invertible first; use sInv if you want more safety.
        */
        template <typename M>
        inline void inv(const M m[2][2], M out[2][2]) {
            M inv_det = 1.0 / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
            out[0][0] = inv_det * m[1][1];
            out[0][1] = -inv_det * m[0][1];
            out[1][0] = -inv_det * m[1][0];
            out[1][1] = inv_det * m[0][0];
        }

        /**
         Calculates the inverse of the given 2x2 matrix and stores the result in out.
         If the given matrix is not invertible, out isn't changed.
        */
        template <typename M>
        inline void sInv(const M m[2][2], M out[2][2]) {
            M inv_det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
            if (inv_det != 0) {
                inv_det = 1.0 / inv_det;

                out[0][0] = inv_det * m[1][1];
                out[0][1] = -inv_det * m[0][1];
                out[1][0] = -inv_det * m[1][0];
                out[1][1] = inv_det * m[0][0];
            }
        }

        /**
         Multiplies two matrices and stores the result in out.
         Out should be initialized to zero!
        */
        template <typename M, int dim1, int dim2, int dim3>
        inline void mul(const M m1[dim1][dim2], 
                        const M m2[dim2][dim3], 
                        M out[dim1][dim3]) {
            for (int r = 0; r < dim1; ++r) {
                for (int r2 = 0; r2 < dim2; ++r2) {
                    for (int c = 0; c < dim3; ++c) {
                        out[r][c] += m1[r][r2] * m2[r2][c];
                    }
                }
            }
        }

        /**
         Multiplies the vector by the matrix as v * m, treating the vector as a row vector.
         Returns the row vector result.
        */
        template <typename V, typename M>
        inline Vector2<V> mul(const Vector2<V> &v, const M m[2][2]) {
            return v.mul(m);
        }

        /**
         Multiplies the matrix and vector as m * v, treating the vector as a column vector.
         Returns the column vector result.
        */
        template <typename M, typename V>
        inline Vector2<V> mul(const M m[2][2], const Vector2<V> &v) {
            return Vector2<V>(
                m[0][0] * v.x + m[0][1] * v.y,
                m[1][0] * v.x + m[1][1] * v.y
            );
        }

    }

    template <typename T, int dim1, int dim2>
    class Matrix {
    public:
        T m[dim1][dim2];

        // Inverse functions
        // Only works if a MatrixMath::inv function exists for this matrix's dimensions.

        // Does NOT check if this matrix is invertible first; use sInv if you want more safety.
        Matrix inv() const {
            Matrix inverse;
            MatrixMath::inv(m, inverse.m);
            return inverse;
        }

        // Safer version of inv(), checks if the matrix is invertible.
        // Returns zero matrix if not invertible.
        Matrix sInv() const {
            Matrix inverse = { {0} };
            MatrixMath::sInv(m, inverse.m);
            return inverse;
        }

        // Matrix multiplication

        template <int dim3>
        Matrix<T, dim1, dim3> mul(const Matrix<T, dim2, dim3> &m2) const {
            Matrix<T, dim1, dim3> res = { 0 };
            MatrixMath::mul<T, dim1, dim2, dim3>(m, m2.m, res.m);
            return res;
        }

        template <typename V>
        Vector2<V> mul(const Vector2<V> &v) const {
            return MatrixMath::mul(m, v);
        }

        // operator overloads

        T *operator[](int index) {
            return m[index];
        }

        const T *operator[](int index) const {
            return m[index];
        }

        Matrix operator+(const Matrix &m2) const {
            Matrix res;
            for (int r = 0; r < dim1; ++r) {
                for (int c = 0; c < dim2; ++c) {
                    res[r][c] = m[r][c] + m2[r][c];
                }
            }
            return res;
        }

        Matrix operator-(const Matrix &m2) const {
            Matrix res;
            for (int r = 0; r < dim1; ++r) {
                for (int c = 0; c < dim2; ++c) {
                    res[r][c] = m[r][c] - m2[r][c];
                }
            }
            return res;
        }

        Matrix &operator+=(const Matrix &m2) {
            for (int r = 0; r < dim1; ++r) {
                for (int c = 0; c < dim2; ++c) {
                    m[r][c] += m2[r][c];
                }
            }
            return *this;
        }

        Matrix &operator-=(const Matrix &m2) {
            for (int r = 0; r < dim1; ++r) {
                for (int c = 0; c < dim2; ++c) {
                    m[r][c] -= m2[r][c];
                }
            }
            return *this;
        }
    };

    // Scalar multiplication
    template <typename S, typename M, int dim1, int dim2>
    inline Matrix<M, dim1, dim2> operator*(const S scalar, Matrix<M, dim1, dim2> &m) {
        Matrix<M, dim1, dim2> m2;
        for (int r = 0; r < dim1; ++r) {
            for (int c = 0; c < dim2; ++c) {
                m2[r][c] = scalar * m[r][c];
            }
        }
        return m2;
    }

    // Stream operator
    template <typename M, int dim1, int dim2>
    std::ostream &operator<<(std::ostream &os, const Matrix<M, dim1, dim2> &m) {
        os << "{" << std::endl;
        for (int r = 0; r < dim1; ++r) {
            for (int c = 0; c < dim2; ++c) {
                os << " " << m[r][c] << ", ";
            }
            os << std::endl;
        }
        os << "}";
        return os;
    }
}

#endif // D_MATRIX_H
