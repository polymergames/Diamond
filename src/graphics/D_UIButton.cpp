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

#include "D_UIButton.h"

Diamond::UIButton::UIButton(UIFlags flags,
                            const DTransform2 &transform,
                            tD_pos width,
                            tD_pos height,
                            const UITouchCallback &onTouchDown,
                            const UITouchCallback &onTouchDrag,
                            const UITouchCallback &onTouchUp) :
Diamond::UIView(flags, transform, width, height),
onTouchDown(onTouchDown),
onTouchDrag(onTouchDrag),
onTouchUp(onTouchUp) {}

Diamond::UIButton::UIButton(const UITouchCallback &onTouchDown,
                            const UITouchCallback &onTouchDrag,
                            const UITouchCallback &onTouchUp) :
UIButton(NONE, DTransform2(), 0, 0, onTouchDown, onTouchDrag, onTouchUp) {}


void Diamond::UIButton::handleTouchDown(const Vector2<tD_pos> &touchPos) {
    if (onTouchDown)
        onTouchDown(touchPos);
    
    UIView::handleTouchDown(touchPos);
}

void Diamond::UIButton::handleTouchDrag(const Vector2<tD_pos> &touchPos) {
    if (onTouchDrag)
        onTouchDrag(touchPos);
    
    UIView::handleTouchDrag(touchPos);
}

void Diamond::UIButton::handleTouchUp(const Vector2<tD_pos> &touchPos) {
    if (onTouchUp)
        onTouchUp(touchPos);
    
    UIView::handleTouchUp(touchPos);
}

