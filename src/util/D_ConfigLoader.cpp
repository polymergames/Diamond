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

#include "D_ConfigLoader.h"


const std::array<std::string, 1> Diamond::ConfigLoader::ignoreStrings = { "\r" };

bool Diamond::ConfigLoader::configureLine(const std::string &line,
                                          ConfigTable &config) {
    std::string key, value;

    Status status = parseLine(line, key, value);

    switch (status) {
        case ERROR:
            return false;
        case PARSED:
            config.set(key, value);
            break;
        default:
            break;
    }

    return true;
}

Diamond::ConfigLoader::Status Diamond::ConfigLoader::parseLine(const std::string &line,
                                                               std::string &key,
                                                               std::string &value) {
    auto first = line.find_first_not_of(' ');

    if (first == std::string::npos)
        return EMPTY;

    if (line[first] == commentMark)
        return COMMENT;


    auto last = line.size() - 1;
    auto c = line.find(commentMark);
    if (c != std::string::npos)
        last = c - 1;

    // Find where the key and value are separated
    auto i = line.find(configDelim);

    // Check that key-value delimiter is not
    // at beginning or end
    if (i == std::string::npos ||
        i <= first ||
        i >= last)
        return ERROR;

    key = line.substr(first, i - first);
    value = line.substr(i + 1, last - i);

    trimEndSpace(key);
    trimFrontSpace(value);
    trimEndSpace(value);

    removeStrings(key, ignoreStrings);
    removeStrings(value, ignoreStrings);

    return PARSED;
}


void Diamond::ConfigLoader::trimFrontSpace(std::string &str) {
    auto i = str.find_first_not_of(' ');
    str.erase(0, i);
}


void Diamond::ConfigLoader::trimEndSpace(std::string &str) {
    auto i = str.find_last_not_of(' ');

    if (i != std::string::npos && i + 1 < str.size()) {
        str.erase(i + 1);
    }
}
