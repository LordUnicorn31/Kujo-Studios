#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <math.h>
#include "j1App.h"
#include "j1Transitions.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SDL_render.h"
#include "SDL_timer.h"

j1Transitions::j1Transitions() : j1Module()
{
	name = "transitions";
}

j1Transitions::~j1Transitions()
{}

// Load assets
bool j1Transitions::Start()
{
	screen = { 0, 0, App->win->width * App->win->scale, App->win->height * App->win->scale };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool j1Transitions::Update(float dt)
{
	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			Moduleoff->Disable();
			Moduleon->Enable();
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{

		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;

	} break;

	case fade_step::slide_in:

		normalized = 1.0f;
		if (screen.x >= 0)
			screen.x = 0;
		else
			screen.x += (int)(((float)(screen.w) / (float)total_time)* dt * (float)now * 2);

		if (now >= total_time)
		{
			current_step = fade_step::slide_change;
		}

		break;

	case fade_step::slide_change:

		normalized = 1.0f;
		screen.x;
		Moduleoff->Disable();
		Moduleon->Enable();
		total_time += total_time;
		start_time = SDL_GetTicks();
		current_step = fade_step::slide_out;

		break;

	case fade_step::slide_out:

		normalized = 1.0f;
		screen.x += (int)(((float)(screen.w) / (float)total_time) * dt * (float)now * 2);
		if (now >= total_time) {
			current_step = fade_step::none;
		}
			
		break;
	}

	SDL_SetRenderDrawColor(App->render->renderer, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one j1Module, then activate the other
bool j1Transitions::FadeToBlack(j1Module* j1Module_off, j1Module* j1Module_on, float time)
{
	bool ret = false;
	if (current_step == fade_step::none)
	{
		screen.x = 0;
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		Moduleoff = j1Module_off;
		Moduleon = j1Module_on;
		ret = true;
	}

	return ret;
}

bool j1Transitions::Slide(j1Module* j1Module_off, j1Module* j1Module_on, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		screen.x -= App->win->width;
		current_step = fade_step::slide_in;
		start_time = SDL_GetTicks();
		total_time = (Uint32) (time *0.5* 1000.0f);
		Moduleoff = j1Module_off;
		Moduleon = j1Module_on;
		ret = true;
	}
	return ret;
}



bool j1Transitions::IsFading() const
{
	return current_step != fade_step::none;
}

bool j1Transitions::CleanUp() {
	return true;
}
