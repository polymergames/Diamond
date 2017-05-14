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

#include "D_UIText.h"

Diamond::UIText::UIText(Renderer2D *renderer,
                        const Diamond::Font *font,
                        const std::string &text,
                        const Diamond::RGBA &color,
                        const UIViewProps &props,
                        const DTransform2 &transform,
                        tD_pos width,
                        tD_pos height,
                        RenderLayer layer) :
UIView(props, transform, width, height),
font(font),
text(text),
color(color),
renderer(renderer),
layer(layer) {
    setText(text);
    renderComponent = renderer->makeRenderComponent(worldTransform(), texture, layer);
}

Diamond::UIText::~UIText() {
    renderComponent.free();
    texture.free();
}


void Diamond::UIText::updateLayout() {
    if (texture) {
        // resize this view to fit its text
        m_width = texture->getWidth() * worldTransform().scale.x;
        m_height = texture->getHeight() * worldTransform().scale.y;
        
        // layout children
        UIView::updateLayout();
    }
}


void Diamond::UIText::setText(const std::string &newText) {
    text = newText;
    
    texture.free();
    texture = renderer->loadTextTexture(newText, font, color);
    
    if (renderComponent) { // if text is currently visible
        // A new render component is created so that it is properly sized
        // for the new text texture.
        // TODO: modify the existing render component without
        // breaking the size.
        renderComponent.free();
        renderComponent = renderer->makeRenderComponent(worldTransform(), texture, layer);
    }
    // else, don't make render component because text is currently invisible
}


void Diamond::UIText::setFont(const Diamond::Font *newFont) {
    font = newFont;
    // refresh the text so it has the new font
    setText(text);
}


void Diamond::UIText::setColor(const Diamond::RGBA &newColor) {
    color = newColor;
    
    if (texture)
        texture->setColor(newColor);
}


void Diamond::UIText::setVisible(bool newVisible) {
    if (newVisible && !renderComponent) {
        // make this image visible again
        renderComponent = renderer->makeRenderComponent(worldTransform(), texture, layer);
    }
    else if (!newVisible && renderComponent) {
        // make this image invisible
        renderComponent.free();
    }
    
    UIView::setVisible(newVisible);
}

