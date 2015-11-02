/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLTexture.h"

Diamond::SDLTexture::SDLTexture(SDL_Texture *texture, int width, int height) : Texture(width, height), texture(texture) {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void Diamond::SDLTexture::set_color(Diamond::RGBA color) {
	Texture::set_color(color);
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);
}

Diamond::SDLTexture::~SDLTexture() {
	SDL_DestroyTexture(texture);
}
