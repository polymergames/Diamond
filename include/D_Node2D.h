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

    // TODO: how can we make Node transformations cooperate with physics engine-driven movements?
    // since physics engine ignores node relationships and moves everything in world space
    // perhaps require a separate physics engine for tree-aware physics?
    // otherwise, have to do manual syncing of local and world transforms of tree nodes with physics engine
    // at different times, not elegant or user friendly
    class Node2D {
    public:
        Node2D(DTransform2 &world_transform);


        // ======= Parenting troubles =======

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



        // ======= More than meets the eye =======

        /** 
         This node's local transform
        */
        DTransform2 &localTransform() { return m_localTransform; }
        const DTransform2 &localTransform() const { return m_localTransform; }

        /**
         This node's world transform
        */
        DTransform2 &worldTransform() { return m_worldTransform; }
        const DTransform2 &worldTransform() const { return m_worldTransform; }

        /**
         This node's world transformation matrix (not including translation).
        */
        Matrix<tD_real, 2, 2> transformationMatrix() const {
            return Math::transMat((tD_real)Math::deg2rad(m_worldTransform.rotation),
                                  (tD_real)m_worldTransform.scale.x,
                                  (tD_real)m_worldTransform.scale.y);
        }



        // ======= Update transforms =======
        
        /**
         Updates all world transforms based on local transforms and parent world transforms
         in the tree rooted at this node.
        */
        void updateAllWorldTransforms(const DTransform2 &parent_transform = DTransform2(),
                                      const Matrix<tD_real, 2, 2> &parent_trans_mat = { { { 1, 0 },{ 0, 1 } } });

        /**
         Updates this node's world transform based on its local transform and the given parent world transform.
        */
        void updateWorldTransform(const DTransform2 &parent_transform, 
                                  const Matrix<tD_real, 2, 2> &parent_trans_mat)
        { m_worldTransform = Node2D::localToWorldSpace(m_localTransform, parent_transform, parent_trans_mat); }


        /**
         Updates all local transforms based on world transforms and parent world transforms
         in the tree rooted at this node.
        */
        void updateAllLocalTransforms(const DTransform2 &parent_transform = DTransform2(),
                                      const Matrix<tD_real, 2, 2> &parent_trans_mat = { { { 1, 0 },{ 0, 1 } } });
        
        /**
         Updates this node's local transform based on its world transform and the given parent world transform.
        */
        void updateLocalTransform(const DTransform2 &parent_transform,
                                  const Matrix<tD_real, 2, 2> &parent_trans_mat) 
        { m_localTransform = Node2D::worldToLocalSpace(m_worldTransform, parent_transform, parent_trans_mat); }



        // ======= Transform conversion local->world =======

        /**
         Transforms a given transform object from the given local space
         (specified by the local space's origin and transform in world space) to world space.
        */
        template <typename P, typename R, typename S>
        static Transform2<P, R, S> localToWorldSpace(const Transform2<P, R, S> &local_trans,
                                                     const Transform2<P, R, S> &space_origin,
                                                     const Matrix<tD_real, 2, 2> &space_trans_mat) {
            return Transform2<P, R, S>(
                localToWorldSpace(local_trans.position, space_origin.position, space_trans_mat),
                localToWorldRotation(local_trans.rotation, space_origin.rotation),
                localToWorldScale(local_trans.scale, space_origin.scale)
            );
        }

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
         Transforms a given rotation from the given local space
         (specified by local space's rotation in world space) to world space.
        */
        template <typename R>
        static R localToWorldRotation(R local_rot, R space_rot) {
            return local_rot + space_rot;
        }

        /**
         Transforms a given scale from the given local space
         (specified by local space's scale in world space) to world space.
        */
        template <typename S>
        static Vector2<S> localToWorldScale(const Vector2<S> &local_scale,
                                            const Vector2<S> &space_scale) {
            return Vector2<S>(local_scale).scalar(space_scale);
        }


        /**
         Transforms a given transform object from this node's local space to world space.
        */
        template <typename P, typename R, typename S>
        Transform2<P, R, S> localToWorldSpace(const Transform2<P, R, S> &local_trans) const {
            return Node2D::localToWorldSpace(local_trans, m_worldTransform, transformationMatrix());
        }

        /**
         Transforms a given point from this node's parent's local space to world space.
        */
        template <typename P>
        Vector2<P> localToWorldSpace(const Vector2<P> &local_coords) const {
            return Node2D::localToWorldSpace(local_coords, m_worldTransform.position, transformationMatrix());
        }

        /**
         Transforms a given rotation from this node's parent's local space to world space.
        */
        template <typename R>
        R localToWorldRotation(R local_rot) const {
            return Node2D::localToWorldRotation(local_rot, m_worldTransform.rotation);
        }

        /**
         Transforms a given scale vector from this node's parent's local space to world space.
        */
        template <typename S>
        Vector2<S> localToWorldScale(const Vector2<S> &local_scale) const {
            return Node2D::localToWorldScale(local_scale, m_worldTransform.scale);
        }



        // ======= Transform conversion world->local =======

        /**
         Transforms a given transform object from world space to the given local space
         (specified by the local space's origin and transform in world space).
        */
        template <typename P, typename R, typename S>
        static Transform2<P, R, S> worldToLocalSpace(const Transform2<P, R, S> &world_trans,
                                                     const Transform2<P, R, S> &space_origin,
                                                     const Matrix<tD_real, 2, 2> &space_trans_mat) {
            return Transform2<P, R, S>(
                worldToLocalSpace(world_trans.position, space_origin.position, space_trans_mat),
                worldToLocalRotation(world_trans.rotation, space_origin.rotation),
                worldToLocalScale(world_trans.scale, space_origin.scale)
            );
        }

        /**
         Transforms a given point from world space to the given local space 
         (specified by local space's origin in world space and transformation matrix).
        */
        template <typename P>
        static Vector2<P> worldToLocalSpace(const Vector2<P> &world_coords,
                                            const Vector2<P> &space_origin,
                                            const Matrix<tD_real, 2, 2> &space_trans_mat) {
            return (world_coords - space_origin).mul(space_trans_mat.inv().m);
        }

        /**
         Transforms a given rotation from world space to the given local space
         (specified by local space's rotation in world space).
        */
        template <typename R>
        static R worldToLocalRotation(R world_rot, R space_rot) {
            return world_rot - space_rot;
        }

        /**
         Transforms a given scale from world space to the given local space
         (specified by local space's scale in world space).
        */
        template <typename S>
        static Vector2<S> worldToLocalScale(const Vector2<S> &world_scale,
                                            const Vector2<S> &space_scale) {
            return Vector2<S>(world_scale).scalar(1.0 / space_scale.x, 1.0 / space_scale.y);
        }


        /**
         Transforms a given transform object from world space to this node's parent's local space.
        */
        template <typename P, typename R, typename S>
        Transform2<P, R, S> worldToLocalSpace(const Transform2<P, R, S> &world_trans) const {
            return Node2D::worldToLocalSpace(world_trans, m_worldTransform.position, transformationMatrix());
        }

        /**
         Transforms a given point from world space to this node's parent's local space.
        */
        template <typename P>
        Vector2<P> worldToLocalSpace(const Vector2<P> &world_coords) const {
            return Node2D::worldToLocalSpace(world_coords, m_worldTransform.position, transformationMatrix());
        }

        /**
         Transforms a given rotation from world space to this node's parent's local space.
        */
        template <typename R>
        R worldToLocalRotation(R world_rot) const {
            return Node2D::worldToLocalRotation(world_rot, m_worldTransform.rotation);
        }

        /**
         Transforms a given scale vector from world space to this node's parent's local space.
        */
        template <typename S>
        Vector2<S> worldToLocalScale(const Vector2<S> &world_scale) const {
            return Node2D::worldToLocalScale(world_scale, m_worldTransform.scale);
        }


    protected:
        DTransform2 m_localTransform;
        DTransform2 &m_worldTransform;
        ChildList   m_children;
    };
}

#endif // D_NODE2D_H
