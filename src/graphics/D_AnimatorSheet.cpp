/*
    Copyright 2015 Ahnaf Siddiqui

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

#include "D_AnimatorSheet.h"
#include "D_Log.h"

namespace {
const std::string EMPTY_ANIMATION_ERROR =
    "AnimatorSheet ERROR: Tried to set an empty animation!";
const std::string NULL_RENDERCOMP_ERROR =
    "AnimatorSheet ERROR: The given render component is null!";
}

Diamond::AnimatorSheet::AnimatorSheet(RenderComponent2D *rcomp,
                                      const AnimationSheet *anim)
    : m_render_comp(rcomp), m_anim(anim), m_cur_frame(0), m_elapsed(0) {
  if (!anim || !(anim->sprite_sheet) || anim->num_frames == 0) {
    // TODO: throw exception?
    Log::log(EMPTY_ANIMATION_ERROR);
  } else if (!rcomp) {
    Log::log(NULL_RENDERCOMP_ERROR);
  } else {
    rcomp->setSprite(anim->sprite_sheet);
    initClip();
  }
}

void Diamond::AnimatorSheet::setAnimation(const AnimationSheet *anim) {
  if (!anim || !(anim->sprite_sheet) || anim->num_frames == 0) {
    // TODO: throw exception?
    Log::log(EMPTY_ANIMATION_ERROR);
    return;
  }

  m_anim = anim;
  m_render_comp->setSprite(anim->sprite_sheet);
  m_cur_frame = 0;
  m_elapsed = 0;

  initClip();
}

void Diamond::AnimatorSheet::setRenderComponent(RenderComponent2D *rcomp) {
  if (!rcomp) {
    Log::log(NULL_RENDERCOMP_ERROR);
    return;
  }

  m_render_comp = rcomp;
  m_render_comp->setSprite(m_anim->sprite_sheet);

  initClip();
}

void Diamond::AnimatorSheet::update(tD_delta delta) {
  // continue animation if it is not yet done
  if (!isDone()) {
    m_elapsed += delta;

    // if the current frame is done, switch to the next frame
    if (m_elapsed > m_anim->frame_length) {
      m_cur_frame =
          (m_cur_frame + m_elapsed / m_anim->frame_length) % m_anim->num_frames;

      m_render_comp->setClipPos(
          (m_cur_frame % m_anim->columns) * m_frame_width,
          (m_cur_frame / m_anim->columns) * m_frame_height);
      m_elapsed %= m_anim->frame_length;
    }
  }
}

void Diamond::AnimatorSheet::initClip() {
  m_frame_width = m_anim->sprite_sheet->getWidth() / m_anim->columns;
  m_frame_height = m_anim->sprite_sheet->getHeight() / m_anim->rows;

  m_render_comp->setClip(0, 0, m_frame_width, m_frame_height);
}
