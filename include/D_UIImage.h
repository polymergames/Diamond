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

#include "D_Renderer2D.h"
#include "D_UIView.h"

namespace Diamond {
class UIImage : public UIView {
 public:
  UIImage(const UIViewProps& props, const DTransform2& transform,
          Renderer2D* renderer, const Texture* texture, RenderLayer layer = 1);

  UIImage(Renderer2D* renderer, const Texture* texture, RenderLayer layer = 1);

  virtual ~UIImage();

  void updateLayout() override;

  // set whether this image should be rendered.
  void setVisible(bool visible) override;

  RenderComponent2D* getRenderComponent() { return renderComponent.get(); }
  const RenderComponent2D* getRenderComponent() const {
    return renderComponent.get();
  }

 private:
  const Texture* texture;
  RenderLayer layer;
  DumbPtr<RenderComponent2D> renderComponent;
  Renderer2D* renderer;
};
}  // namespace Diamond

#endif  // D_UI_IMAGE_H
