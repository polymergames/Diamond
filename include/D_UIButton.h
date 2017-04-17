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
        UIButton(UIFlags flags,
                 const DTransform2 &transform = DTransform2(),
                 tD_pos width = 0,
                 tD_pos height = 0,
                 const UITouchCallback &onTouchDown = nullptr,
                 const UITouchCallback &onTouchDrag = nullptr,
                 const UITouchCallback &onTouchUp = nullptr);
        
        UIButton(const UITouchCallback &onTouchDown = nullptr,
                 const UITouchCallback &onTouchDrag = nullptr,
                 const UITouchCallback &onTouchUp = nullptr);
        
        virtual ~UIButton() {}
        
        
        void setOnTouchDown(const UITouchCallback &callback)
        { onTouchDown = callback; }
        
        void setOnTouchDrag(const UITouchCallback &callback)
        { onTouchDrag = callback; }
        
        void setOnTouchUp(const UITouchCallback &callback)
        { onTouchUp = callback; }
        
        
        void handleTouchDown(const Vector2<tD_pos> &touchPos) override;
        void handleTouchDrag(const Vector2<tD_pos> &touchPos) override;
        void handleTouchUp(const Vector2<tD_pos> &touchPos) override;
        
    private:
        UITouchCallback onTouchDown;
        UITouchCallback onTouchDrag;
        UITouchCallback onTouchUp;
    };
}

#endif // D_UI_BUTTON_H
