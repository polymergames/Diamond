/*
 Copyright (c) 2015 Polymer Games
*/

#include "Game.h"
#include "Launcher.h"
#include "Input.h"
#include "SDLInput.h"
using namespace Diamond;

class Demo : public Game {
	public:
	const float movespeed = 0.5f;

	std::unique_ptr<GameObject2D> spike;
	std::shared_ptr<Texture> spike_sprite;
	std::shared_ptr<Texture> cloud_sprite;

	RGBA spike_color = RGBA{255, 255, 255, 255};

	void init() {
		spike_sprite = std::shared_ptr<Texture>(Graphics2D::load_texture("spike.png"));
		cloud_sprite = std::shared_ptr<Texture>(Graphics2D::load_texture("cloud.png"));

		spike = std::unique_ptr<GameObject2D>(new GameObject2D(cloud_sprite));
		spike->transform->position.x = 500;
		spike->transform->position.y = 400;
		spike->transform->scale = 0.1f;
		//std::cout << spike->transform->position.x << " and " << spike->transform->position.y << " and " << spike->transform->scale << std::endl;
	}

	void update(float delta) {
		if (Input::keydown[Input::K_R]) {
			spike_color = {255, 0, 0, 255};
			spike->get_sprite()->set_color(spike_color);
		}

		if (Input::keydown[Input::K_T]) {
			spike_color = {255, 255, 255, 255};
			spike->get_sprite()->set_color(spike_color);
		}

		if (Input::keyup[Input::K_Y]) {
			RGBA sc = spike->get_sprite()->get_color();
			sc.a -= 32;
			spike->get_sprite()->set_color(sc);
		}

		if (Input::keyup[Input::K_S]) {
			spike->set_sprite(spike_sprite);
		}

		if (Input::keyup[Input::K_C]) {
			spike->set_sprite(cloud_sprite);
		}

		if (Input::keyup[Input::K_SPACE]) {
			spike->toggle_visibility();
		}

		if (Input::keydown[Input::K_LSHIFT]) {
			spike->transform->scale += 0.0001f;
		}

		if (Input::keydown[Input::K_LCTRL]) {
			spike->transform->scale -= 0.0001f;
		}

		if (Input::keydown[Input::K_W]) {
			std::cout << "W pressed!" << std::endl;
			Launcher::config.bg_color = {0, 0, 0, 0};
		}
		if (Input::keyup[Input::K_W]) {
			std::cout << "W released!" << std::endl;
			Launcher::config.bg_color = {0, 128, 255, 255};
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

	void quit() {};
};

int main(int argc, char *argv[]) {
	Demo demo;

    Launcher::config.bg_color = {0, 128, 255, 255};
    Launcher::launch(demo);

	return 0;
}
