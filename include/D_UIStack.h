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

#ifndef D_UI_STACK_H
#define D_UI_STACK_H

#include "D_UIView.h"

namespace Diamond {
    
    // The layout properties of a UIStack.
    struct UIStackProps {
        // TODO: implement alignment
        // (ie, all stack elements are centered, aligned along left, right,
        // top, or bottom)
        
        enum UIStackOrientation { VERTICAL, HORIZONTAL };
        
        // Whether the stack is vertical or horizontal.
        UIStackOrientation orientation = VERTICAL;
        
        // the amount of space between adjacent UIViews in the stack.
        tD_pos spacing = 0;
    };
    
    
    class UIStack : public UIView {
    public:
        UIStack(const UIViewProps &viewProps = UIViewProps(),
                const UIStackProps &stackProps = UIStackProps(),
                const DTransform2 &transform = DTransform2(),
                tD_pos width = 0,
                tD_pos height = 0);
        
        virtual ~UIStack() {}
        
        UIStackProps &stackProps() { return m_stackProps; }
        const UIStackProps &stackProps() const { return m_stackProps; }
        
        void updateLayout() override;
        
    private:
        UIStackProps m_stackProps;
    };
}

#endif // D_UI_STACK_H
