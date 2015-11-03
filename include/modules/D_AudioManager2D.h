/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_AUDIO_MANAGER_2D_H
#define D_AUDIO_MANAGER_2D_H

#include "D_DiskJockey2D.h"

namespace Diamond {
	namespace AudioManager2D {
		// TODO: getting and setting master volume

		/**
		 Loads an audio file as a sound effect.
		 Returns nullptr if sound failed to load.
		*/
		Sound2D *load_sound(std::string path);

		/**
		 Loads an audio file as a music track.
		 Returns nullptr if music failed to load.
		*/
		Music *load_music(std::string path);

		/**
		Returns the maximum volume value of the currently active sound system.
		*/
		int get_max_volume();

		/**
		 Pause all music that is currently playing.
		*/
		void pause_music();

		/**
		 Resume active music if paused.
		*/
		void resume_music();

		/**
		 Stops all music that is currently playing.
		*/
		void stop_music();

		/**
		 Returns whether any music is actively playing.
		*/
		bool is_music_playing();

		/**
		 Get the current volume of any actively playing music.
		*/
		int get_music_volume();

		/**
		 Set the volume for any music that is playing/will be played.
		*/
		void set_music_volume(int volume);

		// Don't call unless you know what you're doing!
		void set_dj(DiskJockey2D *dj);
		bool init_dj(); // returns whether initialization was successful
	};
}

#endif // D_AUDIO_MANAGER_2D_H
