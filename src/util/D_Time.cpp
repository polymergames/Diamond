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

#include "D_Time.h"

#include <memory>

#include "D_Timer.h"

namespace Diamond {
    namespace Time {
        float fps = 0;
        tD_delta delta = 0;
        
        static std::unique_ptr<Timer> timer = nullptr;
    }
}

tD_time Diamond::Time::msElapsed() {
    return timer->msElapsed();
}

void Diamond::Time::setTimer(Timer *timer) {
    Time::timer = std::unique_ptr<Timer>(timer);
}
