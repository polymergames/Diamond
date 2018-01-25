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

#include "D_UIImage.h"

Diamond::UIImage::UIImage(const UIViewProps& props,
                          const DTransform2& transform, Renderer2D* renderer,
                          const Texture* texture, RenderLayer layer)
    : UIView(props, transform),
      texture(texture),
      layer(layer),
      renderer(renderer) {
  renderComponent =
      renderer->makeRenderComponent(worldTransform(), texture, layer);
}

Diamond::UIImage::UIImage(Renderer2D* renderer, const Texture* texture,
                          RenderLayer layer)
    : UIImage(UIViewProps(), DTransform2(), renderer, texture, layer) {}

Diamond::UIImage::~UIImage() { renderComponent.free(); }

void Diamond::UIImage::updateLayout() {
  // resize this view to fit its image
  auto clipDims = renderComponent->getClipDim();
  m_width = clipDims.x * worldTransform().scale.x;
  m_height = clipDims.y * worldTransform().scale.y;

  // layout children
  UIView::updateLayout();
}

void Diamond::UIImage::setVisible(bool newVisible) {
  if (newVisible) {
    renderComponent->setAlpha(255);
  } else {
    renderComponent->setAlpha(0);
  }

  UIView::setVisible(newVisible);
}
