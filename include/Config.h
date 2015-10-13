/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Diamond {
    struct RGBA {
        int r, g, b, a;
    };
    
    struct Config {
        std::string game_name = "A Game Without a Name";
        int window_width = 1280;
        int window_height = 720;
        struct RGBA bg_color = RGBA{0, 0, 0, 100};
    };
}

#endif // CONFIG_H
