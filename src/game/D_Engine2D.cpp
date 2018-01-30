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

#include "D_Engine2D.h"

#include <ctime>
#include <iostream>
#include "D_Game2D.h"
#include "D_Log.h"
#include "D_StreamLogger.h"

// SDL subsystems
#include "D_SDLDiskJockey2D.h"
#include "D_SDLEventHandler.h"
#include "D_SDLRenderer2D.h"
#include "D_SDLTimer.h"

// Quantum2D
#include "D_QuantumWorld2D.h"

#if defined __ANDROID__
#include "D_AndroidLogger.h"
#endif

// Are we on iOS?
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#define IPHONE
#else
#define MACOSX
#endif
#endif

Diamond::Engine2D::Engine2D(const Config &config, bool &success)
    : is_running(false),
      is_paused(false),
      config(config),
      renderer(nullptr),
      dj(nullptr),
      timer(nullptr),
      event_handler(nullptr),
      phys_world(nullptr),
      transformPool(config.max_gameobjects_estimate) {

    success = false;

#if defined _WIN32
    success = initWindows();
#elif defined __ANDROID__
    success = initAndroid();
#elif defined IPHONE
    success = initIOS();
#elif defined MACOSX
    success = initMac();
#else
    Log::log("Platform unsupported!");
    success = false;
#endif

    if (success)
        Log::log("Diamond systems are online and ready to roll.");
    else
        Log::log("We have a problem sir.");
}


Diamond::Engine2D::~Engine2D() {
    Log::log("Diamond systems shutting down.");
    delete renderer;
    delete dj;
    delete timer;
    delete event_handler;
    delete phys_world;
    if (logstream.is_open())
        logstream.close();
}

void Diamond::Engine2D::launch(Game2D &game) {
    is_paused = false;
    is_running = true;

    // Init time
    tD_time time, last_time = timer->msElapsed();
//    tD_delta delta = 1000 / renderer->getRefreshRate();
    // TODO: BUG: getting the refresh rate from the renderer
    // causes it to crash on Android. Fix it and remove hardcoded value!
    tD_delta delta = 1000 / 60;
    int nframes = 0;

    // DEBUG Benchmark
    // clock_t clocktime;
    // clock_t getmstime;
    // clock_t eventtime;
    // clock_t gametime;
    // clock_t physicstime;
    // clock_t postphysicsgametime;
    // clock_t rendertime;

    // Initialize the game
    if (game.init()) {
    
        // Game loop
        while (is_running) {
            // Update time junk
            ++nframes;

            // clocktime = clock();
            time = timer->msElapsed();
            // getmstime = clock() - clocktime;
            
            // if vsync is on, we will use the delta value calculated
            // when delta was initialized based on the refresh rate.
            if (!config.vsync) {
                delta = time - last_time;
                last_time = time;
            }

            // TODO: replace with timer functions, timer calculates and stores its own values
            // then I just have to go get those values ya know?
            timer->setDelta(delta);
            timer->setFPS(nframes / (time / 1000.0));

            // Catch up on events
            // clocktime = clock();
            event_handler->update();
            // eventtime = clock() - clocktime;

            if (is_paused) {
                game.pausedUpdate(delta);
            }
            else {
                // Update game logic
                // clocktime = clock();
                game.update(delta);
                // gametime = clock() - clocktime;

                // Update physics
                // clocktime = clock();
                phys_world->update(delta);
                // physicstime = clock() - clocktime;

                // Update post-physics game logic
                // clocktime = clock();
                game.postPhysicsUpdate(delta);
                // postphysicsgametime = clock() - clocktime;
            }

            // Draw pictures!
            // clocktime = clock();
            renderer->renderAll();
            // rendertime = clock() - clocktime;

            // DEBUG
            // TODO: report to an engine benchmarking system
            // float total = eventtime + gametime + physicstime + postphysicsgametime + rendertime;
            // std::cout << "Delta: " << delta << std::endl;
    //        std::cout << "Event time: " << (float)eventtime / total << std::endl;
    //        std::cout << "Game time: " << (float)gametime / total << std::endl;
    //        std::cout << "Physics time: " << (float)physicstime / total << std::endl;
    //        std::cout << "Post physics game time: " << (float)postphysicsgametime / total << std::endl;
    //        std::cout << "Render time: " << (float)rendertime / total << std::endl;
            // std::cout << "Get ms ticks: " << (float)getmstime << std::endl;
            // std::cout << "Event ticks: " << (float)eventtime << std::endl;
            // std::cout << "Game ticks: " << (float)gametime << std::endl;
            // std::cout << "Physics ticks: " << (float)physicstime << std::endl;
            // std::cout << "Post physics game ticks: " << (float)postphysicsgametime << std::endl;
            // std::cout << "Render ticks: " << (float)rendertime << std::endl;
            // std::cout << "Total ticks: " << total << std::endl << std::endl;
        }
    }

    // End game
    game.quit();
}


void Diamond::Engine2D::refreshRenderer() {
    SDLEventHandler *sdlEventHandler = dynamic_cast<SDLEventHandler*>(event_handler);
    
    if (sdlEventHandler) {
        sdlEventHandler->setResolution(renderer->getResolution());
    }
}


bool Diamond::Engine2D::initSDL() {
    bool success = true;
    renderer = new SDLRenderer2D(config, success);
    if (!success) {
        // TODO: Handle renderer initialization failure
        return false;
    }

    dj = new SDLDiskJockey2D();
    if (!dj->init(config) && config.require_audio) {
        // TODO: Handle audio initialization failure
        return false;
    }

    timer = new SDLTimer();
    event_handler = new SDLEventHandler(
//        renderer->getScreenResolution(),
        // Honestly, I don't know if we should be using getResolution or getScreenResolution
        renderer->getResolution(),
        [this]() { is_running = false; }
    );

    return true;
}

bool Diamond::Engine2D::initQuantum() {
    phys_world = new QuantumWorld2D();
    if (!phys_world->init(config)) {
        // TODO: Handle physics initialization failure
        return false;
    }

    return true;
}

bool Diamond::Engine2D::initWindows() {
    logstream.open(config.log_path, std::ios::app);
    if (!logstream.is_open())
        std::cout << "Logger ERROR: Failed to open log file " << config.log_path << "!" << std::endl;
    else
        Log::setLogger(new StreamLogger(logstream));

    return initSDL() && initQuantum();
}

bool Diamond::Engine2D::initMac() {
    return initWindows();
}

bool Diamond::Engine2D::initAndroid() {
    config.fullscreen = true;
    // Log::setLogger(new FileLogger(config.log_path)); // TODO: Android file logger
#if defined __ANDROID__
    Log::setLogger(new AndroidLogger(config.game_name));
#endif
    Log::log("Hello Android");
    return initSDL() && initQuantum();
}

bool Diamond::Engine2D::initIOS() {
    config.fullscreen = true;
    // TODO: iOS logger
    Log::log("Hello IOS");
    return initSDL() && initQuantum();
}
