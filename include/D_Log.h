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

#ifndef D_LOG_H
#define D_LOG_H

#include <ctime>
#include <string>
#include <iomanip>
#include <iostream>
#include "D_Logger.h"

namespace Diamond {
    namespace Log {
        
        /**
         Sets the logging implementation.
        */
        void setLogger(Logger *logger);
        
        /**
         Logs a message to the current log stream.
        */
        void log(const std::string &message);

        /**
         Outputs the current date and time to a given stream.
        */
        inline void logTime(std::ostream &os) {
            std::time_t t = std::time(nullptr);
            struct tm *now = std::localtime(&t);
            os << now->tm_mon + 1 << "/" << now->tm_mday << "/" << now->tm_year + 1900
               << " " << now->tm_hour
               << ":" << std::setw(2) << std::setfill('0')
               << now->tm_min
               << ":" << std::setw(2) << std::setfill('0')
               << now->tm_sec;
        }
    };
}

#endif // D_LOG_H
