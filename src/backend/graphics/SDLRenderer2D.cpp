/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer2D.h"
#include <iostream>
#include "Launcher.h"
#include "SDL_image.h"
#include "SDLInput.h"
#include "SDLTexture.h"

int Diamond::SDLRenderer2D::reserve_size = 10;

Diamond::SDLRenderer2D::SDLRenderer2D() : window(nullptr), renderer(nullptr) {
	render_objects.reserve(reserve_size);
    inactive_render_objects.reserve(reserve_size);
}

bool Diamond::SDLRenderer2D::init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure and log
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create window
    window = SDL_CreateWindow(Launcher::config.game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              Launcher::config.window_width, Launcher::config.window_height, Launcher::config.window_width <= 0
                              || Launcher::config.window_height <= 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	if (window == nullptr) {
		// TODO: Handle window creation failure and log
		std::cout << "SDL failed to create window! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | (Launcher::config.vsync ? SDL_RENDERER_PRESENTVSYNC : 0x00000000));
	if (renderer == nullptr) {
		// TODO: Handle renderer creation failure and log
		std::cout << "SDL failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialize image loading
	int img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if (IMG_Init(img_flags) != img_flags) {
		// TODO: Handle image-loader initialization failure and log
		std::cout << "SDL_image failed to initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	return true;
}

void Diamond::SDLRenderer2D::render() {
	// Handle SDL events
	Input::reset();
	while (SDL_PollEvent(&e)) {
        SDLInput::handle(e);
	}

	// Render all the graphics
	SDL_SetRenderDrawColor(renderer, Launcher::config.bg_color.r, Launcher::config.bg_color.g, Launcher::config.bg_color.b, Launcher::config.bg_color.a); // reset color
    SDL_RenderClear(renderer);
    for (std::vector<SDLRenderObj2D>::iterator i = render_objects.begin(); i != render_objects.end(); i++) {
        //std::cout << i->transform.position.x << " and " << i->transform.position.y << " and " << i->transform.scale << std::endl; // DEBUG
        i->render(renderer);
    }

	// Update screen
    SDL_RenderPresent(renderer);
}

Diamond::Texture *Diamond::SDLRenderer2D::load_texture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        // TODO: Handle image loading failure and log
        std::cout << "Failed to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        // TODO: Handle texture creation failure and log
        std::cout << "Failed to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    int width = surface->w;
    int height = surface->h;
    
    SDL_FreeSurface(surface);
    return new SDLTexture(texture, width, height);
}

void Diamond::SDLRenderer2D::gen_render_obj(GameObject2D *parent, Texture *texture) {
	unsigned long size = render_objects.size();
	if (size == render_objects.capacity()) {
		// Reallocate render_objects vector then loop through and reset their parents' references
		// This is done to maintain integrity of render pointers
		render_objects.reserve(size + reserve_size);
		for (std::vector<SDLRenderObj2D>::iterator i = render_objects.begin(); i != render_objects.end(); i++) {
			i->arm_parent();
		}
	}
	render_objects.push_back(SDLRenderObj2D(parent, texture));
    render_objects[size].arm_parent();
	render_objects[size].index = size;
}

void Diamond::SDLRenderer2D::activate_render_obj(unsigned long index) {
    unsigned long size = render_objects.size();
    if (size == render_objects.capacity()) {
        render_objects.reserve(size + reserve_size);
        for (std::vector<SDLRenderObj2D>::iterator i = render_objects.begin(); i != render_objects.end(); i++) {
            i->arm_parent();
        }
    }
    render_objects.push_back(inactive_render_objects[index]);
    render_objects[size].arm_parent();
    render_objects[size].index = size;
}

void Diamond::SDLRenderer2D::deactivate_render_obj(unsigned long index) {
    unsigned long size = inactive_render_objects.size();
    if (size == inactive_render_objects.capacity()) {
        inactive_render_objects.reserve(size + reserve_size);
        for (std::vector<SDLRenderObj2D>::iterator i = inactive_render_objects.begin(); i != inactive_render_objects.end(); i++) {
            i->arm_parent();
        }
    }
    inactive_render_objects.push_back(render_objects[index]);
    destroy_render_obj(index);
    inactive_render_objects.back().arm_parent();
    inactive_render_objects.back().index = inactive_render_objects.size() - 1;
}

void Diamond::SDLRenderer2D::destroy_render_obj(unsigned long index) {
	if (index < render_objects.size() - 1) { // If in middle of vector, replace it with the last render object in vector
		render_objects[index] = render_objects.back();
		render_objects[index].arm_parent();
		render_objects[index].index = index;
	}
	render_objects.pop_back();
}

Diamond::SDLRenderer2D::~SDLRenderer2D() {
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    IMG_Quit();
	SDL_Quit();
}
