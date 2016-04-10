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

#include "D_RenderComponent2D.h"

Diamond::RenderComponent2D::RenderComponent2D(Entity2D *parent, 
                                              Renderer2D *renderer, 
                                              std::shared_ptr<Texture> sprite, 
                                              float scale)
    : Component(parent), renderer(renderer), sprite(sprite), clip_dim(), scale(scale) {
    render_obj = renderer->genRenderObj(parent, sprite.get(), scale);
}

Diamond::RenderComponent2D::~RenderComponent2D() {
    freeRenderObj();
}

void Diamond::RenderComponent2D::freeRenderObj() {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->freeRenderObj(render_obj);
        render_obj = Diamond::INVALID;
    }
}
