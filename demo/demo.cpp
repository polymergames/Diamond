/*
 Copyright (c) 2015 Polymer Games
*/

#include <memory>

#include "D_AudioManager2D.h"
#include "D_Game.h"
#include "D_GameObject2D.h"
#include "D_Graphics2D.h"
#include "D_Input.h"
#include "D_Launcher.h"
#include "D_SDLInput.h"
using namespace Diamond;

class Demo : public Game {
	public:
	const float movespeed = 10.0f;
	const float spinspeed = 10.0f;
	const float growspeed = 0.01f;

	std::unique_ptr<GameObject2D> spike;

	std::shared_ptr<Texture> spike_sprite;
	std::shared_ptr<Texture> cloud_sprite;

	RGBA spike_color = RGBA{255, 255, 255, 255};

	std::unique_ptr<Sound2D> haha;
	
	void init() {
		spike_sprite = std::shared_ptr<Texture>(Graphics2D::load_texture("spike.png"));
		cloud_sprite = std::shared_ptr<Texture>(Graphics2D::load_texture("cloud.png"));

		spike = std::unique_ptr<GameObject2D>(new GameObject2D(cloud_sprite));
		spike->set_transform(500, 400, 0, 0.1f);

		haha = std::unique_ptr<Sound2D>(AudioManager2D::load_sound("haha.wav"));
	}

	void update(float delta) {
		// Coloring
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

		// Sprite switching
		if (Input::keyup[Input::K_1]) {
			spike->set_sprite(spike_sprite);
		}
		if (Input::keyup[Input::K_2]) {
			spike->set_sprite(cloud_sprite);
		}

		// Visibility
		if (Input::keyup[Input::K_SPACE]) {
			spike->toggle_visibility();
		}

		// Stretching
		if (Input::keydown[Input::K_LSHIFT]) {
			spike->set_scale(spike->get_transform().scale + growspeed * delta);
		}
		if (Input::keydown[Input::K_LCTRL]) {
			spike->set_scale(spike->get_transform().scale - growspeed * delta);
		}

		// Flipping
		if (Input::keyup[Input::K_DOWN]) {
			spike->flip_x();
		}
		if (Input::keyup[Input::K_UP]) {
			spike->flip_y();
		}

		// Movement
		if (Input::keydown[Input::K_W]) {
			Transform2 trans = spike->get_transform();
			trans.position.y -= movespeed * delta;
			spike->set_transform(trans);
		}
		if (Input::keydown[Input::K_S]) {
			Transform2 trans = spike->get_transform();
			trans.position.y += movespeed * delta;
			spike->set_transform(trans);
		}
		if (Input::keydown[Input::K_A]) {
			Transform2 trans = spike->get_transform();
			trans.position.x -= movespeed * delta;
			spike->set_transform(trans);
		}
		if (Input::keydown[Input::K_D]) {
			Transform2 trans = spike->get_transform();
			trans.position.x += movespeed * delta;
			spike->set_transform(trans);
		}

		// Rotation
		if (Input::keydown[Input::K_LEFT]) {
			spike->set_rotation(spike->get_transform().rotation - spinspeed * delta);
		}
		if (Input::keydown[Input::K_RIGHT]) {
			spike->set_rotation(spike->get_transform().rotation + spinspeed * delta);
		}

		// Sound
		if (Input::keyup[Input::K_F]) {
			haha->play();
		}

		std::cout << "x flip: " << spike->is_flipped_x() << "; y flip: " << spike->is_flipped_y() << std::endl;
	}

	void quit() {};
};

int main(int argc, char *argv[]) {
	Demo demo;

	Launcher::config.vsync = true;
	Launcher::config.bg_color = {0, 128, 255, 255};
	Launcher::launch(demo);

	return 0;
}
