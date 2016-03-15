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

#include "D_AudioManager2D.h"

#include <memory>

#include "D_DiskJockey2D.h"

namespace Diamond {
    namespace AudioManager2D {
        static std::unique_ptr<Diamond::DiskJockey2D> dj = nullptr;
    }
}

Diamond::Sound2D *Diamond::AudioManager2D::loadSound(std::string path) {
    return dj->loadSound(path);
}

Diamond::Music *Diamond::AudioManager2D::loadMusic(std::string path) {
    return dj->loadMusic(path);
}

int Diamond::AudioManager2D::getMaxVolume() {
    return dj->getMaxVolume();
}

void Diamond::AudioManager2D::pauseMusic() {
    dj->pauseMusic();
}

void Diamond::AudioManager2D::resumeMusic() {
    dj->resumeMusic();
}

void Diamond::AudioManager2D::stopMusic() {
    dj->stopMusic();
}

bool Diamond::AudioManager2D::isMusicPlaying() {
    return dj->isMusicPlaying();
}

int Diamond::AudioManager2D::getMusicVolume() {
    return dj->getMusicVolume();
}

void Diamond::AudioManager2D::setMusicVolume(int volume) {
    dj->setMusicVolume(volume);
}

bool Diamond::AudioManager2D::initDj(DiskJockey2D *dj) {
    if (AudioManager2D::dj == nullptr && dj != nullptr) {
        AudioManager2D::dj = std::unique_ptr<DiskJockey2D>(dj);
        return dj->init();
    }
    return false;
}
