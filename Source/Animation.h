#pragma once
#include "p2Defs.h"
#include "EASTL/string.h"
#include "EASTL/array.h"
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
	eastl::array<SDL_Rect, MAX_FRAMES>frames{};

private:
	float currentFrame=0.0f;
	int lastFrame = 0;
	int loops = 0;

public:

	void PushBack(const SDL_Rect& collider)
	{
		frames[lastFrame++] = collider;
	}

	SDL_Rect& GetCurrentFrame(float dt)
	{
		currentFrame += speed * dt;
		if (currentFrame >= lastFrame)
		{
			currentFrame = (loop) ? 0.0f : lastFrame - 1;
			loops++;
		}

		return frames[(int)currentFrame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		currentFrame = 0;
		loops = 0;
	}
};