/*
    Copyright 2016 Ahnaf Siddiqui

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

#ifndef D_SDL_RENDER_COMPONENT_2D_H
#define D_SDL_RENDER_COMPONENT_2D_H

#include <memory>

#include "D_SDLRenderer2D.h"
#include "duSwapVector.h"

namespace Diamond {
class SDLRenderComponent2D : public RenderComponent2D {
public:
  SDLRenderComponent2D(SDLRenderer2D &renderer, SDLrenderobj_id renderObj,
                       const Texture *texture, RenderLayer layer)
      : m_renderer(renderer), m_renderObj(renderObj), m_sprite(texture),
        m_layer(layer) {}

  ~SDLRenderComponent2D() { m_renderer.destroyRenderObj(m_layer, m_renderObj); }

  const Texture *getSprite() const override { return m_sprite; }

  void setSprite(const Texture *sprite) override {
    auto texture = dynamic_cast<const SDLTexture *>(sprite);
    if (texture) {
      m_renderer.renderObj(m_layer, m_renderObj).setTexture(texture->texture);
      m_sprite = sprite;
    }
  }

  RenderLayer getLayer() const override { return m_layer; }

  void setLayer(RenderLayer newLayer) override {
    m_renderObj = m_renderer.changeLayer(m_layer, m_renderObj, newLayer);
    m_layer = newLayer;
  }

  uint8_t getAlpha() const override {
    return m_renderer.renderObj(m_layer, m_renderObj).alpha();
  }

  void setAlpha(uint8_t alpha) override {
    m_renderer.renderObj(m_layer, m_renderObj).alpha() = alpha;
  }

  Vector2<tD_pos> getClipPos() const override {
    SDL_Rect &clip = m_renderer.renderObj(m_layer, m_renderObj).clip();
    return Vector2<tD_pos>(clip.x, clip.y);
  }

  Vector2<int> getClipDim() const override {
    SDL_Rect &clip = m_renderer.renderObj(m_layer, m_renderObj).clip();
    return Vector2<int>(clip.w, clip.h);
  }

  void setClip(tD_pos x, tD_pos y, int w, int h) override {
    SDL_Rect &clip = m_renderer.renderObj(m_layer, m_renderObj).clip();
    clip.x = x;
    clip.y = y;
    clip.w = w;
    clip.h = h;
  }

  void setClipPos(tD_pos x, tD_pos y) override {
    SDL_Rect &clip = m_renderer.renderObj(m_layer, m_renderObj).clip();
    clip.x = x;
    clip.y = y;
  }

  void setClipDim(int w, int h) override {
    SDL_Rect &clip = m_renderer.renderObj(m_layer, m_renderObj).clip();
    clip.w = w;
    clip.h = h;
  }

  Vector2<tD_pos> getPivot() const override {
    SDL_Point &pivot = m_renderer.renderObj(m_layer, m_renderObj).pivot();
    return Vector2<tD_pos>(pivot.x, pivot.y);
  }

  void setPivot(const Vector2<tD_pos> &newpivot) override {
    m_renderer.renderObj(m_layer, m_renderObj).pivot() = {(int)newpivot.x,
                                                          (int)newpivot.y};
  }

  void flipX() override { m_renderer.renderObj(m_layer, m_renderObj).flipX(); }
  void flipY() override { m_renderer.renderObj(m_layer, m_renderObj).flipY(); }

  bool isFlippedX() const override {
    return m_renderer.renderObj(m_layer, m_renderObj).isFlippedX();
  }
  bool isFlippedY() const override {
    return m_renderer.renderObj(m_layer, m_renderObj).isFlippedY();
  }

private:
  SDLRenderer2D &m_renderer;
  SDLrenderobj_id m_renderObj;
  const Texture *m_sprite;
  RenderLayer m_layer;
};
} // namespace Diamond

#endif // D_SDL_RENDER_COMPONENT_2D_H
