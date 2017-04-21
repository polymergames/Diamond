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

namespace Diamond {
    const float UI_EPSILON = 0.5; // in pixels
}

Diamond::UIView::UIView(const UIViewProps &props,
                        const DTransform2 &transform,
                        tD_pos width,
                        tD_pos height) :
m_props(props),
m_worldTransform(transform),
m_node(m_worldTransform),
m_width(width),
m_height(height) {}


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


void Diamond::UIView::updateLayout() {
    for (auto child: m_children) {
        child->updateLayout();
        
        switch (child->props().horizontalAlignment) {
            case UIViewProps::LEFT:
                child->localTransform().position.x =
                    m_props.leftPadding + child->props().leftMargin;
                break;
            case UIViewProps::CENTER:
                child->localTransform().position.x =
                    m_width / 2.0 - child->localWidth() / 2.0;
                break;
            case UIViewProps::RIGHT:
                child->localTransform().position.x =
                    m_width - m_props.rightPadding - child->props().rightMargin - child->localWidth();
                break;
            default:
                break;
        }
        
        switch (child->props().verticalAlignment) {
            case UIViewProps::TOP:
                child->localTransform().position.y =
                    m_props.topPadding + child->props().topMargin;
                break;
            case UIViewProps::CENTER:
                child->localTransform().position.y =
                    m_height / 2.0 - child->localHeight() / 2.0;
                break;
            case UIViewProps::BOTTOM:
                child->localTransform().position.y =
                    m_height - m_props.bottomPadding - child->props().bottomMargin - child->localHeight();
                break;
            default:
                break;
        }
    }
    
    if ((m_props.flags & UIViewProps::FIT_CONTENTS) && !m_children.empty()) {
        tD_pos minx = MAXFLOAT, miny = MAXFLOAT;
        tD_pos maxx = -MAXFLOAT, maxy = -MAXFLOAT;
        
        for (auto child : m_children) {
            Vector2<tD_pos> position(child->localTransform().position.x - child->props().leftMargin,
                                     child->localTransform().position.y - child->props().topMargin);
            auto width = child->localWidth() + child->props().leftMargin + child->props().rightMargin;
            auto height = child->localHeight() + child->props().topMargin + child->props().bottomMargin;
            
            if (position.x < minx)
                minx = position.x;
            
            if (position.y < miny)
                miny = position.y;
            
            if (position.x + width > maxx)
                maxx = position.x + width;
            
            if (position.y + height > maxy)
                maxy = position.y + height;
        }
        
        auto offsetx = minx - m_props.leftPadding;
        auto offsety = miny - m_props.topPadding;
        
        if (minx > UI_EPSILON || minx < -UI_EPSILON || miny > UI_EPSILON || miny < -UI_EPSILON) {
            // offset all children so that the minx, miny child is at this view's origin.
            for (auto child : m_children) {
                child->localTransform().position.x -= offsetx;
                child->localTransform().position.y -= offsety;
            }
            
            // NOTE: the code below is commented out for now,
            // so the children will be moved in world space to fit inside this parent.
            // move this view in the opposite direction of its children.
            // this way, in world space, the children stay where they already were,
            // but this parent view moves and resizes to fit the children.
//            m_node.localTransform().position.x += minx;
//            m_node.localTransform().position.y += miny;
        }
        
        // resize this view to fit its contents
        m_width = maxx - minx + m_props.leftPadding + m_props.rightPadding;
        m_height = maxy - miny + m_props.topPadding + m_props.bottomPadding;
    }
}


void Diamond::UIView::updateTransforms(const DTransform2 &parentTransform,
                                       const Matrix<tD_real, 2, 2> &parentTransMat) {
    m_node.updateAllWorldTransforms(parentTransform, parentTransMat);
}


bool Diamond::UIView::handleInput() {
    bool handled = false;
    
    if (Input::touch_down) {
        handled = handleTouchDown(Input::touch_pos) || handled;
    }
    if (Input::touch_drag) {
        handled = handleTouchDrag(Input::touch_pos) || handled;
    }
    if (Input::touch_up) {
        handled = handleTouchUp(Input::touch_pos) || handled;
    }
    
    return handled;
}


bool Diamond::UIView::handleTouchDown(const Vector2<tD_pos> &touchPos) {
    for (auto child : m_children) {
        if (child->inside(touchPos)) {
            child->handleTouchDown(touchPos);
            return true;
        }
    }
    return false;
}

bool Diamond::UIView::handleTouchDrag(const Vector2<tD_pos> &touchPos) {
    for (auto child : m_children) {
        if (child->inside(touchPos))
            child->handleTouchDrag(touchPos);
    }
    return false;
}

bool Diamond::UIView::handleTouchUp(const Vector2<tD_pos> &touchPos) {
    for (auto child : m_children) {
        if (child->inside(touchPos)) {
            child->handleTouchUp(touchPos);
            return true;
        }
    }
    return false;
}


bool Diamond::UIView::inside(const Vector2<tD_pos> &pos) const {
    return (pos.x >= m_worldTransform.position.x &&
            pos.x <= m_worldTransform.position.x + worldWidth() &&
            pos.y >= m_worldTransform.position.y &&
            pos.y <= m_worldTransform.position.y + worldHeight());
}
