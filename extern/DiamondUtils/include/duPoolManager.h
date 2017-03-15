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

#ifndef DU_POOL_MANAGER_H
#define DU_POOL_MANAGER_H

#include "duDumbPtr.h"
#include "duMemPool.h"

namespace Diamond {

    /**
     Deleter that is constructed with a memory pool
     and, when called, frees the given pointer from the pool.
    */
    template <class PoolType, typename ElemType>
    class PoolDeleter {
    public:
        PoolDeleter(PoolType &pool) : m_pool(pool) {}

        void operator() (ElemType *ptr) const {
            m_pool.free(ptr);
        }

    private:
        PoolType &m_pool;
    };

    /**
     Like PoolDeleter but used with DumbPoolManager
    */
    template <class PoolType, typename ElemType>
    class DumbPoolDeleter : public DumbDeleter {
    public:
        DumbPoolDeleter(PoolType &pool) : m_pool(pool) {}

        void free(void *ptr) const override {
            m_pool.free((ElemType*)ptr);
        }

    private:
        PoolType &m_pool;
    };

    /**
     Memory pool container that generates smart pointers of
     the pooled object with a pool deleter.
    */
    template <typename ElemType,
              class PtrType,
              class Allocator = std::allocator<MemNode<ElemType> > >
    class PoolManager {
    public:
        PoolManager(size_t chunkSize = 10,
                    Allocator allocator = Allocator())
            : m_pool(chunkSize, allocator),
              m_deleter(m_pool) {}


        template <typename... Args>
        PtrType make(Args&&... args) {
            return PtrType(m_pool.make(std::forward<Args>(args)...),
                           m_deleter);
        }


    protected:
        MemPool<ElemType, Allocator> m_pool;
        PoolDeleter<MemPool<ElemType, Allocator>, ElemType> m_deleter;
    };

    /**
     Like PoolManager but for dumb pointers.
    */
    template <typename ElemType,
              class Allocator = std::allocator<MemNode<ElemType> > >
    class DumbPoolManager {
    public:
        DumbPoolManager(size_t chunkSize = 10,
                        Allocator allocator = Allocator())
            : m_pool(chunkSize, allocator),
              m_deleter(m_pool) {}

        template <typename... Args>
        DumbPtr<ElemType> make(Args&&... args) {
            return DumbPtr<ElemType>(m_pool.make(std::forward<Args>(args)...),
                                     &m_deleter);
        }

    protected:
        MemPool<ElemType, Allocator> m_pool;
        DumbPoolDeleter<MemPool<ElemType, Allocator>, ElemType> m_deleter;
    };
}

#endif // DU_POOL_MANAGER_H
