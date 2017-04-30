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

#ifndef D_UI_TEXT_H
#define D_UI_TEXT_H

#include "D_UIView.h"
#include "D_Renderer2D.h"

namespace Diamond {
    class UIText : public UIView {
    public:
        UIText(Renderer2D *renderer,
               const Diamond::Font *font,
               const std::string &text = "",
               const Diamond::RGBA &color = {255, 255, 255, 100},
               const UIViewProps &props = UIViewProps(),
               const DTransform2 &transform = DTransform2(),
               tD_pos width = 0,
               tD_pos height = 0,
               RenderLayer layer = 1);
        
        virtual ~UIText();
        
        
        std::string getText() const { return text; }
        void setText(const std::string &newText);
        
        const Diamond::Font *getFont() const { return font; }
        void setFont(const Diamond::Font *newFont);
        
        RGBA getColor() const { return color; }
        void setColor(const RGBA &newColor);
        
        
        // set whether this image should be rendered.
        void setVisible(bool visible) override;
        
        RenderComponent2D *getRenderComponent() { return renderComponent.get(); }
        const RenderComponent2D *getRenderComponent() const { return renderComponent.get(); }
        
    private:
        const Diamond::Font *font;
        std::string text;
        Diamond::RGBA color;
        
        Renderer2D *renderer;
        DumbPtr<Texture> texture;
        RenderLayer layer;
        DumbPtr<RenderComponent2D> renderComponent;
    };
}

#endif // D_UI_TEXT_H
