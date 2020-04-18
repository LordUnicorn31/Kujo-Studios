#pragma once
#include "p2Defs.h"
#include "EASTL/string.h"
#include "SDL.h"
#define MAX_FRAMES 60

/*
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
*/

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame;
	int last_frame = 0;
	int loops = 0;

public:

	void PushBack(const SDL_Rect& collider)
	{
		frames[last_frame++] = collider;
	}

	SDL_Rect& GetCurrentFrame(float dt)
	{
		current_frame += speed * dt;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			loops++;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
		loops = 0;
	}
};