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

#ifndef D_UI_VIEW_H
#define D_UI_VIEW_H

#include <vector>
#include "D_Node2D.h"
#include "D_typedefs.h"

namespace Diamond {
    class UIView;
    using UIChildList = std::vector<UIView*>;
    
    // Note: because UIViews store pointers/references to each other
    // to maintain the UI tree, the memory locations of the UIView
    // objects should never change
    // (ie, be careful storing your views in a vector like data structure).
    class UIView {
    public:
        UIView(DTransform2 transform = DTransform2(),
               tD_pos width = 0,
               tD_pos height = 0);
        virtual ~UIView() {}
        
        // Updates the world transforms of all UI views in the tree
        // rooted at this view, based on their local transforms
        // and parent transforms.
        void updateTransforms(const DTransform2 &parent_transform = DTransform2(),
                              const Matrix<tD_real, 2, 2> &parent_trans_mat = IDENTITY_MAT2);
        
        /**
         Returns the given child after adding it to children.
         Note: this will overwrite the child's previous local transform,
         replacing it with the child's world transform converted to
         its local transform in this view's coordinate space.
        */
        UIView &addChild(UIView &child);
        UIView *addChild(UIView *child);
        
        /**
         Searches children for the given child and removes it from children.
         Returns true if child was found and removed, otherwise false.
        */
        bool removeChild(UIView &child);
        bool removeChild(UIView *child);
        
        
        DTransform2 &worldTransform() { return m_worldTransform; }
        const DTransform2 &worldTransform() const { return m_worldTransform; }
        
        DTransform2 &localTransform() { return m_node.localTransform(); }
        const DTransform2 &localTransform() const { return m_node.localTransform(); }
        
        tD_pos &localWidth() { return m_width; }
        tD_pos localWidth() const { return m_width; }
        
        tD_pos &localHeight() { return m_height; }
        tD_pos localHeight() const { return m_height; }
        
        tD_pos worldWidth() const { return m_width * m_worldTransform.scale.x; }
        tD_pos worldHeight() const { return m_height * m_worldTransform.scale.y; }
        
        const UIChildList &children() const { return m_children; }
        
    private:
        // world space properties
        DTransform2 m_worldTransform;
        
        // local space properties
        Node2D m_node;
        tD_pos m_width;
        tD_pos m_height;
        
        UIChildList m_children;
    };
}

#endif // D_UI_VIEW_H
