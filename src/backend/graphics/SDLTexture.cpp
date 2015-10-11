/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLTexture.h"

Diamond::SDLTexture::SDLTexture() : texture(nullptr) {}

Diamond::SDLTexture::SDLTexture(SDL_Texture *texture) : texture(texture) {}

Diamond::SDLTexture::~SDLTexture() {
	SDL_DestroyTexture(texture);
}
