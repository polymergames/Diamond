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

#ifndef D_TEXTURE_FACTORY_H
#define D_TEXTURE_FACTORY_H

#include <string>
#include <unordered_map>
#include "D_Renderer2D.h"
#include "D_typedefs.h"

namespace Diamond {
    /**
      Loads and caches reusable textures identified by path.
      If loadTexture is called on the same path multiple times without
      calling unLoadTexture, the texture file will only be loaded the first time
      and the stored texture object will be returned in subsequent loads.
      When this factory is destroyed, all cached textures will be freed.
    */
    class TextureFactory {
    public:
        TextureFactory(Renderer2D *renderer, const std::string &pathRoot = "");
        ~TextureFactory();

        /**
         Loads a texture with the file path formed by appending the given filename
         to the path root given in initial construction.
         Returns nullptr if failed to load.
        */
        DumbPtr<Texture> loadTexture(const std::string &fileName);
        
        /**
         Erases the texture with the given file name from internal store
         if it is cached.
        */
        void unLoadTexture(const std::string &fileName);
        
    private:
        Renderer2D *m_renderer;
        std::string m_pathRoot;
        
        std::unordered_map<std::string, DumbPtr<Texture> > m_textureMap;
    };
}

#endif // D_TEXTURE_FACTORY_H
