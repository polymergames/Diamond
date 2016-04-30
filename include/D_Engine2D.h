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

#ifndef D_ENGINE_H
#define D_ENGINE_H

#if defined __ANDROID__ || defined IOS
#include "SDL.h" // Has to be included with game's main function for SDL_main to work. TODO: include for iOS as well?
#endif

#include "D_Config.h"
#include "D_DataCenter.h"
#include "D_DiskJockey2D.h"
#include "D_EventHandler.h"
#include "D_PhysicsWorld2D.h"
#include "D_Renderer2D.h"
#include "D_Timer.h"
#include "D_World2D.h"

namespace Diamond {
    class Game2D;

    class Engine2D {
    public:
        Engine2D();

        virtual bool init(const Config &config);

        virtual void launch(Game2D &game);

        Config &getConfig() { return config; }

        Renderer2D *getRenderer() const { return renderer; }

        DiskJockey2D *getDJ() const { return dj; }

        Timer *getTimer() const { return timer; }

        EventHandler *getEventHandler() const { return event_handler; }

        PhysicsWorld2D *getPhysWorld() const { return phys_world; }

        World2D *getWorld() const { return world; }

        bool isRunning() const { return is_running; }

        void quit() { is_running = false; }

    protected:
        bool is_running;
        DataCenter data;
        Config config;
        Renderer2D *renderer;
        DiskJockey2D *dj;
        Timer *timer;
        EventHandler *event_handler;
        PhysicsWorld2D *phys_world;
        World2D *world;

        virtual bool initWindows(const Config &config);
        virtual bool initMac(const Config &config);
        virtual bool initAndroid(const Config &config);
        virtual bool initIOS(const Config &config);
        
        void shutDown();
    };
}

#endif // D_ENGINE_H
