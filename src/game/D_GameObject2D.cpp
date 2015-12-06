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

#include "D_GameObject2D.h"

#include "D_Launcher.h"
#include "D_RenderObj2D.h"

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite, bool visible)
: sprite(sprite), visible(visible) {
	transform = Quantum2D::QuantumWorld2D::genTransform();
	if (visible) {
		render_obj = Graphics2D::genRenderObj(sprite.get(), transform);
	}
	else {
		render_obj = Diamond::INVALID;
	}
	setScale(1.0f);
}

// TODO: test
Diamond::GameObject2D::GameObject2D(const GameObject2D &other)
: sprite(other.sprite), visible(other.visible), scale(other.scale) {
	transform = Quantum2D::QuantumWorld2D::genTransform();
	getTransform() = other.getTransform();
	if (visible) {
		render_obj = Graphics2D::genRenderObj(sprite.get(), transform);
	}
	else {
		render_obj = Diamond::INVALID;
	}
	
	if (other.isFlippedX())	flipX();
	if (other.isFlippedY())	flipY();
}

// TODO: test
Diamond::GameObject2D::GameObject2D(GameObject2D &&other)
: sprite(other.sprite), transform(other.transform), render_obj(other.render_obj), visible(other.visible), scale(other.scale) {
	other.sprite = nullptr;
	other.transform = Diamond::INVALID;
	other.render_obj = Diamond::INVALID;
}

// TODO: test
Diamond::GameObject2D &Diamond::GameObject2D::operator=(const GameObject2D &other) {
	if (this != &other) {
		sprite = other.sprite;
		visible = other.visible;
		scale = other.scale;
		
		getTransform() = other.getTransform();
		if (visible) {
			render_obj = Graphics2D::genRenderObj(sprite.get(), transform);
		}
		else {
			render_obj = Diamond::INVALID;
		}
		
		if (other.isFlippedX())	flipX();
		if (other.isFlippedY())	flipY();
	}

	return *this;
}

// TODO: test
Diamond::GameObject2D &Diamond::GameObject2D::operator=(GameObject2D &&other) {
	if (this != &other) {
		freeRenderObj();

		sprite = other.sprite;
		transform = other.transform;
		render_obj = other.render_obj;
		visible = other.visible;
		scale = other.scale;

		other.sprite = nullptr;
		other.transform = Diamond::INVALID;
		other.render_obj = Diamond::INVALID;
	}

	return *this;
}

void Diamond::GameObject2D::setSprite(std::shared_ptr<Texture> sprite) {
	this->sprite = sprite;
	Graphics2D::getRenderObj(render_obj)->setTexture(sprite.get());
	applyScale();
}

void Diamond::GameObject2D::setTransform(Transform2i &new_transform) {
	getTransform() = new_transform;
	applyScale();
}

void Diamond::GameObject2D::setScale(float scale) {
	this->scale = scale;
	applyScale();
}

void Diamond::GameObject2D::makeVisible() {
	if (!visible) {
		render_obj = Graphics2D::genRenderObj(sprite.get(), transform);
		visible = true;
	}
}

void Diamond::GameObject2D::makeInvisible() {
	if (visible) {
		freeRenderObj();
		visible = false;
	}
}

void Diamond::GameObject2D::toggleVisibility() {
	visible ? makeInvisible() : makeVisible();
}

void Diamond::GameObject2D::applyScale() {
	getTransform().size = Vector2i(sprite->width * scale, sprite->height *scale);
}

void Diamond::GameObject2D::freeTransform() {
	if ((t_valid)transform != Diamond::INVALID) {
		Quantum2D::QuantumWorld2D::freeTransform(transform);
		transform = Diamond::INVALID;
	}
}

void Diamond::GameObject2D::freeRenderObj() {
	if ((t_valid)render_obj != Diamond::INVALID) {
		Graphics2D::freeRenderObj(render_obj);
		render_obj = Diamond::INVALID;
	}
}

Diamond::GameObject2D::~GameObject2D() {
	// TODO: find exception-safer method of memory management. ie it's possible that render_obj has been destroyed/game has ended/crashed even if is_open = true
	if (Launcher::is_open) {
		freeTransform();
		freeRenderObj();
	}
}
