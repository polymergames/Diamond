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

#ifndef DU_SPARSEVECTOR_H
#define DU_SPARSEVECTOR_H

#include <vector>
#include "duTypedefs.h"

namespace Diamond {
    /**
     A contiguous vector data structure with O(1) deletion at any point and
     ID references that are guaranteed valid for the lifetime of a referred element.
     Access is O(1) and faster than swapvector by a constant factor (and same as std::vector).
     Unlike swapvector, maintains order of elements and uses O(1) amortized auxiliary space, but
     leaves gaps of invalid data, and therefore should not be iterated directly.
     Please note that when an element is removed from a SparseVector, it is not necessarily
     destroyed / its destructor is not necessarily called immediately
     (but will be destroyed eventually).
    */
    template <class T, typename TID = tD_id>
    class SparseVector {
    public:

        // Accces functions

        T &operator[](TID id) { return objects[id]; }
        const T &operator[](TID id) const { return objects[id]; }

        T &at(TID id) { return objects.at(id); }
        const T &at(TID id) const { return objects.at(id); }


        /**
         Constructs an object and adds it to the collection.
         Returns an id that can be used to access the emplaced object using [] or at().
        */
        template <typename... Args>
        TID emplace(Args&&... args) {
            if (!free_id_stack.empty()) {
                TID new_id = free_id_stack.back();
                free_id_stack.pop_back();
                objects[new_id] = T(std::forward<Args>(args)...);
                return new_id;
            }
            else {
                objects.emplace_back(std::forward<Args>(args)...);
                return objects.size() - 1;
            }
        }


        /**
         Adds an object to the collection.
         Returns an id that can be used to access the new object using [] or at().
        */
        TID insert(const T &obj) {
            if (!free_id_stack.empty()) {
                TID new_id = free_id_stack.back();
                free_id_stack.pop_back();
                objects[new_id] = obj;
                return new_id;
            }
            else {
                objects.push_back(obj);
                return objects.size() - 1;
            }
        }

        // TODO: test if rvalue reference is being forwarded properly
        TID insert(T &&obj) {
            if (!free_id_stack.empty()) {
                TID new_id = free_id_stack.back();
                free_id_stack.pop_back();
                objects[new_id] = obj;
                return new_id;
            }
            else {
                objects.push_back(obj);
                return objects.size() - 1;
            }
        }


        /**
         Removes the object corresponding to the given id.
        */
        void erase(TID erase_id) { free_id_stack.push_back(erase_id); }


        /**
         Returns the total number of valid and invalid elements in the vector.
        */
        TID size() { return objects.size(); }


        /**
         Deletes everything.
        */
        void clear() {
            objects.clear();
            free_id_stack.clear();
        }

    private:
        std::vector<T> objects;
        std::vector<TID> free_id_stack;
    };
}

#endif // DU_SPARSEVECTOR_H
