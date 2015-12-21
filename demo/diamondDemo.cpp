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

#include <memory>

#include "Q_QuantumWorld2D.h"
using namespace Quantum2D;

#include "D_AudioManager2D.h"
#include "D_Game.h"
#include "D_Entity2D.h"
#include "D_Graphics2D.h"
#include "D_Input.h"
#include "D_Launcher.h"
#include "D_RenderComponent2D.h"
#include "D_Time.h"
using namespace Diamond;

class Demo : public Game {
	public:
	const float movespeed = 0.75f;
	const float spinspeed = 0.75f;
	const float growspeed = 0.00075f;

	Entity2D spike;

	std::shared_ptr<Texture> spike_sprite;
	std::shared_ptr<Texture> cloud_sprite;

	RGBA spike_color = RGBA{255, 255, 255, 255};

	std::unique_ptr<Sound2D> haha;
	
	
	void init() override {
		spike_sprite = std::shared_ptr<Texture>(Graphics2D::loadTexture("spike.png"));
		cloud_sprite = std::shared_ptr<Texture>(Graphics2D::loadTexture("cloud.png"));
		
		spike.addComponent(new RenderComponent2D(&spike, cloud_sprite, 0.1f));
		spike.setTransform(500, 400);
		if (!spike.getComponent<RenderComponent2D>()) {
			std::cout << "NULL!" << std::endl;
		}

		haha = std::unique_ptr<Sound2D>(AudioManager2D::loadSound("haha.wav"));
	}

	void update(uint32_t delta) override {
		// Coloring
		if (Input::keydown[Input::K_R]) {
			spike_color = {255, 0, 0, 255};
			spike.getComponent<RenderComponent2D>()->getSprite()->setColor(spike_color);
		}
		if (Input::keydown[Input::K_T]) {
			spike_color = {255, 255, 255, 255};
			spike.getComponent<RenderComponent2D>()->getSprite()->setColor(spike_color);
		}
		if (Input::keyup[Input::K_Y]) {
			RGBA sc = spike.getComponent<RenderComponent2D>()->getSprite()->getColor();
			sc.a -= 32;
			spike.getComponent<RenderComponent2D>()->getSprite()->setColor(sc);
		}

		// Sprite switching
		if (Input::keyup[Input::K_1]) {
			spike.getComponent<RenderComponent2D>()->setSprite(spike_sprite);
		}
		if (Input::keyup[Input::K_2]) {
			spike.getComponent<RenderComponent2D>()->setSprite(cloud_sprite);
		}

		// Visibility
		if (Input::keyup[Input::K_SPACE]) {
			spike.getComponent<RenderComponent2D>()->toggleVisibility();
		}

		// Stretching
		if (Input::keydown[Input::K_LSHIFT]) {
			spike.getComponent<RenderComponent2D>()->setScale(spike.getComponent<RenderComponent2D>()->getScale() + growspeed * delta);
		}
		if (Input::keydown[Input::K_LCTRL]) {
			spike.getComponent<RenderComponent2D>()->setScale(spike.getComponent<RenderComponent2D>()->getScale() - growspeed * delta);
		}

		// Flipping
		if (Input::keyup[Input::K_DOWN]) {
			spike.getComponent<RenderComponent2D>()->flipX();
		}
		if (Input::keyup[Input::K_UP]) {
			spike.getComponent<RenderComponent2D>()->flipY();
		}

		// Movement
		if (Input::keydown[Input::K_W]) {
			spike.getTransform().position.y -= movespeed * delta;
		}
		if (Input::keydown[Input::K_S]) {
			spike.getTransform().position.y += movespeed * delta;
		}
		if (Input::keydown[Input::K_A]) {
			spike.getTransform().position.x -= movespeed * delta;
		}
		if (Input::keydown[Input::K_D]) {
			spike.getTransform().position.x += movespeed * delta;
		}

		// Rotation
		if (Input::keydown[Input::K_LEFT]) {
			spike.setRotation(spike.getTransform().rotation - spinspeed * delta);
		}
		if (Input::keydown[Input::K_RIGHT]) {
			spike.setRotation(spike.getTransform().rotation + spinspeed * delta);
		}

		// Sound
		if (Input::keyup[Input::K_F]) {
			haha->play();
		}

		std::cout << "Delta = " << delta << "ms; FPS = " << Time::fps << std::endl;
	}

	void quit() override {};
};

int main(int argc, char *argv[]) {
	Demo demo;

	Launcher::config.vsync = true;
	Launcher::config.bg_color = {0, 128, 255, 255};
	Launcher::launch(demo);

	return 0;
}
