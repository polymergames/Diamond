/*
 * Copyright 2017 Ahnaf Siddiqui
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "D_UIStack.h"


Diamond::UIStack::UIStack(const UIViewProps &viewProps,
                          const UIStackProps &stackProps,
                          const DTransform2 &transform,
                          tD_pos width,
                          tD_pos height) :
Diamond::UIView(viewProps,transform, width, height), m_stackProps(stackProps) {}


void Diamond::UIStack::updateLayout() {
    // update the layouts of the children
    for (auto child : m_children) {
        if (child->isActive())
            child->updateLayout();
    }
    
    // stack up the children!
    switch (m_stackProps.orientation) {
        case UIStackProps::VERTICAL:
        {
            // vertically oriented stack
            
            // the current height where the next stack element will be added
            tD_pos top = m_props.topPadding;
            
            // calculate the width of the stack,
            // which is the width of the widest element
            // in the stack.
            m_width = m_props.leftPadding + m_props.rightPadding;
            for (auto child : m_children) {
                auto childWidth =
                    m_props.leftPadding + child->props().leftMargin +
                    child->localWidth() + child->props().rightMargin +
                    m_props.rightPadding;
                
                if (childWidth > m_width)
                    m_width = childWidth;
            }
            
            // position and align the elements of the stack
            for (auto child : m_children) {
                // vertical positioning
                child->localTransform().position.y =
                    top + child->props().topMargin;
                
                top = child->localTransform().position.y +
                      child->localHeight() + child->props().bottomMargin +
                      m_stackProps.spacing;
                
                // horizontal positioning
                switch (m_stackProps.stackAlignment) {
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
                            m_width - m_props.rightPadding -
                            child->props().rightMargin - child->localWidth();
                        break;
                    default:
                        break;
                }
            }
            
            if (!m_children.empty()) {
                // there should not be spacing between the last element
                // of the stack and the bottom,
                // besides the stack's padding.
                top -= m_stackProps.spacing;
            }
            
            // set the stack's rect height
            m_height = top + m_props.bottomPadding;
        }
            break;
        case UIStackProps::HORIZONTAL:
        {
            // horizontally oriented stack
            // TODO
            
            // the current horizontal position where the next stack element
            // will be added.
            tD_pos left = m_props.leftPadding;
            
            // calculate the height of the stack,
            // which is the height of the tallest element
            // in the stack.
            m_height = m_props.topPadding + m_props.bottomPadding;
            for (auto child : m_children) {
                auto childHeight =
                    m_props.topPadding + child->props().topMargin +
                    child->localHeight() + child->props().bottomMargin +
                    m_props.bottomPadding;
                
                if (childHeight > m_height)
                    m_height = childHeight;
            }
            
            // position and align the elements of the stack
            for (auto child : m_children) {
                // horizontal positioning
                child->localTransform().position.x =
                    left + child->props().leftMargin;
                
                left = child->localTransform().position.x +
                       child->localWidth() + child->props().rightMargin +
                       m_stackProps.spacing;
                
                // vertical positioning
                switch (m_stackProps.stackAlignment) {
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
                            m_height - m_props.bottomPadding -
                            child->props().bottomMargin - child->localHeight();
                        break;
                    default:
                        break;
                }
            }
            
            if (!m_children.empty()) {
                // there should not be spacing between the last element
                // of the stack and the right edge,
                // besides the stack's padding.
                left -= m_stackProps.spacing;
            }
            
            // set the stack's rect width
            m_width = left + m_props.rightPadding;
        }
            break;
        default:
            break;
    }
}

