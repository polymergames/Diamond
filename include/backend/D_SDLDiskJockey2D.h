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

#ifndef D_SDL_DISK_JOCKEY_2D_H
#define D_SDL_DISK_JOCKEY_2D_H

#include "D_DiskJockey2D.h"

namespace Diamond {
    class SDLDiskJockey2D : public DiskJockey2D {
    public:
        ~SDLDiskJockey2D();

        bool init(const Config &config) override;

        DumbPtr<Sound2D> loadSound(std::string path) override;

        DumbPtr<Music> loadMusic(std::string path) override;

        int getMaxVolume() const override;

        void pauseMusic() override;

        void resumeMusic() override;

        void stopMusic() override;

        bool isMusicPlaying() const override;

        int getMusicVolume() const override;

        void setMusicVolume(int volume) override;
    };
}

#endif // D_SDL_DISK_JOCKEY_2D_H
