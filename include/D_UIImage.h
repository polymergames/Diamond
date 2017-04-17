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

#ifndef D_UI_IMAGE_H
#define D_UI_IMAGE_H

#include "D_UIView.h"
#include "D_Renderer2D.h"

namespace Diamond {
    class UIImage : public UIView {
    public:
        UIImage(UIFlags flags,
                const DTransform2 &transform,
                Renderer2D *renderer,
                const Texture *texture,
                RenderLayer layer = 1);
        
        UIImage(Renderer2D *renderer,
                const Texture *texture,
                RenderLayer layer = 1);
        
        virtual ~UIImage();
        
        void updateState() override;
        
        RenderComponent2D *getRenderComponent() { return renderComponent.get(); }
        const RenderComponent2D *getRenderComponent() const { return renderComponent.get(); }
        
    private:
        DumbPtr<RenderComponent2D> renderComponent;
    };
}

#endif // D_UI_IMAGE_H
