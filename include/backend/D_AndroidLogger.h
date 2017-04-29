/*
    Copyright 2017 Ahnaf Siddiqui

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

#ifndef D_ANDROID_LOGGER_H
#define D_ANDROID_LOGGER_H

#include "D_Logger.h"
#include <android/log.h>

namespace Diamond {
    class AndroidLogger : public Logger {
    public:
        AndroidLogger(const std::string &appName) : appName(appName.c_str()) {}
        
        void log(const std::string &message) override {
            __android_log_print(ANDROID_LOG_VERBOSE, appName, "%s", message.c_str());
        }
        
    private:
        const char *appName;
    };
}

#endif // D_ANDROID_LOGGER_H
