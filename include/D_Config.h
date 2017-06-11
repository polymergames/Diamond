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

#ifndef D_CONFIG_H
#define D_CONFIG_H

#include <stdint.h>
#include <string>

namespace Diamond {
enum audio_channels_t { D_MONO, D_STEREO };

struct RGB {
  uint8_t r, g, b;
};

struct RGBA {
  uint8_t r, g, b, a;
};

struct Config {
  std::string game_name = "A Game Without a Name";

  // Graphics settings
  int16_t window_width = 1280;
  int16_t window_height = 720;
  bool vsync = false;
  bool fullscreen = false;
  RGBA bg_color = RGBA{0, 0, 0, 100};

  // Audio settings
  audio_channels_t audio_channels = D_STEREO;
  int32_t audio_out_freq = 44100;       // in hertz
  int16_t audio_out_sample_size = 2048; // in bytes

  // Subsystem constraints
  // if one of these is false, Diamond will run even if the corresponding
  // subsystem fails to initialize (ie, that subsystem is optional).
  bool require_audio = false;

  // Estimate of the max number of gameobjects active at any time.
  // This is used to allocate memory for transforms, render components,
  // etc.
  int max_gameobjects_estimate = 1000;

  // Allocates memory for max_gameobjects_estimate render components
  // in EACH render layer based on num_render_layers_estimate, if
  // optimize_render_layers is true.
  // WARNING: if num_render_layers_estimate is a high number
  // and max_gameobjects_estimate is also a high number,
  // this may allocate A LOT of memory!!!!
  // WARNING: this assumes that all render layers used are in order,
  // starting from 0. If that's not the case, you may have
  // a lot of wasted memory (A LOT!!!)
  bool optimize_render_layers = true;
  int num_render_layers_estimate = 1;
};
} // namespace Diamond

#endif // D_CONFIG_H
