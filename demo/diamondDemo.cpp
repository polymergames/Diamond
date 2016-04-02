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
#include "RandomDemo.h"

int main(int argc, char *argv[]) {
    Diamond::Config config;
    Diamond::Engine2D engine;
	CollideDemo demo;
    
    config.vsync = true;
    config.bg_color = { 0, 128, 255, 255 };
    
    if (engine.init(config)) {
        engine.launch(demo);
    }
    
	return 0;
}
