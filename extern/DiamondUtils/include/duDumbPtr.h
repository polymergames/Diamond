/*
    Copyright 2017 Ahnaf Siddiqui

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

#ifndef D_DUMB_PTR_H
#define D_DUMB_PTR_H

#include <memory>

namespace Diamond {
    /**
     * Wraps a pointer and a deleter. Does not automatically delete the pointer.
     * You have to free the pointer manually by calling dumbPtr.free().
     * Safe to copy and assign.
     */
    template <typename T, class Deleter = std::default_delete<T> >
    class DumbPtr {
    public:
        DumbPtr(T *ptr, Deleter d = Deleter()) : ptr(ptr), d(d) {}

        T *get() const { return ptr; }

        T &operator*() const { return *ptr; }

        T *operator->() const { return ptr; }

        void free() { d(ptr); ptr = nullptr; }

        explicit operator bool() const { return ptr != nullptr; }

    private:
        T *ptr;
        Deleter d;
    };

    // Comparison operators

    template <typename T, typename TD, typename U, typename UD>
    bool operator==(const DumbPtr<T,TD> &a, const DumbPtr<U,UD> &b) {
        return a.get() == b.get();
    }

    template <typename T, typename TD, typename U, typename UD>
    bool operator!=(const DumbPtr<T,TD> &a, const DumbPtr<U,UD> &b) {
        return a.get() != b.get();
    }

    template <typename T, typename TD, typename U, typename UD>
    bool operator<(const DumbPtr<T,TD> &a, const DumbPtr<U,UD> &b) {
        return a.get() < b.get();
    }

    template <typename T, typename TD, typename U, typename UD>
    bool operator>(const DumbPtr<T,TD> &a, const DumbPtr<U,UD> &b) {
        return a.get() > b.get();
    }

    template <typename T, typename TD, typename U, typename UD>
    bool operator<=(const DumbPtr<T,TD> &a, const DumbPtr<U,UD> &b) {
        return a.get() <= b.get();
    }

    template <typename T, typename TD, typename U, typename UD>
    bool operator>=(const DumbPtr<T,TD> &a, const DumbPtr<U,UD> &b) {
        return a.get() >= b.get();
    }
}

#endif // D_DUMB_PTR_H
