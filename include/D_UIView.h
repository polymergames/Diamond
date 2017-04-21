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
    
    // The layout properties of a UIView, used when calculating
    // positions and sizes of rects in a UI hierarchy.
    struct UIViewProps {
        enum UIFlags {
            NONE = 0,
            FIT_CONTENTS = 1 << 0
        };
        
        enum UIAlignment { UNALIGNED, LEFT, CENTER, RIGHT, TOP, BOTTOM };
        
        
        UIFlags flags = NONE;
        
        UIAlignment horizontalAlignment = UNALIGNED;
        UIAlignment verticalAlignment = UNALIGNED;
        
        tD_pos leftMargin = 0;
        tD_pos rightMargin = 0;
        tD_pos topMargin = 0;
        tD_pos bottomMargin = 0;
        
        tD_pos leftPadding = 0;
        tD_pos rightPadding = 0;
        tD_pos topPadding = 0;
        tD_pos bottomPadding = 0;
    };
    
    
    class UIView;
    
    using UIChildList = std::vector<UIView*>;
    
    
    // NOTE: because UIViews store pointers/references to each other
    // to maintain the UI tree, the memory locations of the UIView
    // objects should never change
    // (ie, be careful storing your views in a vector-like data structure).
    class UIView {
    public:
        UIView(const UIViewProps &props = UIViewProps(),
               const DTransform2 &transform = DTransform2(),
               tD_pos width = 0,
               tD_pos height = 0);
        virtual ~UIView() {}
        
        /**
         Get the settings of this UIView.
        */
        UIViewProps &props() { return m_props; }
        const UIViewProps &props() const { return m_props; }
        
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
        
        
        // Calculates and updates the local transforms and rects of this view
        // and its children based on their UIViewProps.
        // This does not update world transforms, which should be performed
        // by calling updateTransforms after calling updateLayout.
        // updateLayout can be overriden by UIView subclasses.
        virtual void updateLayout();
        
        // Updates the world transforms of all UI views in the tree
        // rooted at this view, based on their local transforms
        // and parent transforms.
        // This should be called on the UI hierarchy's root view,
        // after calling updateLayout.
        void updateTransforms(const DTransform2 &parentTransform = DTransform2(),
                              const Matrix<tD_real, 2, 2> &parentTransMat = IDENTITY_MAT2);
        
        // The handle input functions below return true if the touch input
        // was handled by a child of this view.
        
        // Gets the input state and handles all input types
        // (ie, calls handleTouchDown, etc. as appropriate)
        // for this view and any child views that are affected
        // by the input (ie, by testing for each child view rect's intersection
        // with input events).
        // In order for this to be accurate, it must be called
        // AFTER updateTransforms.
        // If the UI is static,
        // it's sufficient to call updateLayout and updateTransforms only once,
        // and then call handleInput on every frame.
        bool handleInput();
        
        // The handle functions below call their corresponding function
        // for all children in this view tree.
        // When overriding input handlers in a subclass,
        // the overriding function should call its superclass version
        // after it's done handling its own behavior
        // in order to update its children.
        virtual bool handleTouchDown(const Vector2<tD_pos> &touchPos);
        virtual bool handleTouchDrag(const Vector2<tD_pos> &touchPos);
        virtual bool handleTouchUp(const Vector2<tD_pos> &touchPos);
        
        
        // Returns whether the given vector position
        // is inside this view.
        bool inside(const Vector2<tD_pos> &pos) const;
        
        
        // The UIView's world transform corresponds to the point
        // at coordinates (0, 0) in the view's local space.
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
        
    protected:
        // settings
        UIViewProps m_props;
        
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
