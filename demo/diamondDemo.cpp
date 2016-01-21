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

#include <list>
#include <memory>

#include "Q_QuantumWorld2D.h"

#include "D_Animator2D.h"
#include "D_AnimatorSheet.h"
#include "D_AudioManager2D.h"
#include "D_Game.h"
#include "D_Entity2D.h"
#include "D_Graphics2D.h"
#include "D_Input.h"
#include "D_Launcher.h"
#include "D_RenderComponent2D.h"
#include "D_Time.h"
#include "D_World2D.h"
using namespace Diamond;

class Demo : public Game {
	public:
	const float movespeed = 0.75f;
	const float spinspeed = 0.75f;
	const float growspeed = 0.00075f;

	Entity2D spike, zapper, zapper2;
	std::list<std::unique_ptr<Entity2D>> objects;

	std::shared_ptr<Texture> spike_sprite;
	std::shared_ptr<Texture> cloud_sprite;

	Animation2D zapper_anim;
	AnimationSheet zapper2_anim;

	RGBA spike_color = RGBA{255, 255, 255, 255};

	std::unique_ptr<Sound2D> haha;
	
	Vector2<int> window;

	// body2d_id body;
	
	void init() override {
		window = Graphics2D::getResolution();

		Vector2<int> screen = Graphics2D::getScreenResolution();
		std::cout << "Resolution: " << window.x << " by " << window.y << std::endl;
		std::cout << "Screen resolution: " << screen.x << " by " << screen.y << std::endl;

		spike_sprite = Graphics2D::loadTexture("spike.png");
		cloud_sprite = Graphics2D::loadTexture("cloud.png");
		
		//spike.addComponent(new RenderComponent2D(&spike, spike_sprite, 0.1f));
		spike.addComponent<RenderComponent2D>(&spike, spike_sprite, 0.1f);
		spike.setTransform(500, 400);
		if (!spike.getComponent<RenderComponent2D>()) {
			std::cout << "NULL!" << std::endl;
		}
		World2D::root.addChild(&spike);

		// Animations
		zapper_anim.sprites.push_back(Graphics2D::loadTexture("zapper1.png"));
		zapper_anim.sprites.push_back(Graphics2D::loadTexture("zapper2.png"));
		zapper_anim.sprites.push_back(Graphics2D::loadTexture("zapper3.png"));
		zapper_anim.sprites.push_back(Graphics2D::loadTexture("zapper4.png"));

		zapper.addBehavior<Animator2D>(&zapper, &zapper_anim);
		zapper.getComponent<RenderComponent2D>()->setScale(0.5f);
		zapper.setTransform(700, 300);
		World2D::root.addChild(&zapper);

		zapper2_anim.sprite_sheet = Graphics2D::loadTexture("zapper.png");
		//std::cout << "Zapper sheet is " << zapper2_anim.sprite_sheet->width << " by " << zapper2_anim.sprite_sheet->height << std::endl;
		zapper2_anim.rows = 2;
		zapper2_anim.columns = 2;
		zapper2_anim.num_frames = 4;
		zapper2.addBehavior(new AnimatorSheet(&zapper2, &zapper2_anim));
		zapper2.getComponent<RenderComponent2D>()->setScale(0.5f);
		zapper2.setTransform(600, 100);
		World2D::root.addChild(&zapper2);

		haha = std::unique_ptr<Sound2D>(AudioManager2D::loadSound("haha.wav"));

		// Physics
		// body = Quantum2D::QuantumWorld2D::genRigidbody(spike.getTransformID());
	}

	void update(tD_delta delta) override {
		// Quantum2D::Rigidbody2D rbody = Quantum2D::QuantumWorld2D::getRigidbody(body);
		// std::cout << "Velocity: " << rbody.velocity.x << ", " << rbody.velocity.y << std::endl;

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
			zapper2.getComponent<RenderComponent2D>()->toggleVisibility();
		}

		// Stretching
		if (Input::keydown[Input::K_LSHIFT]) {
			zapper2.getComponent<RenderComponent2D>()->setScale(zapper2.getComponent<RenderComponent2D>()->getScale() + growspeed * delta);
		}
		if (Input::keydown[Input::K_LCTRL]) {
			zapper2.getComponent<RenderComponent2D>()->setScale(zapper2.getComponent<RenderComponent2D>()->getScale() - growspeed * delta);
		}

		// Flipping and velocity
		if (Input::keyup[Input::K_DOWN]) {
			zapper2.getComponent<RenderComponent2D>()->flipX();
			// Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(0, -movespeed));
		}
		if (Input::keyup[Input::K_UP]) {
			zapper2.getComponent<RenderComponent2D>()->flipY();
			// Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(0, movespeed));
		}

		// Movement
		if (Input::keydown[Input::K_W]) {
			zapper2.getTransform().position.y -= movespeed * delta;
		}
		if (Input::keydown[Input::K_S]) {
			zapper2.getTransform().position.y += movespeed * delta;
		}
		if (Input::keydown[Input::K_A]) {
			zapper2.getTransform().position.x -= movespeed * delta;
		}
		if (Input::keydown[Input::K_D]) {
			zapper2.getTransform().position.x += movespeed * delta;
		}

		// Rotation and velocity
		if (Input::keydown[Input::K_LEFT]) {
			zapper2.setRotation(zapper2.getTransform().rotation - spinspeed * delta);
			// Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(-movespeed, 0));
		}
		if (Input::keydown[Input::K_RIGHT]) {
			zapper2.setRotation(zapper2.getTransform().rotation + spinspeed * delta);
			// Quantum2D::QuantumWorld2D::getRigidbody(body).velocity.add(Vector2<float>(movespeed, 0));
		}

		// Sound
		if (Input::keyup[Input::K_F]) {
			haha->play();
		}


		// Touch
		if (Input::touch_down) {
			Entity2D *spawn = new Entity2D();
			spawn->addComponent(new RenderComponent2D(spawn, cloud_sprite, 0.1f));
			spawn->setTransform(Input::touch_pos.x * window.x, Input::touch_pos.y * window.y);
			objects.push_back(std::unique_ptr<Entity2D>(spawn));
		}

		//std::cout << "Delta = " << delta << "ms; FPS = " << Time::fps << std::endl;
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
