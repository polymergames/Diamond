/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "Input.h"
#include "SDLInput.h"
using namespace Diamond;

std::unique_ptr<GameObject2D> spike;

class Init {
public:
    void operator() () {
        spike = std::unique_ptr<GameObject2D>(new GameObject2D(std::shared_ptr<Texture>(Graphics2D::load_texture("spike.png"))));
    }
};

class Update {
public:
    void operator() (float delta) {
        if (Input::keydown[Input::K_W]) {
            std::cout << "W pressed!" << std::endl;
        }
        if (Input::keyup[Input::K_W]) {
            std::cout << "W released!" << std::endl;
        }
        if (Input::keydown[Input::K_UP]) {
            std::cout << "Up!" << std::endl;
        }
        if (Input::keydown[Input::K_DOWN]) {
            std::cout << "Down!" << std::endl;
        }
        if (Input::keydown[Input::K_LEFT]) {
            std::cout << "Left!" << std::endl;
        }
        if (Input::keydown[Input::K_RIGHT]) {
            std::cout << "Right!" << std::endl;
        }
    }
};

int main(int argc, char *argv[]) {
	Config config = Config();
    config.bg_color = {0, 128, 255, 255};
    Launcher::launch(config, Init(), Update());
	return 0;
}
