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

#ifndef D_UI_BUTTON_H
#define D_UI_BUTTON_H

#include <functional>
#include "D_UIView.h"

namespace Diamond {
    using UITouchCallback = std::function<void(const Vector2<tD_pos>&)>;
    
    class UIButton : public UIView {
    public:
        UIButton(const UIViewProps &props,
                 const DTransform2 &transform = DTransform2(),
                 tD_pos width = 0,
                 tD_pos height = 0,
                 const UITouchCallback &onPress = nullptr,
                 const UITouchCallback &onHold = nullptr,
                 const UITouchCallback &onRelease = nullptr);
        
        UIButton(const UITouchCallback &onPress = nullptr,
                 const UITouchCallback &onHold = nullptr,
                 const UITouchCallback &onRelease = nullptr);
        
        virtual ~UIButton() {}
        
        
        void setOnPress(const UITouchCallback &callback)
        { onPress = callback; }
        
        void setOnHold(const UITouchCallback &callback)
        { onHold = callback; }
        
        void setOnRelease(const UITouchCallback &callback)
        { onRelease = callback; }
        
//        void updateState() override;
        
        bool handleTouchDown(const Vector2<tD_pos> &touchPos) override;
        bool handleTouchDrag(const Vector2<tD_pos> &touchPos) override;
        bool handleTouchUp(const Vector2<tD_pos> &touchPos) override;
        
    private:
        UITouchCallback onPress;
        UITouchCallback onHold;
        UITouchCallback onRelease;
        
//        bool touchedLastFrame;
//        bool holdingDown;
    };
}

#endif // D_UI_BUTTON_H
