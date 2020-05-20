#ifndef __TRANSITIONS_H__
#define __TRANSITIONS_H__

#include "Module.h"
#include "SDL_rect.h"


class Transitions : public Module
{
public:


	Transitions();

	virtual ~Transitions();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	bool FadeToBlack(Module* Module_off, Module* Module_on, float time = 2.0f);
	bool Slide(Module* Module_off, Module* Module_on, float time = 2.0f);
	bool IsFading() const;


private:

	Module* Moduleoff;
	Module* Moduleon;


	enum class fade_step
	{
		none,
		fade_to_black,
		fade_from_black,
		slide_in,
		slide_change,
		slide_out
	}
	current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;

};

#endif //__TRANSITIONS_H__