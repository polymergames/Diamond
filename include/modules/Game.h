/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GAME_H
#define GAME_H

namespace Diamond {
	class Game {
		public:
		/**
		 Called at beginning of game, after Diamond backend systems have initialized.
		 Put game initialization code here.
		*/
		virtual void init() = 0;

		/**
		 Called once every frame, where delta is the time in seconds since the last frame.
		 Update game logic here.
		*/
		virtual void update(float delta) = 0;

		/**
		 Called when game ends.
		 Put cleanup code here.
		*/
		virtual void quit() = 0;
	};
}

#endif // GAME_H
