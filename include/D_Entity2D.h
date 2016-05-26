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
#include "D_typedefs.h"

namespace Diamond {
    /**
     A set of components and a 2D transform.
    */
    class Entity2D : public Entity {
    public:
        Entity2D(TransformList &transform_list)
            : m_transform_list(transform_list), m_transform_id(transform_list.emplace()) {}

        // We haven't perfected cloning yet
        // (and we don't plan to, it's creepy)
        Entity2D(const Entity2D&) = delete;
        Entity2D& operator=(const Entity2D&) = delete;

        virtual ~Entity2D() { m_transform_list.erase(m_transform_id); }


        Transform2<tD_pos, tD_rot> &transform() { return m_transform_list[m_transform_id]; }
        const Transform2<tD_pos, tD_rot> &transform() const { return m_transform_list[m_transform_id]; }

        transform2_id getTransformID() const { return m_transform_id; }

    protected:
        TransformList &m_transform_list;
        transform2_id m_transform_id;
    };
}

#endif // D_ENTITY2D_H
