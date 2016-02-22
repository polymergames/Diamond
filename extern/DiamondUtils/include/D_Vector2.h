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

#ifndef D_VECTOR_2_H
#define D_VECTOR_2_H

#include <cmath>
#include <iostream>

namespace Diamond {
    template <typename T>
    class Vector2 {
        public:
        T x, y;

        Vector2() : x(), y() {}
        
        Vector2(T x, T y) : x(x), y(y) {}

        void set(T x, T y) {
            this->x = x, this->y = y;
        }

        Vector2 &normalize() {
            T m = magnitude();
            if(m != 0)
                x /= m, y /= m;
            return *this;
        }

        template <typename V>
        Vector2 &add(const Vector2<V> &b) {
            x += b.x, y += b.y;
            return *this;
        }
        
        template <typename V>
        Vector2 &sub(const Vector2<V> &b) {
            x -= b.x, y -= b.y;
            return *this;
        }
        
        template <typename S>
        Vector2 &scalar(const S scalar) {
            x *= scalar, y *= scalar;
            return *this;
        }

        template <typename S>
        Vector2 &scalar(const S s1, const S s2) {
            x *= s1, y *= s2;
            return *this;
        }

        template <typename V>
        Vector2 &scalar(const Vector2<V> &b) {
            x *= b.x, y *= b.y;
            return *this;
        }

        T magnitudeSq() const {
            return x*x + y*y;
        }

        T magnitude() const {
            return std::sqrt(magnitudeSq());
        }

        template <typename V>
        T distanceSq(const Vector2<V> &b) const {
            return (b - *this).magnitudeSq();
        }

        template <typename V>
        T distance(const Vector2<V> &b) const {
            return (b - *this).magnitude();
        }

        // operator overloads
        template <typename V>
        Vector2 &operator=(const Vector2<V> &other) {
            x = other.x;
            y = other.y;
            return *this;
        }

        template <typename V>
        Vector2 operator+(const Vector2<V> &other) const {
            return Vector2(x + other.x, y + other.y);
        }

        template <typename V>
        Vector2 operator-(const Vector2<V> &other) const {
            return Vector2(x - other.x, y - other.y);
        }

        // Conversion operator
        template <typename V>
        operator Vector2<V>() const {
            return Vector2<V>(x, y);
        }
    };

    template <typename V, typename S>
    Vector2<V> operator*(const Vector2<V> &vec, const S scalar) {
        return Vector2<V>(vec.x * scalar, vec.y * scalar);
    }

    template <typename V, typename S>
    Vector2<V> operator*(const S scalar, const Vector2<V> &vec) {
        return vec * scalar;
    }

    template <typename V>
    std::ostream &operator<<(std::ostream &os, const Vector2<V> &vec) {
        os << "{" << vec.x << ", " << vec.y << "}";
        return os;
    }
}

#endif // D_VECTOR_2_H
