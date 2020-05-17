#include "p2Defs.h"
#include "p2Log.h"
#include "j1Audio.h"
#include "j1App.h"

#include "SDL.h"
#include "SDL_mixer.h"



j1Audio::j1Audio() : j1Module()
{
	music = NULL;
	name = "audio";

	currentMusicVolume = MIX_MAX_VOLUME;
	currentFxVolume = MIX_MAX_VOLUME;
}

// Destructor
j1Audio::~j1Audio()
{}

// Called before render is available
bool j1Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the OGG and Audio formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	return ret;
}

// Called before quitting
bool j1Audio::CleanUp()
{
	if (!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	eastl::list<Mix_Chunk*> ::iterator it;
	for (it = fx.begin(); it != fx.end(); ++it)
		Mix_FreeChunk(*it);

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool j1Audio::PlayMusic(const char* path, float fade_time)
{

	bool ret = true;

	if (!active)
		return false;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
			
		}

		LOG("Successfully playing %s", path);
	}


	return ret;
}


// Load WAV
unsigned int j1Audio::LoadFx(const char* path)
{

	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	
	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		Mix_VolumeChunk(chunk, 100);  //Change the 100 for a fxVolume
		fx.push_back(chunk);
		ret = fx.size();
	}

	LOG("Load wav %s", path);
	return ret;
}

// Play WAV
bool j1Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	if (id > 0 && id <= fx.size())
	{
		eastl::list<Mix_Chunk*> ::iterator it;
		it = eastl::next(fx.begin(), id - 1);
		Mix_PlayChannel(-1, *it, repeat);
	}

	return ret;
}

void j1Audio::MusicVolume(float vol)
{
	if (vol > MIX_MAX_VOLUME)
		vol = MIX_MAX_VOLUME;

	else if (vol < -MIX_MAX_VOLUME)
		vol = -MIX_MAX_VOLUME;

	Mix_VolumeMusic(vol);
	currentMusicVolume = vol;
}

void j1Audio::FxVolume(float vol)
{
	if (vol > MIX_MAX_VOLUME)
		vol = MIX_MAX_VOLUME;

	eastl::list<Mix_Chunk*>::iterator it;
	for (it = fx.begin(); it != fx.end(); ++it)
	{
		Mix_VolumeChunk(*it, vol);
	}
	currentFxVolume = vol;
}

float j1Audio::GetMusicVolume()
{
	return currentMusicVolume;
}

float j1Audio::GetFxVolume()
{
	return currentFxVolume;
}

void j1Audio::UnloadFx() 
{
	eastl::list<Mix_Chunk*>::iterator it;
	for (it = fx.begin(); it != fx.end(); ++it)
	{
		Mix_FreeChunk(*it);
	}
	fx.clear();
}

void j1Audio::UnloadMusic(float fade_time)
{
	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(music);
	}

	music = NULL;
}