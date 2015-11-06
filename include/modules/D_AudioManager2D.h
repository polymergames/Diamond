/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_AUDIO_MANAGER_2D_H
#define D_AUDIO_MANAGER_2D_H

#include <iostream>

#include "D_Music.h"
#include "D_Sound2D.h"

namespace Diamond {
	class DiskJockey2D;

	namespace AudioManager2D {
		// TODO: getting and setting master volume

		/**
		 Loads an audio file as a sound effect.
		 Returns nullptr if sound failed to load.
		*/
		Sound2D *loadSound(std::string path);

		/**
		 Loads an audio file as a music track.
		 Returns nullptr if music failed to load.
		*/
		Music *loadMusic(std::string path);

		/**
		Returns the maximum volume value of the currently active sound system.
		*/
		int getMaxVolume();

		/**
		 Pause all music that is currently playing.
		*/
		void pauseMusic();

		/**
		 Resume active music if paused.
		*/
		void resumeMusic();

		/**
		 Stops all music that is currently playing.
		*/
		void stopMusic();

		/**
		 Returns whether any music is actively playing.
		*/
		bool isMusicPlaying();

		/**
		 Get the current volume of any actively playing music.
		*/
		int getMusicVolume();

		/**
		 Set the volume for any music that is playing/will be played.
		*/
		void setMusicVolume(int volume);

		/**
		 Called by Diamond launcher to initialize sound.
		*/
		bool initDj(DiskJockey2D *dj); // returns whether initialization was successful
	};
}

#endif // D_AUDIO_MANAGER_2D_H
