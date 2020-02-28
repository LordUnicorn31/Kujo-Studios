#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_Mixer.h>
#include <SDL_ttf.h>
#include "pugixml.hpp"

int main(int argc, char* args[]) {
	pugi::xml_document Entity_doc;
	SDL_Init(SDL_INIT_EVERYTHING);
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		// handle error
	}
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