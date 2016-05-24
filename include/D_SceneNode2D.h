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

#ifndef D_SCENE_NODE2D_H
#define D_SCENE_NODE2D_H

#include <vector>
#include "duMatrix.h"
#include "D_Transform2.h"
#include "D_typedefs.h"

namespace Diamond {
    typedef std::vector<SceneNode2D*> ChildList;

    class SceneNode2D {
    public:
        SceneNode2D(TransformList &transform_list, transform2_id world_transform_id);

        // children

        const ChildList &getChildren() const { return m_children; }

        /**
         Returns the given child after adding it to children.
        */
        SceneNode2D &addChild(SceneNode2D &child);
        SceneNode2D *addChild(SceneNode2D *child);

        /**
         Searches children for the given child and removes it from children.
         Returns true if child was found and removed, otherwise false.
        */
        bool removeChild(SceneNode2D &child);
        bool removeChild(SceneNode2D *child);



        // local transform

        Transform2<tD_pos, tD_rot> &localTransform() { return m_local_transform; }
        const Transform2<tD_pos, tD_rot> &localTransform() const { return m_local_transform; }


        // world transform

        Transform2<tD_pos, tD_rot> &worldTransform() { return m_transform_list[m_world_transform_id]; }
        const Transform2<tD_pos, tD_rot> &worldTransform() const { return m_transform_list[m_world_transform_id]; }

        transform2_id getWorldTransformID() const { return m_world_transform_id; }



        // update transforms

        void updateWorldTransform() { worldTransform() = localToWorldSpace(m_local_transform); }

        void updateLocalTransform() { m_local_transform = worldToLocalSpace(worldTransform()); }

        void updateParentTransform(const Transform2<tD_pos, tD_rot> &parent_transform,
                                   const Matrix<tD_real, 2, 2> &parent_trans_mat);



        // transform conversion local-> world

        /**
         Transforms a given transform object from this node's local space to world space.
        */
        Transform2<tD_pos, tD_rot> localToWorldSpace(const Transform2<tD_pos, tD_rot> &local_trans) const {
            return Transform2<tD_pos, tD_rot>(
                localToWorldSpace(local_trans.position), 
                localToWorldRotation(local_trans.rotation), 
                localToWorldScale(local_trans.scale));
        }

        /**
         Transforms a given point from this node's local space to world space.
         TODO: test
        */
        template <typename V>
        Vector2<V> localToWorldSpace(const Vector2<V> &local_coords) const {
            return local_coords.mul(m_parent_trans_mat.m) + m_parent_transform.position;
        }

        /**
         Transforms a given rotation from this node's local space to world space.
        */
        template <typename R>
        R localToWorldRotation(R local_rot) const {
            return local_rot + m_parent_transform.rotation;
        }

        /**
         Transforms a given scale vector from this node's local space to world space.
        */
        template <typename S>
        Vector2<S> localToWorldScale(const Vector2<S> &local_scale) const {
            return Vector2<tD_real>(local_scale).scalar(m_parent_transform.scale);
        }


        // Transform conversion world->local

        /**
         Transforms a given transform object from world space to this node's local space.
        */
        Transform2<tD_pos, tD_rot> worldToLocalSpace(const Transform2<tD_pos, tD_rot> &world_trans) const {
            return Transform2<tD_pos, tD_rot>(
                worldToLocalSpace(world_trans.position),
                worldToLocalRotation(world_trans.rotation), 
                worldToLocalScale(world_trans.scale));
        }

        /**
         Transforms a given point from world space to this node's local space.
         TODO: test
        */
        template <typename V>
        Vector2<V> worldToLocalSpace(const Vector2<V> &world_coords) const {
            return (world_coords - m_parent_transform.position).mul(m_parent_trans_mat.inv().m);
        }
        
        /**
         Transforms a given rotation from world space to this node's local space.
        */
        template <typename R>
        R worldToLocalRotation(R world_rot) const {
            return world_rot - m_parent_transform.rotation;
        }

        /**
         Transforms a given scale vector from world space to this node's local space.
        */
        template <typename S>
        Vector2<S> worldToLocalScale(const Vector2<S> &world_scale) const {
            return Vector2<S>(world_scale).scalar(1.0 / m_parent_transform.scale.x, 1.0 / m_parent_transform.scale.y);
        }


        /**
         Get this node's world transformation matrix (not including translation).
        */
        Matrix<tD_real, 2, 2> getTransMat() const;



    private:
        Transform2<tD_pos, tD_rot> m_local_transform;
        TransformList &m_transform_list;
        transform2_id m_world_transform_id;

        Transform2<tD_pos, tD_rot> m_parent_transform;
        Matrix<tD_real, 2, 2> m_parent_trans_mat;

        ChildList m_children;
    };
}

#endif // D_SCENE_NODE2D_H
