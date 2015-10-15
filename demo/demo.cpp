/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "Input.h"
#include "SDLInput.h"
using namespace Diamond;

std::unique_ptr<GameObject2D> spike;

float d = 0.0f;
const int movespeed = 20;

class Init {
public:
    void operator() () {
        spike = std::unique_ptr<GameObject2D>(new GameObject2D(std::shared_ptr<Texture>(Graphics2D::load_texture("spike.png"))));
        spike->transform->position.x = 500;
        spike->transform->position.y = 400;
        spike->transform->scale = 0.1;
//        std::cout << spike->transform->position.x << " and " << spike->transform->position.y << " and " << spike->transform->scale << std::endl;
    }
};

class Update {
public:
    void operator() (float delta) {
        if (Input::keydown[Input::K_SPACE]) {
            spike->toggle_visibility();
        }
        
        if (Input::keydown[Input::K_W]) {
            std::cout << "W pressed!" << std::endl;
        }
        if (Input::keyup[Input::K_W]) {
            std::cout << "W released!" << std::endl;
        }
        if (Input::keydown[Input::K_UP]) {
            std::cout << "Up!" << std::endl;
            spike->transform->position.y -= movespeed;
        }
        if (Input::keydown[Input::K_DOWN]) {
            std::cout << "Down!" << std::endl;
            spike->transform->position.y += movespeed;
        }
        if (Input::keydown[Input::K_LEFT]) {
            std::cout << "Left!" << std::endl;
            spike->transform->position.x -= movespeed;
        }
        if (Input::keydown[Input::K_RIGHT]) {
            std::cout << "Right!" << std::endl;
            spike->transform->position.x += movespeed;
        }
    }
};

int main(int argc, char *argv[]) {
    Launcher::config.bg_color = {0, 128, 255, 255};
    Launcher::launch(Init(), Update());
	return 0;
}
