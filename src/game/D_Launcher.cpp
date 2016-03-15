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

#include "D_Launcher.h"

#include <iostream>
#include <memory>
#include "D_typedefs.h"

#include "D_AudioManager2D.h"
#include "D_DesktopLogger.h"
#include "D_Graphics2D.h"
#include "D_EventHandler.h"
#include "D_Log.h"
#include "D_Time.h"
#include "D_World2D.h"

#if defined __ANDROID__ || defined IOS || _WIN32 || defined __APPLE__
#include "D_SDLDiskJockey2D.h"
#include "D_SDLEventHandler.h"
#include "D_SDLRenderer2D.h"
#include "D_SDLTimer.h"
#endif

namespace Diamond {
    namespace Launcher {
        bool is_open = true;
        Config config = Config();
        
        static std::unique_ptr<EventHandler> events = nullptr;

        static int nframes = 0;

        static void initDesktop() {
            Log::setLogger(new DesktopLogger());
            
            if (!Graphics2D::initRenderer(new SDLRenderer2D())) {
                // TODO: Handle renderer initialization failure
            }

            if (!AudioManager2D::initDj(new SDLDiskJockey2D())) {
                // TODO: Handle audio initialization failure
            }
            
            Time::setTimer(new SDLTimer());
            
            events = std::unique_ptr<EventHandler>(new SDLEventHandler());
        }

        static void initMobile() {
            config.fullscreen = true;

            Log::setLogger(new DesktopLogger()); // temporary
            
            if (!Graphics2D::initRenderer(new SDLRenderer2D())) {
                // TODO: Handle renderer initialization failure
            }

            if (!AudioManager2D::initDj(new SDLDiskJockey2D())) {
                // TODO: Handle audio initialization failure
            }

            Time::setTimer(new SDLTimer());
            
            events = std::unique_ptr<EventHandler>(new SDLEventHandler());
        }
    }
}

void Diamond::Launcher::launch(Game &game) {
#if defined __ANDROID__ || defined IOS // TODO: What is the IOS platform macro? Or define one manually!
    // Android launcher
    initMobile();
#elif defined _WIN32 || defined __APPLE__
    initDesktop(); // Desktop launcher (windows/osx)
#else
    // TODO: Log this using logger, and use a better RAII-compliant exit method! (ex. exceptions)
    std::cout << "Platform unsupported!" << std::endl;
    std::exit();
#endif

    // Init physics
    if (!Quantum2D::QuantumWorld2D::init()) {
        // TODO: Handle physics initialization failure
    }

    // Init time
    tD_time time, last_time = Time::msElapsed();
    tD_delta delta;
    
    // Init game
    game.init();

    // Update
    while (Launcher::is_open) {
        ++nframes;
        
        time = Time::msElapsed();
        delta = time - last_time;
        last_time = time;
        
        Time::fps = nframes / (time / 1000.0);
        
        Quantum2D::QuantumWorld2D::step(delta);
        events->update();
        World2D::update(delta);
        game.update(delta);
        Graphics2D::renderAll();
    }

    // End game
    game.quit();
}

void Diamond::Launcher::quit() {
    is_open = false;
}
