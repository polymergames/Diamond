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

#ifndef D_SOUND_2D_H
#define D_SOUND_2D_H

namespace Diamond {
    /**
     If using the SDL sound implementation, see D_SDLSound2D.h for an important note on the reliability of some functions.
    */
    class Sound2D {
    public:
        // TODO: bool is_playing()

        virtual ~Sound2D() {};
        
        virtual void play() = 0;
        
        virtual void pause() = 0;

        virtual void resume() = 0;

        virtual void stop() = 0;

        virtual int getVolume() const = 0;
        
        /**
         Note: you can use the getMaxVolume() function in AudioManager2D to scale your volume values.
        */
        virtual void setVolume(int volume) = 0;
    };
}

#endif // D_SOUND_2D_H
