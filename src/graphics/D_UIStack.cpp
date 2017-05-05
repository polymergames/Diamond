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
            tD_pos top = m_props.topPadding;
            tD_pos maxWidth = m_props.leftPadding + m_props.rightPadding;
            
            for (auto child : m_children) {
                child->localTransform().position.y =
                    top + child->props().topMargin;
                
                child->localTransform().position.x =
                    m_props.leftPadding + child->props().leftMargin;
                
                top = child->localTransform().position.y +
                      child->localHeight() + child->props().bottomMargin +
                      m_stackProps.spacing;
                
                auto childWidth =
                    child->localTransform().position.x +
                    child->localWidth() + child->props().rightMargin +
                    m_props.rightPadding;
                if (childWidth > maxWidth)
                    maxWidth = childWidth;
            }
            
            if (!m_children.empty()) {
                // there should not be spacing between the last element
                // of the stack and the bottom,
                // besides the stack's padding.
                top -= m_stackProps.spacing;
            }
            
            m_height = top + m_props.bottomPadding;
            m_width = maxWidth;
        }
            break;
        case UIStackProps::HORIZONTAL:
        {
            // TODO
            tD_pos left = m_props.leftPadding;
            tD_pos maxHeight = m_props.topPadding + m_props.bottomPadding;
            
            for (auto child : m_children) {
                //
            }
        }
            break;
        default:
            break;
    }
}

