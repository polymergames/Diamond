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

#ifndef D_NODE2D_H
#define D_NODE2D_H

#include <vector>
#include "duMath.h" // for deg2rad and transMat
#include "D_Transform2.h"
#include "D_typedefs.h"

namespace Diamond {
    class Node2D;
    typedef std::vector<Node2D*> ChildList;

    class Node2D {
    public:
        // TODO: use reference to a transform, not pointer!
        Node2D(DTransform2 &world_transform);

        // Parenting troubles

        const ChildList &getChildren() const { return m_children; }

        /**
         Returns the given child after adding it to children.
        */
        Node2D &addChild(Node2D &child);
        Node2D *addChild(Node2D *child);

        /**
         Searches children for the given child and removes it from children.
         Returns true if child was found and removed, otherwise false.
        */
        bool removeChild(Node2D &child);
        bool removeChild(Node2D *child);


        // local transform
        DTransform2 &localTransform() { return m_localTransform; }
        const DTransform2 &localTransform() const { return m_localTransform; }

        // world transform
        DTransform2 &worldTransform() { return m_worldTransform; }
        const DTransform2 &worldTransform() const { return m_worldTransform; }

        // update transforms

        /**
         Updates all world transforms based on local transforms and parent world transforms
         in the tree rooted at this node.
        */
        void updateAllWorldTransforms();

        /**
         Updates all local transforms based on world transforms in the tree rooted at this node.
        */
        void updateAllLocalTransforms();


        void updateWorldTransform() { m_worldTransform = localToWorldSpace(m_localTransform); }

        void updateLocalTransform() { m_localTransform = worldToLocalSpace(m_worldTransform); }

        void updateParentTransform(const DTransform2 &parent_transform,
                                   const Matrix<tD_real, 2, 2> &parent_trans_mat) {
            m_parent_transform = parent_transform;
            m_parent_trans_mat = parent_trans_mat;
        }



        // transform conversion local->world

        /**
         Transforms a given point from the given local space 
         (specified by local space's origin in world space and transformation matrix) to world space.
        */
        template <typename P>
        static Vector2<P> localToWorldSpace(const Vector2<P> &local_coords, 
                                            const Vector2<P> &space_origin,
                                            const Matrix<tD_real, 2, 2> &space_trans_mat) {
            return local_coords.mul(space_trans_mat.m) + space_origin;
        }

        /**
         Transforms a given point from world space to the given local space 
         (specified by local space's origin in world space and transformation matrix).
        */
        template <typename P>
        static Vector2<P> worldToLocalSpace(const Vector2<P> &world_coords,
                                            const Vector2<P> &space_origin,
                                            const Matrix<tD_real, 2, 2> &space_trans_mat) {
            return (world_coords - space_origin.position).mul(space_trans_mat.inv().m);
        }

        /**
         Transforms a given transform object from this node's parent's local space to world space.
        */
        template <typename P, typename R, typename S>
        Transform2<P, R, S> localToWorldSpace(const Transform2<P, R, S> &local_trans) const {
            return Transform2<P, R, S>(
                localToWorldSpace(local_trans.position),
                localToWorldRotation(local_trans.rotation),
                localToWorldScale(local_trans.scale)
            );
        }

        /**
         Transforms a given point from this node's parent's local space to world space.
         TODO: test
        */
        template <typename P>
        Vector2<P> localToWorldSpace(const Vector2<P> &local_coords) const {
            return localToWorldSpace(local_coords, m_parent_transform.position, m_parent_trans_mat);
        }

        /**
         Transforms a given rotation from this node's parent's local space to world space.
        */
        template <typename R>
        R localToWorldRotation(R local_rot) const {
            return local_rot + m_parent_transform.rotation;
        }

        /**
         Transforms a given scale vector from this node's parent's local space to world space.
        */
        template <typename S>
        Vector2<S> localToWorldScale(const Vector2<S> &local_scale) const {
            return Vector2<S>(local_scale).scalar(m_parent_transform.scale);
        }


        // Transform conversion world->local

        /**
         Transforms a given transform object from world space to this node's parent's local space.
        */
        template <typename P, typename R, typename S>
        Transform2<P, R, S> worldToLocalSpace(const Transform2<P, R, S> &world_trans) const {
            return Transform2<P, R, S>(
                worldToLocalSpace(world_trans.position),
                worldToLocalRotation(world_trans.rotation),
                worldToLocalScale(world_trans.scale)
            );
        }

        /**
         Transforms a given point from world space to this node's parent's local space.
         TODO: test
        */
        template <typename P>
        Vector2<P> worldToLocalSpace(const Vector2<P> &world_coords) const {
            return (world_coords - m_parent_transform.position).mul(m_parent_trans_mat.inv().m);
        }

        /**
         Transforms a given rotation from world space to this node's parent's local space.
        */
        template <typename R>
        R worldToLocalRotation(R world_rot) const {
            return world_rot - m_parent_transform.rotation;
        }

        /**
         Transforms a given scale vector from world space to this node's parent's local space.
        */
        template <typename S>
        Vector2<S> worldToLocalScale(const Vector2<S> &world_scale) const {
            return Vector2<S>(world_scale).scalar(1.0 / m_parent_transform.scale.x, 1.0 / m_parent_transform.scale.y);
        }


        /**
         Get this node's world transformation matrix (not including translation).
        */
        Matrix<tD_real, 2, 2> getTransMat() const {
            return Math::transMat((tD_real)Math::deg2rad(m_worldTransform.rotation),
                                  (tD_real)m_worldTransform.scale.x,
                                  (tD_real)m_worldTransform.scale.y);
        }



    protected:
        DTransform2             m_localTransform;
        DTransform2             &m_worldTransform;

        DTransform2             m_parent_transform;
        Matrix<tD_real, 2, 2>   m_parent_trans_mat;

        ChildList m_children;
    };
}

#endif // D_NODE2D_H
