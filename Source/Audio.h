#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"
#include "SDL_mixer.h"
#include "EASTL/list.h"



#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{

public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	//Music Volume Control
	void MusicVolume(int vol);

	//FX Volume Control
	void FxVolume(int vol);

	int GetMusicVolume() const;
	int GetFxVolume() const;

	//Unload FX 
	void UnloadFx();

	//Unload Music 
	void UnloadMusic();

private:

	Mix_Music* music = NULL;
	eastl::list<Mix_Chunk*>	fx;

	int currentMusicVolume;
	int currentFxVolume;


};

#endif // __AUDIO_H__