/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLTexture.h"

Diamond::SDLTexture::SDLTexture(SDL_Texture *texture, int width, int height) : Texture(width, height), texture(texture) {}

void Diamond::SDLTexture::set_color(Diamond::RGB color) {
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

Diamond::SDLTexture::~SDLTexture() {
	SDL_DestroyTexture(texture);
}
