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

#ifndef D_FILE_LOGGER_H
#define D_FILE_LOGGER_H

#include "D_Logger.h"
#include <fstream>

namespace Diamond {
    class FileLogger : public Logger {
    public:
        FileLogger(const std::string &filename) : logfile(filename, std::ios::app) {
            if (!logfile.is_open()) {
                std::cout << "Logger ERROR: Failed to open log file " << filename << "!" << std::endl;
            }
            else {
                logfile << std::endl << filename << " opened on ";
                Log::logTime(logfile);
                logfile << std::endl;
            }
        }

        void log(const std::string &message) override {
            std::cout << message << std::endl;
            if (logfile.is_open())
                logfile << message << std::endl;
        }

        ~FileLogger() {
            if (logfile.is_open()) {
                logfile.close();
            } 
        }

    private:
        std::ofstream logfile;
    };
}

#endif // D_FILE_LOGGER_H
