#pragma once
#include "p2Defs.h"
#include "EASTL/string.h"
#include "SDL.h"

struct SDL_Rect;
struct SDL_Texture;

struct Frame {
	float duration;
	SDL_Rect rect;
};

struct Animation {
	eastl::string name;
	uint total_frames;
	uint current_frame;
	float current_frame_time = 0.0f;
	SDL_Texture* texture;
	Frame* frames;
	SDL_Rect& GetCurrentFrame(float dt = 1.0f);
	SDL_Rect& DoOneLoop(float dt = 1.0f);
};