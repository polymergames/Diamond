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

Diamond::Engine2D::Engine2D(const Config &config, bool &success)
    : is_running(false),
      config(config),
      renderer(nullptr),
      dj(nullptr),
      timer(nullptr),
      event_handler(nullptr),
      phys_world(nullptr),
      // TODO: construct transformPool with given estimate of how many transforms max would ever be onscreen
      transformPool(200) {

    success = false;

#if defined _WIN32
    success = initWindows();
#elif defined __APPLE__
    success = initMac();
#elif defined __ANDROID__
    success = initAndroid();
#elif defined IOS // TODO: What is the IOS platform macro? Or define one manually!
    success = initIOS();
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
    is_running = true;

    // Init time
    tD_time time, last_time = timer->msElapsed();
    tD_delta delta;
    int nframes = 0;

    // Game loop
    while (is_running) {
        // Update time junk
        ++nframes;

        time = timer->msElapsed();
        delta = time - last_time;
        last_time = time;

        // TODO: replace with timer functions, timer calculates and stores its own values
        // then I just have to go get those values ya know?
        timer->setDelta(delta);
        timer->setFPS(nframes / (time / 1000.0));

        // Catch up on events
        event_handler->update();

        // Update game logic
        game.update(delta);

        // Update physics
        phys_world->update(delta);

        // Update post-physics game logic
        game.postPhysicsUpdate(delta);

        // Draw pictures!
        renderer->renderAll();
    }

    // End game
    game.quit();
}


bool Diamond::Engine2D::initSDL() {
    renderer = new SDLRenderer2D();
    if (!renderer->init(config)) {
        // TODO: Handle renderer initialization failure
        return false;
    }

    dj = new SDLDiskJockey2D();
    if (!dj->init(config)) {
        // TODO: Handle audio initialization failure
        // Perhaps make audio non-critical, ie return success even if audio initialization failed
        // Or return a bitflag indicating which systems initialized successfully and which ones didn't
        return false;
    }

    timer = new SDLTimer();
    event_handler = new SDLEventHandler(
        renderer->getScreenResolution(),
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
    logstream.open(config.game_name + ".log", std::ios::app);
    if (!logstream.is_open())
        std::cout << "Logger ERROR: Failed to open log file " << config.game_name + ".log" << "!" << std::endl;
    else
        Log::setLogger(new StreamLogger(logstream));

    return initSDL() && initQuantum();
}

bool Diamond::Engine2D::initMac() {
    return initWindows();
}

bool Diamond::Engine2D::initAndroid() {
    config.fullscreen = true;
    // Log::setLogger(new FileLogger(config.game_name + ".log")); // TODO: Android logger
    return initSDL() && initQuantum();
}

bool Diamond::Engine2D::initIOS() {
    return initAndroid();
}
