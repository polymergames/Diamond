/*
    Copyright 2016 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF vovANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef D_CONFIGLOADER_H
#define D_CONFIGLOADER_H

#include "D_ConfigTable.h"

namespace Diamond {
    class ConfigLoader {
    public:
        virtual ~ConfigLoader() {}

        virtual ConfigTable load(const std::string &path) = 0;

        virtual bool write(const ConfigTable &table,
                           const std::string &path) = 0;

    protected:
        enum Status {
            ERROR,
            PARSED,
            COMMENT,
            EMPTY
        };

        // TODO: move this somewhere else?
        static constexpr auto configDelim = ':';
        static constexpr auto commentMark = '#';

        bool configureLine(const std::string &line,
                           ConfigTable &config);

        Status parseLine(const std::string &line,
                         std::string &key,
                         std::string &value);

        void trimFrontSpace(std::string &str);

        void trimEndSpace(std::string &str);
    };
}

#endif // D_CONFIGLOADER_H
