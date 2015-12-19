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

#ifndef D_RENDER_COMPONENT_2D_H
#define D_RENDER_COMPONENT_2D_H

#include "D_Component.h"
#include "D_Graphics2D.h"
#include "D_Texture.h"

namespace Diamond {
	class RenderComponent2D : public Component {
		public:
		RenderComponent2D(Texture *sprite, bool visible = true, float scale = 1.0f);
		RenderComponent2D(std::shared_ptr<Texture> sprite, bool visible = true, float scale = 1.0f);
		~RenderComponent2D();

		void setParent(Entity2D *parent) override;

		std::shared_ptr<Texture> getSprite() const;
		void setSprite(Texture *sprite);
		void setSprite(std::shared_ptr<Texture> sprite);

		float getScale() const;
		void setScale(float scale);

		void flipX();
		void flipY();

		int isFlippedX() const;
		int isFlippedY() const;

		/**
		Returns whether this game object's sprite is currently being rendered.
		*/
		bool isVisible() const;

		/**
		Causes this game object to be rendered.
		This game object must have a sprite (use setSprite() if needed) before calling this function.
		*/
		void makeVisible();

		/**
		Causes this game object to stop being rendered.
		*/
		void makeInvisible();

		/**
		If this game object is currently visible, makes it invisible (ie not rendered), and vice versa.
		*/
		void toggleVisibility();

		private:
		Entity2D *parent;

		std::shared_ptr<Texture> sprite;
		renderobj_id render_obj;
		bool visible;
		float scale;

		void freeRenderObj();
	};
}

inline std::shared_ptr<Diamond::Texture> Diamond::RenderComponent2D::getSprite() const {
	return sprite;
}

inline void Diamond::RenderComponent2D::setSprite(Texture *sprite) {
	setSprite(std::shared_ptr<Texture>(sprite));
}

inline void Diamond::RenderComponent2D::setSprite(std::shared_ptr<Texture> sprite) {
	this->sprite = sprite;
	if ((tD_index)render_obj != Diamond::INVALID) {
		Graphics2D::getRenderObj(render_obj)->setTexture(sprite.get(), scale);
	}
}

inline float Diamond::RenderComponent2D::getScale() const {
	return scale;
}

void Diamond::RenderComponent2D::setScale(float scale) {
	this->scale = scale;
	if ((tD_index)render_obj != Diamond::INVALID) {
		Graphics2D::getRenderObj(render_obj)->applyScale(scale);
	}
}

inline void Diamond::RenderComponent2D::flipX() {
	Graphics2D::getRenderObj(render_obj)->flipX();
}

inline void Diamond::RenderComponent2D::flipY() {
	Graphics2D::getRenderObj(render_obj)->flipY();
}

inline int Diamond::RenderComponent2D::isFlippedX() const {
	return Graphics2D::getRenderObj(render_obj)->isFlippedX();
}

inline int Diamond::RenderComponent2D::isFlippedY() const {
	return Graphics2D::getRenderObj(render_obj)->isFlippedY();
}

inline bool Diamond::RenderComponent2D::isVisible() const {
	return visible;
}

void Diamond::RenderComponent2D::makeVisible() {
	if (!visible) {
		render_obj = Graphics2D::genRenderObj(sprite.get(), parent->getTransformID, scale);
		visible = true;
	}
}

void Diamond::RenderComponent2D::makeInvisible() {
	if (visible) {
		freeRenderObj();
		visible = false;
	}
}

void Diamond::RenderComponent2D::toggleVisibility() {
	visible ? makeInvisible() : makeVisible();
}

#endif // D_RENDER_COMPONENT_2D_H
