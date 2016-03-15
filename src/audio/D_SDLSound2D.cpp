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

#include "D_SDLSound2D.h"

Diamond::SDLSound2D::SDLSound2D(Mix_Chunk *sound) : sound(sound), channel(0) {}

Diamond::SDLSound2D::~SDLSound2D() {
    Mix_FreeChunk(sound);
}

void Diamond::SDLSound2D::play() {
    channel = Mix_PlayChannel(-1, sound, 0);
}

void Diamond::SDLSound2D::pause() {
    Mix_Pause(channel);
}

void Diamond::SDLSound2D::resume() {
    Mix_Resume(channel);
}

void Diamond::SDLSound2D::stop() {
    Mix_HaltChannel(channel);
}

int Diamond::SDLSound2D::getVolume() const {
    return Mix_VolumeChunk(sound, -1);
}

void Diamond::SDLSound2D::setVolume(int volume) {
    Mix_VolumeChunk(sound, volume);
}
