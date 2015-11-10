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

#include "D_Graphics2D.h"
#include "D_Launcher.h"
#include "D_RenderObj2D.h"

Diamond::GameObject2D::GameObject2D(std::shared_ptr<Texture> sprite) : sprite(sprite), render_obj(nullptr), visible(true) {
	Graphics2D::genRenderObj(this, sprite.get());
}

// TODO: test
Diamond::GameObject2D::GameObject2D(const GameObject2D &other) : sprite(other.sprite), render_obj(nullptr), visible(other.visible) {
	Graphics2D::genRenderObj(this, sprite.get());
	if (!visible) {
		Graphics2D::deactivateRenderObj(render_obj->index);
	}
	
	render_obj->transform = other.render_obj->transform;
	if (other.isFlippedX())	flipX();
	if (other.isFlippedY())	flipY();
}

// TODO: test
Diamond::GameObject2D::GameObject2D(GameObject2D &&other) : sprite(other.sprite), render_obj(other.render_obj), visible(other.visible) {
	reAdoptRenderObj();

	other.sprite = nullptr;
	other.render_obj = nullptr;
	other.visible = false;
}

// TODO: test
Diamond::GameObject2D &Diamond::GameObject2D::operator=(const GameObject2D &other) {
	if (this != &other) {
		destroyRenderObj();

		sprite = other.sprite;
		visible = other.visible;
		Graphics2D::genRenderObj(this, sprite.get());
		if (!visible) {
			Graphics2D::deactivateRenderObj(render_obj->index);
		}
		
		render_obj->transform = other.render_obj->transform;
		if (other.isFlippedX())	flipX();
		if (other.isFlippedY())	flipY();
	}

	return *this;
}

// TODO: test
Diamond::GameObject2D &Diamond::GameObject2D::operator=(GameObject2D &&other) {
	if (this != &other) {
		destroyRenderObj();

		sprite = other.sprite;
		render_obj = other.render_obj;
		visible = other.visible;

		reAdoptRenderObj();

		other.sprite = nullptr;
		other.render_obj = nullptr;
		other.visible = false;
	}

	return *this;
}

std::shared_ptr<Diamond::Texture> Diamond::GameObject2D::getSprite() const {
	return sprite;
}

void Diamond::GameObject2D::setSprite(std::shared_ptr<Texture> sprite) {
	this->sprite = sprite;
	render_obj->setTexture(sprite.get());
}

Diamond::Transform2 Diamond::GameObject2D::getTransform() const {
	return render_obj->transform;
}

void Diamond::GameObject2D::setTransform(Diamond::Transform2 &transform) {
	render_obj->transform = transform;
}

void Diamond::GameObject2D::setTransform(Diamond::Vector2 &position) {
	render_obj->transform.position = position;
}

void Diamond::GameObject2D::setTransform(float x, float y, float rotation, float scale) {
	render_obj->transform.position.x = x;
	render_obj->transform.position.y = y;
	render_obj->transform.rotation = rotation;
	render_obj->transform.scale = scale;
}

void Diamond::GameObject2D::setTransform(float x, float y) {
	render_obj->transform.position.x = x;
	render_obj->transform.position.y = y;
}

void Diamond::GameObject2D::setRotation(float rotation) {
	render_obj->transform.rotation = rotation;
}

void Diamond::GameObject2D::setScale(float scale) {
	render_obj->transform.scale = scale;
}

void Diamond::GameObject2D::flipX() {
	render_obj->flipX();
}

void Diamond::GameObject2D::flipY() {
	render_obj->flipY();
}

int Diamond::GameObject2D::isFlippedX() const {
	return render_obj->isFlippedX();
}

int Diamond::GameObject2D::isFlippedY() const {
	return render_obj->isFlippedY();
}

bool Diamond::GameObject2D::isVisible() const {
	return visible;
}

void Diamond::GameObject2D::makeVisible() {
	if (!visible) {
		Graphics2D::activateRenderObj(render_obj->index);
		visible = true;
	}
}

void Diamond::GameObject2D::makeInvisible() {
	if (visible) {
		Graphics2D::deactivateRenderObj(render_obj->index);
		visible = false;
	}
}

void Diamond::GameObject2D::toggleVisibility() {
	visible ? makeInvisible() : makeVisible();
}

void Diamond::GameObject2D::reAdoptRenderObj() {
	render_obj->parent = this;
}

void Diamond::GameObject2D::setRenderObj(RenderObj2D *render_obj) {
	this->render_obj = render_obj;
}

void Diamond::GameObject2D::destroyRenderObj() {
	if (render_obj != nullptr) {
		if (visible) {
			Graphics2D::destroyRenderObj(render_obj->index);
		}
		else {
			Graphics2D::destroyInactiveRenderObj(render_obj->index);
		}
	}
	render_obj = nullptr;
}

Diamond::GameObject2D::~GameObject2D() {
	// TODO: find exception-safer method of memory management. ie it's possible that render_obj has been destroyed/game has ended/crashed even if is_open = true
	if (Launcher::is_open)	destroyRenderObj();
}
