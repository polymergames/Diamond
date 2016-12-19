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

#include "D_Node2D.h"

#include <algorithm> // ?


Diamond::Node2D::Node2D(DTransform2 &world_transform)
    : m_localTransform(world_transform), 
      m_worldTransform(world_transform) {}



Diamond::Node2D &Diamond::Node2D::addChild(Node2D &child) {
    return *(addChild(&child));
}

Diamond::Node2D *Diamond::Node2D::addChild(Node2D *child) {
    if (child && child != this)
        m_children.push_back(child);

    child->updateLocalTransform(m_worldTransform, transformationMatrix());

    return child;
}


bool Diamond::Node2D::removeChild(Node2D &child) {
    return removeChild(&child);
}

bool Diamond::Node2D::removeChild(Node2D *child) {
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        m_children.erase(it);
        return true;
    }
    return false;
}



void Diamond::Node2D::updateAllWorldTransforms(const DTransform2 &parent_transform,
                                               const Matrix<tD_real, 2, 2> &parent_trans_mat) {
    updateWorldTransform(parent_transform, parent_trans_mat);

    auto transMat = transformationMatrix();

    for (auto child : m_children) {
        child->updateAllWorldTransforms(m_worldTransform, transMat);
    }
}


void Diamond::Node2D::updateAllLocalTransforms(const DTransform2 &parent_transform,
                                               const Matrix<tD_real, 2, 2> &parent_trans_mat) {
    updateLocalTransform(parent_transform, parent_trans_mat);

    auto transMat = transformationMatrix();

    for (auto child : m_children) {
        child->updateAllLocalTransforms(m_worldTransform, transMat);
    }
}
