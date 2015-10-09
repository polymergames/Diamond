/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "Input.h"
#include "SDLInput.h"
using namespace Diamond;

float d = 0.0f;

class Init {
	public:
	void operator() () {
		std::cout << "Initializing..." << std::endl;
		std::cout << Diamond::SDLInput::keymap[SDLK_ASTERISK] << " and " << Diamond::Input::K_UNDEFINED << std::endl;
	}
};

class Update {
	public:
	void operator() (float delta) {
		//std::cout << "Delta is " << (d+=delta) << std::endl;
//        if(Input::keydown[Input::K_W]) {
//            std::cout << "W pressed!" << std::endl;
//        }
//        if(Input::keyup[Input::K_W]) {
//            std::cout << "W released!" << std::endl;
//        }
//        if(Input::keydown[Input::K_UP]) {
//            std::cout << "Up!" << std::endl;
//        }
//        if(Input::keydown[Input::K_DOWN]) {
//            std::cout << "Down!" << std::endl;
//        }
//        if(Input::keydown[Input::K_LEFT]) {
//            std::cout << "Left!" << std::endl;
//        }
//        if(Input::keydown[Input::K_RIGHT]) {
//            std::cout << "Right!" << std::endl;
//        }
	}
};

int main(int argc, char *argv[]) {
	Config config = Config();
	Launcher::launch(config, Init(), Update());
	return 0;
}
