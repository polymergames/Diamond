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
    class DumbDeleter {
    public:
        virtual ~DumbDeleter() {}

        virtual void free(void *ptr) const = 0;
    };

    /**
     * Wraps a pointer and a pointer to a deleter of base type DumbDeleter.
     * This means that the actual deleter object must be stored externally
     * and outlive this dumb pointer.
     * Does not automatically free the stored pointer.
     * You have to free the pointer manually by calling dumbPtr.free(),
     * which will call deleter->free(ptr).
     * Safe to copy and assign.
     */
    template <typename T>
    class DumbPtr {
    public:
        DumbPtr() : ptr(nullptr), d(nullptr) {}
        DumbPtr(std::nullptr_t p) : ptr(p), d(nullptr) {}

        DumbPtr(T *ptr) : ptr(ptr), d(nullptr) {}

        DumbPtr(T *ptr, const DumbDeleter *d) : ptr(ptr), d(d) {}

        // implicit converting constructor
        template <typename Y>
        DumbPtr(const DumbPtr<Y> &p) : ptr(p.get()), d(p.get_deleter()) {}

        T *get() const { return ptr; }

        const DumbDeleter *get_deleter() const { return d; }

        T &operator*() const { return *ptr; }

        T *operator->() const { return ptr; }

        void free() {
            if (d)  d->free(ptr);
            else    delete ptr;
            ptr = nullptr;
        }

        explicit operator bool() const { return ptr != nullptr; }

        // conversion operator
        operator T*() const {
            return ptr;
        }

    private:
        T *ptr;
        const DumbDeleter *d;
    };

    // Casting

    // template <typename T, typename TD, typename U, typename UD>
    // DumbPtr<T, TD> static_pointer_cast(const DumbPtr<U, UD> &ptr) noexcept {
    //     return DumbPtr<T, TD>(static_cast<T*>(ptr.get()), ptr.get_deleter);
    // }
    //
    // template <typename T, typename TD, typename U, typename UD>
    // DumbPtr<T, TD> dynamic_pointer_cast(const DumbPtr<U, UD> &ptr) noexcept {
    //     return DumbPtr<T, TD>(dynamic_cast<T*>(ptr.get()), ptr.get_deleter);
    // }
    //
    // template <typename T, typename TD, typename U, typename UD>
    // DumbPtr<T, TD> const_pointer_cast(const DumbPtr<U, UD> &ptr) noexcept {
    //     return DumbPtr<T, TD>(const_cast<T*>(ptr.get()), ptr.get_deleter);
    // }
    //
    // template <typename T, typename TD, typename U, typename UD>
    // DumbPtr<T, TD> reinterpret_pointer_cast(const DumbPtr<U, UD> &ptr) noexcept {
    //     return DumbPtr<T, TD>(reinterpret_cast<T*>(ptr.get()), ptr.get_deleter);
    // }

    // Comparison operators

    template <typename T, typename U>
    bool operator==(const DumbPtr<T> &a, const DumbPtr<U> &b) {
        return a.get() == b.get();
    }

    template <typename T, typename U>
    bool operator!=(const DumbPtr<T> &a, const DumbPtr<U> &b) {
        return a.get() != b.get();
    }

    template <typename T, typename U>
    bool operator<(const DumbPtr<T> &a, const DumbPtr<U> &b) {
        return a.get() < b.get();
    }

    template <typename T, typename U>
    bool operator>(const DumbPtr<T> &a, const DumbPtr<U> &b) {
        return a.get() > b.get();
    }

    template <typename T, typename U>
    bool operator<=(const DumbPtr<T> &a, const DumbPtr<U> &b) {
        return a.get() <= b.get();
    }

    template <typename T, typename U>
    bool operator>=(const DumbPtr<T> &a, const DumbPtr<U> &b) {
        return a.get() >= b.get();
    }


    template <typename T>
    bool operator==(const DumbPtr<T> &a, std::nullptr_t b) {
        return a.get() == b;
    }
    template <typename T>
    bool operator==(std::nullptr_t a, const DumbPtr<T> &b) {
        return a == b.get();
    }

    template <typename T>
    bool operator!=(const DumbPtr<T> &a, std::nullptr_t b) {
        return a.get() != b;
    }
    template <typename T>
    bool operator!=(std::nullptr_t a, const DumbPtr<T> &b) {
        return a != b.get();
    }

    template <typename T>
    bool operator<(const DumbPtr<T> &a, std::nullptr_t b) {
        return a.get() < b;
    }
    template <typename T>
    bool operator<(std::nullptr_t a, const DumbPtr<T> &b) {
        return a < b.get();
    }

    template <typename T>
    bool operator>(const DumbPtr<T> &a, std::nullptr_t b) {
        return a.get() > b;
    }
    template <typename T>
    bool operator>(std::nullptr_t a, const DumbPtr<T> &b) {
        return a > b.get();
    }

    template <typename T>
    bool operator<=(const DumbPtr<T> &a, std::nullptr_t b) {
        return a.get() <= b;
    }
    template <typename T>
    bool operator<=(std::nullptr_t a, const DumbPtr<T> &b) {
        return a <= b.get();
    }

    template <typename T>
    bool operator>=(const DumbPtr<T> &a, std::nullptr_t b) {
        return a.get() >= b;
    }
    template <typename T>
    bool operator>=(std::nullptr_t a, const DumbPtr<T> &b) {
        return a >= b.get();
    }
}

#endif // D_DUMB_PTR_H
