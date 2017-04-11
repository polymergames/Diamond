/*
    Copyright 2017 Ahnaf Siddiqui

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

#include "D_UIView.h"
#include "D_Input.h"

Diamond::UIView::UIView(DTransform2 transform,
                        tD_pos width,
                        tD_pos height) :
m_worldTransform(transform),
m_node(m_worldTransform),
m_width(width),
m_height(height) {}


void Diamond::UIView::update() {
    updateTransforms();
    updateState();
    handleInput();
}


Diamond::UIView &Diamond::UIView::addChild(Diamond::UIView &child) {
    return *(addChild(&child));
}

Diamond::UIView *Diamond::UIView::addChild(Diamond::UIView *child) {
    if (child && child != this)
        m_children.push_back(child);
    
    m_node.addChild(child->m_node);
    
    return child;
}


bool Diamond::UIView::removeChild(Diamond::UIView &child) {
    return removeChild(&child);
}

bool Diamond::UIView::removeChild(Diamond::UIView *child) {
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        m_children.erase(it);
        m_node.removeChild(child->m_node);
        return true;
    }
    return false;
}


void Diamond::UIView::updateTransforms(const DTransform2 &parent_transform,
                                       const Matrix<tD_real, 2, 2> &parent_trans_mat) {
    m_node.updateAllWorldTransforms(parent_transform, parent_trans_mat);
}


void Diamond::UIView::handleInput() {
    if (Input::touch_down) {
        handleTouchDown(Input::touch_pos);
    }
    if (Input::touch_drag) {
        handleTouchDrag(Input::touch_pos);
    }
    if (Input::touch_up) {
        handleTouchUp(Input::touch_pos);
    }
}


void Diamond::UIView::handleTouchDown(const Vector2<tD_pos> &touchPos) {
    for (auto child : m_children) {
        if (child->inside(touchPos))
            child->handleTouchDown(touchPos);
    }
}

void Diamond::UIView::handleTouchDrag(const Vector2<tD_pos> &touchPos) {
    for (auto child : m_children) {
        if (child->inside(touchPos))
            child->handleTouchDrag(touchPos);
    }
}

void Diamond::UIView::handleTouchUp(const Vector2<tD_pos> &touchPos) {
    for (auto child : m_children) {
        if (child->inside(touchPos))
            child->handleTouchUp(touchPos);
    }
}


bool Diamond::UIView::inside(const Vector2<tD_pos> &pos) const {
    return (pos.x >= m_worldTransform.position.x &&
            pos.x <= m_worldTransform.position.x + worldWidth() &&
            pos.y >= m_worldTransform.position.y &&
            pos.y <= m_worldTransform.position.y + worldHeight());
}
