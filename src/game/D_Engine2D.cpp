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

// Quantum2D
#include "D_QuantumWorld2D.h"

Diamond::Engine2D::Engine2D() 
    : is_running(false), 
      logger(nullptr), 
      renderer(nullptr), 
      dj(nullptr), 
      timer(nullptr), 
      event_handler(nullptr), 
      phys_world(nullptr), 
      world(nullptr) {}


bool Diamond::Engine2D::init(const Config &config) {
    this->config = config;
    bool success = false;

#if defined _WIN32
    success = initWindows(config);
#elif defined __APPLE__
    success = initMac(config);
#elif defined __ANDROID__
    success = initAndroid(config);
#elif defined IOS // TODO: What is the IOS platform macro? Or define one manually!
    success = initIOS(config);
#else
    // TODO: Log this error somehow
    std::cout << "Platform unsupported!" << std::endl;
    return false;
#endif

    if (success) {
        // Init Entity world
        world = new World2D(phys_world);
    }

    return success;
}

void Diamond::Engine2D::launch(Game2D &game) {
    is_running = true;
    game.setEngine(this);

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
        timer->setDelta(delta);
        timer->setFPS(nframes / (time / 1000.0));

        phys_world->step(delta);
        event_handler->update();
        world->update(delta);
        game.update(delta);
        renderer->renderAll();
    }

    // End game
    game.quit();
    world->killAll();
    shutDown();
}


bool Diamond::Engine2D::initWindows(const Config &config) {
    logger = new DesktopLogger();

    renderer = new SDLRenderer2D();
    if (!renderer->init(config)) {
        // TODO: Handle renderer initialization failure
        return false;
    }

    dj = new SDLDiskJockey2D();
    if (!dj->init(config)) {
        // TODO: Handle audio initialization failure
        return false;
    }

    timer = new SDLTimer();
    event_handler = new SDLEventHandler(this);

    phys_world = new DQuantumWorld2D();
    if (!phys_world->init(config)) {
        // TODO: Handle physics initialization failure
        return false;
    }

    return true;
}

bool Diamond::Engine2D::initMac(const Config &config) {
    return initWindows(config);
}

bool Diamond::Engine2D::initAndroid(const Config &config) {
    Config myconf = config;
    myconf.fullscreen = true;

    return initWindows(myconf); // temporary
}

bool Diamond::Engine2D::initIOS(const Config &config) {
    return initAndroid(config);
}


void Diamond::Engine2D::shutDown() {
    delete logger;
    delete renderer;
    delete dj;
    delete timer;
    delete event_handler;
    delete phys_world;
    delete world;
}

