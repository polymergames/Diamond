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

#include "D_Log.h"

#include <iostream>
#include <memory>

namespace Diamond {
    namespace Log {
        static std::unique_ptr<Logger> logger = std::unique_ptr<Logger>(new Logger);
    }
}

void Diamond::Log::setLogger(Logger *logger) {
    // TODO: gotta completely refactor this junk
    // use a global stream object for logging
    if (logger)
        Log::logger = std::unique_ptr<Logger>(logger);
}

void Diamond::Log::log(const std::string &message) {
    logger->log(message);
}
