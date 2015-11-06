/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_CONFIG_H
#define D_CONFIG_H

#include <stdint.h>
#include <string>

namespace Diamond {
	enum audio_channels_t {D_MONO, D_STEREO};

	struct RGBA {
		unsigned char r, g, b, a;
	};
	
	struct Config {
		std::string game_name = "A Game Without a Name";

		// Graphics settings
		int16_t window_width = 1280;
		int16_t window_height = 720;
		bool vsync = false;
		RGBA bg_color = RGBA{0, 0, 0, 100};

		// Audio settings
		audio_channels_t audio_channels = D_STEREO;
		int32_t audio_out_freq = 44100; // in hertz
		int16_t audio_out_sample_size = 2048; // in bytes
	};
}

#endif // D_CONFIG_H
