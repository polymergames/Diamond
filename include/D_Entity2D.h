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

#ifndef D_ENTITY2D_H
#define D_ENTITY2D_H

#include "D_Entity.h"
#include "D_Transform2.h"
#include "D_typedefs.h"

namespace Diamond {
    /**
     A set of components and a 2D transform.
    */
    class Entity2D : public Entity {
    public:
        Entity2D(const Transform2Ptr &transform) 
            : m_transform(transform) {}

        virtual ~Entity2D() {}

        DTransform2 &transform() { return *m_transform; }
        const DTransform2 &transform() const { return *m_transform; }

        // TODO: make this (and other const functions)
        // return a const smart pointer!
        // (ex. ConstTransform2Ptr)
        const Transform2Ptr &getTransformPtr() const {
            return m_transform;
        }

    protected:
        Transform2Ptr m_transform;
    };
}

#endif // D_ENTITY2D_H
