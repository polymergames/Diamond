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

Diamond::UIButton::UIButton(const UIViewProps &props,
                            const DTransform2 &transform,
                            tD_pos width,
                            tD_pos height,
                            const UITouchCallback &onPress,
                            const UITouchCallback &onHold,
                            const UITouchCallback &onRelease) :
Diamond::UIView(props, transform, width, height),
onPress(onPress),
onHold(onHold),
onRelease(onRelease)
//touchedLastFrame(false),
//holdingDown(false)
{}

Diamond::UIButton::UIButton(const UITouchCallback &onPress,
                            const UITouchCallback &onHold,
                            const UITouchCallback &onRelease) :
UIButton(UIViewProps(), DTransform2(), 0, 0, onPress, onHold, onRelease) {}


//void Diamond::UIButton::updateState() {
//    // The button is considered held down for as many frames as touch
//    // input is received- if the button was not touched in the last frame,
//    // then it is no longer being held down.
//    holdingDown = touchedLastFrame;
//    touchedLastFrame = false;
//}


bool Diamond::UIButton::handleTouchDown(const Vector2<tD_pos> &touchPos) {
//    touchedLastFrame = true;
    
    if (onPress)
        onPress(touchPos);
    
    return UIView::handleTouchDown(touchPos);
}

bool Diamond::UIButton::handleTouchDrag(const Vector2<tD_pos> &touchPos) {
    // the button is only considered to be held down
    // on a touchDrag event if it was already being held down.
    // this ensures that the button is only held down if the first touch
    // event on it is a touchDown event.
//    if (holdingDown) {
//        touchedLastFrame = true;
    
        if (onHold)
            onHold(touchPos);
//    }
    
    return UIView::handleTouchDrag(touchPos);
}

bool Diamond::UIButton::handleTouchUp(const Vector2<tD_pos> &touchPos) {
    // a touchUp event only releases the button
    // if it was already being held down.
//    if (holdingDown && onRelease) {
    if (onRelease)
        onRelease(touchPos);
    
    return UIView::handleTouchUp(touchPos);
}

