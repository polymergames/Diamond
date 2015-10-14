/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLTexture.h"

Diamond::SDLTexture::SDLTexture(SDL_Texture *texture, int width, int height) : Texture(width, height), texture(texture) {}

Diamond::SDLTexture::~SDLTexture() {
	SDL_DestroyTexture(texture);
}
