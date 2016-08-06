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

#include "D_Log.h"
#include "D_StdConfigLoader.h"
#include <fstream>

Diamond::StdConfigLoader::StdConfigLoader(const std::string &pathRoot)
    : m_pathRoot(pathRoot) {}


Diamond::ConfigTable Diamond::StdConfigLoader::load(const std::string &path) {
    ConfigTable config;
    std::string fullPath = m_pathRoot + path;

    std::ifstream fileStream;
    fileStream.open(fullPath);

    if (fileStream.is_open()) {
        Log::log("Opened config file " + fullPath + " for reading");

        std::string line, key, value;

        while (std::getline(fileStream, line)) {
            if (!configureLine(line, config)) {
                Log::log("Failed to parse line " + line +
                         " in " + fullPath);
            }
        }

        fileStream.close();
    }
    else {
        Log::log("Failed to open config file " +
                 fullPath + " for reading");
    }

    return config;
}


bool Diamond::StdConfigLoader::write(const ConfigTable &table,
                                     const std::string &path) {
    std::string fullPath = m_pathRoot + path;

    std::ofstream filestream;
    filestream.open(fullPath);

    if (filestream.is_open()) {
        Log::log("Opened config file " + fullPath + " for writing");

        for (auto pair : table.data()) {
            // DEBUG
            // std::cout << pair.first << ":" << pair.second << std::endl;
            filestream << pair.first << ":" << pair.second << std::endl;
        }

        filestream.close();
    }
    else {
        Log::log("Failed to open config file " + fullPath + " for writing");
        return false;
    }

    return true;
}
