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

#ifndef DU_MEM_POOL_H
#define DU_MEM_POOL_H

#include <memory>

namespace Diamond {

    /**
     Linked list node that stores either an element of the
     list or a pointer to the next element.
    */
    template <typename T>
    union MemNode {
        MemNode() : next(nullptr) {}

        T elem;
        MemNode<T> *next;
    };


    /**
     A type-aware memory pool that allocates memory chunks of a fixed chunk size.
     
     Note: this class does not call all destructors of the elements in its memory pool
     when it goes out of scope. It does free the memory, but the user has the responsibility
     of calling MemPool::free on every pool object that needs to be destroyed.
    */
    // TODO: memory align?
    template <typename ElemType, class Allocator = std::allocator<MemNode<ElemType> > >
    class MemPool {
    public:
        using TNode = MemNode<ElemType>;

        MemPool(size_t chunkSize = 10, 
                Allocator allocator = Allocator()) 
            : m_data(nullptr), 
              m_freeHead(nullptr),
              m_chunkSize(chunkSize), 
              m_allocator(allocator) {
            
            m_data = allocateChunk(m_chunkSize);
            if (m_data)
                initChunk(m_data, m_chunkSize);

            m_freeHead = m_data; // first element of free list is beginning of data chunk
        }

        ~MemPool() {
            TNode *p;

            // delete all memory chunks
            while (m_data) {
                p = getNextChunk(m_data, m_chunkSize);
                deallocateChunk(m_data, m_chunkSize);
                m_data = p;
            }
        }


        template <typename... Args>
        ElemType *make(Args&&... args) {
            if (!m_freeHead) // this means there was a memory error
                return nullptr;
            
            if (m_freeHead->next == nullptr) {
                // No more free space available in existing chunks, 
                // so allocate a new chunk and point the last chunk to it.
                TNode *newChunk = allocateChunk(m_chunkSize);
                if (newChunk) {                    
                    initChunk(newChunk, m_chunkSize);
                    
                    // The last node of the previously used chunk
                    // points to the new chunk
                    m_freeHead->next = newChunk;

                    m_freeHead = newChunk;
                }
                else {
                    return nullptr;
                }
            }

            TNode *ret = m_freeHead;
            m_freeHead = m_freeHead->next;

            new (&(ret->elem)) ElemType(std::forward<Args>(args)...);

            return &(ret->elem);
        }


        void free(ElemType *ptr) {
            if (ptr) {
                ptr->~ElemType();

                // The current head of the free list becomes the second element,
                // and the freed pointer becomes the new head
                TNode *freed = new (ptr) TNode();
                freed->next = m_freeHead;
                m_freeHead = freed;
            }
        }

    protected:
        TNode *allocateChunk(size_t chunkSize) {
            return m_allocator.allocate(chunkSize + 1); // + 1 to hold pointer to next chunk
        }

        void deallocateChunk(TNode *chunk, size_t chunkSize) {
            m_allocator.deallocate(chunk, chunkSize + 1);
        }

        void initChunk(TNode *chunk, size_t chunkSize) {
            // point all free list elements to the next adjacent space in the chunk
            TNode *p = chunk;
            while (p < chunk + chunkSize) {
                p->next = p + 1;
                ++p;
            }

            // the last element does not have a next
            p->next = nullptr;
        }

        // Get pointer to the next chunk in a series of chunks
        TNode *getNextChunk(TNode *startChunk, size_t chunkSize) const {
            return (startChunk + chunkSize)->next;
        }


        TNode *m_data; // Pointer to first memory chunk
        TNode *m_freeHead; // Pointer to first element of free list

        size_t m_chunkSize;
        Allocator m_allocator;
    };
}

#endif // DU_MEM_POOL_H
