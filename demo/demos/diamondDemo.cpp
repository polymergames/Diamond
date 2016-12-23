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
#include "CollideDemo.h"
#include "ParticleDemo.h"
#include "RandomDemo.h"


int main(int argc, char *argv[]) {
    Diamond::Config config;
    config.vsync = true;
    //config.bg_color = { 0, 128, 255, 255 };

    // Thank you Joey de Vries for this color :P
    // config.bg_color = { 50, 76, 76, 255 };
    // config.fullscreen = true;
    config.window_width = 1920;
    config.window_height = 1080;
    
    bool success;
    Diamond::Engine2D engine(config, success);
    
    if (success) {
        {
            bool play = true;

            while (play) {
                ParticleDemo demo(engine, 0.75, 0.25);
                engine.launch(demo);

                play = demo.willPlayAgain();
            }
        }

        /*{
            RandomDemo demo(engine);
            engine.launch(demo);
        }

        {
            CollideDemo demo(engine);
            engine.launch(demo);
        }*/
    }
    else {
        std::cout << "Diamond Engine failed to initialize!" << std::endl;
    }
    
	return 0;
}
