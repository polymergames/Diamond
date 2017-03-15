/*
    Copyright 2016 Ahnaf Siddiqui

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

#include "D_TextureFactory.h"
#include "D_Log.h"

Diamond::TextureFactory::TextureFactory(Renderer2D *renderer, const std::string &pathRoot)
    : m_renderer(renderer), m_pathRoot(pathRoot) {}

Diamond::TextureFactory::~TextureFactory() {
    for (auto i = m_textureMap.begin(); i != m_textureMap.end(); ++i) {
        i->second.free();
    }
}


Diamond::DumbPtr<Diamond::Texture> Diamond::TextureFactory::loadTexture(const std::string &fileName) {
    // Check if texture has already been loaded
    auto texture = m_textureMap[fileName];
    
    // Otherwise, load the texture and save it to the internal store
    if (!texture) {
        texture = m_renderer->loadTexture(m_pathRoot + fileName);
        m_textureMap[fileName] = texture;
    }
    
    return texture;
}


void Diamond::TextureFactory::unLoadTexture(const std::string &fileName) {
    m_textureMap[fileName].free();
    m_textureMap[fileName] = nullptr;
}
