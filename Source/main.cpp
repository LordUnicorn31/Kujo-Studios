#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_Mixer.h>
#include <SDL_ttf.h>
#include "pugixml.hpp"

int main(int argc, char* args[]) {
	pugi::xml_document Entity_doc;
	SDL_Init(SDL_INIT_EVERYTHING);
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		// handle error
	}
	// load sample.png into image
	SDL_Surface* image;
	image = IMG_Load("Resources/maps/isometric_grass_and_water.png");
	if (!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}
	// Test sample.png to see if it is a PNG
	SDL_RWops* rwop;
	rwop = SDL_RWFromFile("Resources/maps/isometric_grass_and_water.png", "rb");
	if (IMG_isPNG(rwop))
		printf("sample.png is a PNG file.\n");
	else
		printf("sample.png is not a PNG file, or PNG support is not available.\n");

	flags = MIX_INIT_OGG | MIX_INIT_MOD;
	initted = Mix_Init(flags);
	if ((initted & flags) != flags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		// handle error
	}
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	SDL_Quit();
	return 0;
}