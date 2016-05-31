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

#ifndef D_ENTITY_NODE2D_H
#define D_ENTITY_NODE2D_H

#include "D_Entity.h"
#include "D_Node2D.h"

namespace Diamond {
    /**
     Combines the functionality of an entity-component system and a scene graph node.
     Yeah that's right, we used multiple inheritance. Fight me.
    */
    class EntityNode2D : public Entity, public Node2D {
    public:
        EntityNode2D(TransformList &transform_list)
            : Node2D(transform_list) {}

        EntityNode2D(TransformList &transform_list, transform2_id world_transform_id)
            : Node2D(transform_list, world_transform_id) {}

        EntityNode2D(const EntityNode2D&) = delete;
        EntityNode2D& operator=(const EntityNode2D&) = delete;

        virtual ~EntityNode2D() { m_transform_list.erase(getWorldTransformID()); }
    };
}

#endif // D_ENTITY_NODE2D_H
