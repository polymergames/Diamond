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

#ifndef D_STREAM_LOGGER_H
#define D_STREAM_LOGGER_H

#include "D_Logger.h"
#include <ostream>

namespace Diamond {
    class StreamLogger : public Logger {
    public:
        StreamLogger(std::ostream &stream) : m_stream(stream) {
            if (m_stream.good()) {
                m_stream << std::endl << "Log opened on ";
                Log::logTime(stream);
                stream << std::endl;
            }
        }

        void log(const std::string &message) override {
            Logger::log(message);
            if(m_stream.good())
                m_stream << message << std::endl;
        }

    private:
        std::ostream &m_stream;
    };
}

#endif // D_STREAM_LOGGER_H
