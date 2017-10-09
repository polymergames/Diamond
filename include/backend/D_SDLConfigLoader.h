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

#ifndef D_SDLCONFIGLOADER_H
#define D_SDLCONFIGLOADER_H

#include "D_ConfigLoader.h"

namespace Diamond {
class SDLConfigLoader : public ConfigLoader {
 public:
  static const int DEFAULT_BUFSIZE = 100000;
  static const int LINESIZE = 1000;

  // All path arguments in this class's functions
  // should be relative to pathRoot.
  SDLConfigLoader(const std::string& pathRoot = "");

  // Parses the file at the given path using SDL IO
  // and returns any config that was found in the file.
  ConfigTable load(const std::string& path) override;

  // WARNING: this function is NOT implemented for SDLConfigLoader!
  // Try StdConfigLoader instead (might not work on mobile though)
  bool write(const ConfigTable& table, const std::string& path) override;

  // TODO: move this somewhere else?
  // Loads the contents of the file at the given path into a string
  // using SDL IO.
  std::string loadStr(const std::string& path);

 private:
  std::string m_pathRoot;
};
}

#endif  // D_SDLCONFIGLOADER_H
