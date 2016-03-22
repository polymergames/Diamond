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
#include "D_DesktopLogger.h"
#include "D_World2D.h"

// SDL subsystems
#include "D_SDLDiskJockey2D.h"
#include "D_SDLEventHandler.h"
#include "D_SDLRenderer2D.h"
#include "D_SDLTimer.h"

Diamond::Engine2D::Engine2D() 
    : is_running(false), 
      logger(nullptr), 
      renderer(nullptr), 
      dj(nullptr), 
      timer(nullptr), 
      event_handler(nullptr), 
      world(nullptr) {}


Diamond::Engine2D::~Engine2D() {
    delete logger;
    delete renderer;
    delete dj;
    delete timer;
    delete event_handler;
    delete world;
}

bool Diamond::Engine2D::init(Diamond::Config &config) {
    this->config = config;

#if defined _WIN32
    return initWindows(config);
#elif defined __APPLE__
    return initMac(config);
#elif defined __ANDROID__
    return initAndroid(config);
#elif defined IOS // TODO: What is the IOS platform macro? Or define one manually!
    return initIOS(config);
#else
    // TODO: Log this error somehow
    std::cout << "Platform unsupported!" << std::endl;
    return false;
#endif
}

void Diamond::Engine2D::launch(Diamond::Game2D &game) {
    is_running = true;
    game.setEngine(this);

    // Init physics TODO: create and init physics world object in init function
    if (!Quantum2D::QuantumWorld2D::init()) {
        // TODO: Handle physics initialization failure
    }

    // Init Entity world
    world = new World2D();

    // Init time
    tD_time time, last_time = timer->msElapsed();
    tD_delta delta;
    int nframes = 0;

    // Init game
    game.init();

    // Game loop
    while (is_running) {
        ++nframes;

        time = timer->msElapsed();
        delta = time - last_time;
        last_time = time;

        // TODO: replace with timer functions
        // Time::setDelta(delta);
        // Time::setFPS(nframes / (time / 1000.0));

        Quantum2D::QuantumWorld2D::step(delta); // TODO: replace with physics world object
        event_handler->update();
        world->update(delta);
        game.update(delta);
        renderer->renderAll();
    }

    // End game
    game.quit();
}

bool Diamond::Engine2D::initWindows(Config &config) {
    logger = new DesktopLogger();

    renderer = new SDLRenderer2D();
    if (!renderer->init()) {
        // TODO: Handle renderer initialization failure
        return false;
    }

    dj = new SDLDiskJockey2D();
    if (!dj->init()) {
        // TODO: Handle audio initialization failure
        return false;
    }

    timer = new SDLTimer();

    event_handler = new SDLEventHandler();

    return true;
}

bool Diamond::Engine2D::initMac(Config &config) {
    return initWindows(config);
}

bool Diamond::Engine2D::initAndroid(Config &config) {
    config.fullscreen = true;

    return initWindows(config); // temporary
}

bool Diamond::Engine2D::initIOS(Config &config) {
    return initAndroid(config);
}


