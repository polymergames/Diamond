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

#ifndef DU_SWAPVECTOR_H
#define DU_SWAPVECTOR_H

#include <vector>
#include "duTypedefs.h"

namespace Diamond {
    /**
     A contiguous vector data structure with O(1) deletion at any point and 
     ID references that are guaranteed valid for the lifetime of a referred element.
     Access is O(1) but with higher constant factor than std::vector.
     Does not maintain order of elements, and uses O(n) auxiliary space.
    */
    template <class T, typename TID = tD_id>
    class SwapVector {
    public:

        // Access and iterator functions

        T &operator[](TID id) { return objects[id_index_map[id]]; }
        const T &operator[](TID id) const { return objects[id_index_map[id]]; }

        T &at(TID id) { return objects.at(id_index_map.at(id)); }
        const T &at(TID id) const { return objects.at(id_index_map.at(id)); }

        typename std::vector<T>::iterator begin() { return objects.begin(); }
        typename std::vector<T>::iterator end() { return objects.end(); }
        
        typename std::vector<T>::const_iterator begin() const { return objects.begin(); }
        typename std::vector<T>::const_iterator end() const { return objects.end(); }

        typename std::vector<T>::const_iterator cbegin() const { return objects.cbegin(); }
        typename std::vector<T>::const_iterator cend() const { return objects.cend(); }


        /**
         Constructs an object and adds it to the collection. 
         Returns an id that can be used to access the emplaced object using [] or at().
        */
        template <typename... Args>
        TID emplace(Args&&... args) {
            return emplace_back(std::forward<Args>(args)...);
        }

        template <typename... Args>
        TID emplace_back(Args&&... args) {
            TID new_id;

            if (!free_id_stack.empty()) {
                new_id = free_id_stack.back();
                free_id_stack.pop_back();
                id_index_map[new_id] = objects.size();
            }
            else {
                new_id = id_index_map.size();
                id_index_map.push_back(objects.size());
            }

            objects.emplace_back(std::forward<Args>(args)...);
            index_id_map.push_back(new_id);

            return new_id;
        }


        /**
         Adds an object to the collection.
         Returns an id that can be used to access the new object using [] or at().
        */
        TID insert(const T &obj) { return push_back(obj); }

        TID insert(T &&obj) { return push_back(obj); }

        TID push_back(const T &obj) {
            TID new_id = genNewID();
            objects.push_back(obj);
            return new_id;
        }

        // TODO: test if rvalue reference is being forwarded properly
        TID push_back(T &&obj) {
            TID new_id = genNewID();
            objects.push_back(obj);
            return new_id;
        }


        /**
         Removes the object corresponding to the given id.
        */
        void erase(TID erase_id) {
            TID index = id_index_map[erase_id];

            // If in middle of vector, replace it with last element in vector
            if (index < objects.size() - 1) {
                objects[index] = std::move(objects.back());
                id_index_map[index_id_map.back()] = index;
                index_id_map[index] = index_id_map.back();
            }

            objects.pop_back();
            index_id_map.pop_back();
            free_id_stack.push_back(erase_id);
        }


        /**
         Returns the number of elements in the vector.
        */
        TID size() { return objects.size(); }


        /**
         Returns a direct reference to the internal vector.
        */
        std::vector<T> &data() { return objects; }
        const std::vector<T> &data() const { return objects; }

    private:
        std::vector<T> objects;

        std::vector<TID> id_index_map;
        std::vector<TID> index_id_map;
        std::vector<TID> free_id_stack;


        TID genNewID() {
            TID new_id;

            if (!free_id_stack.empty()) {
                new_id = free_id_stack.back();
                free_id_stack.pop_back();
                id_index_map[new_id] = objects.size();
            }
            else {
                new_id = id_index_map.size();
                id_index_map.push_back(objects.size());
            }

            index_id_map.push_back(new_id);

            return new_id;
        }
    };
}

#endif // DU_SWAPVECTOR_H
