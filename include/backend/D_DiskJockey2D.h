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

#ifndef D_DISK_JOCKEY_2D_H
#define D_DISK_JOCKEY_2D_H

#include <iostream>

#include "D_Config.h"
#include "D_Sound2D.h"
#include "D_Music.h"
#include "D_typedefs.h"

namespace Diamond {
    class DiskJockey2D {
    public:
        virtual ~DiskJockey2D() {};

        virtual bool init(const Config &config) = 0;

        virtual SharedPtr<Sound2D> loadSound(std::string path) = 0;

        virtual SharedPtr<Music> loadMusic(std::string path) = 0;

        virtual int getMaxVolume() const = 0;

        virtual void pauseMusic() = 0;

        virtual void resumeMusic() = 0;

        virtual void stopMusic() = 0;

        virtual bool isMusicPlaying() const = 0;

        virtual int getMusicVolume() const = 0;

        virtual void setMusicVolume(int volume) = 0;
    };
}

#endif // D_DISK_JOCKEY_2D_H
