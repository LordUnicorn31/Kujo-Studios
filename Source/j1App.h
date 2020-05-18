#pragma once
#include "EASTL/list.h"
#include "EASTL/string.h"
#include "j1Module.h"
#include "j1Timer.h"
#include "j1PerfTimer.h"
#include "pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Scene;
class j1SceneLogo;
class j1SceneTitle;
class SceneTutorial;
class j1Map;
class j1Module;
class j1Audio;
class j1Map;
class j1Minimap;
class j1Fonts;
class j1Gui;
class j1Transitions;
class j1PathFinding;
class EntityManager;
class j1Collisions;
class j1WinScene;
class j1LoseScene;
class j1Particle;
//class DialogSystem;
class Fow;



class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;


	void LoadGame();
	void SaveGame() const;
	void GetSaveGames(eastl::list<eastl::string>& list_to_fill) const;
	bool freeze;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	// Modules
	j1Window* win;
	j1Render* render;
	j1Textures* tex;
	j1Scene* scene;
	j1SceneLogo* sceneLogo;
	j1SceneTitle* sceneTitle;
	SceneTutorial* sceneTutorial;
	j1Input* input;
	j1Audio* audio;
	j1Map* map;
	j1Minimap* minimap;
	j1Fonts* font;
	j1Gui* gui;
	j1Transitions* transition;
	j1PathFinding* pathfinding;
	EntityManager* entity;
	j1Collisions* collisions;
	j1WinScene* winscene;
	j1LoseScene* losescene;
	j1Particle* particle;
	//DialogSystem* dialog;
	Fow* fow;

	bool SavedProgress;

private:

	eastl::list<j1Module*>	modules;
	int					argc;
	char** args;

	eastl::string			title;
	eastl::string			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	eastl::string			load_game;
	mutable eastl::string	save_game;

	j1PerfTimer			ptimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float               dt = 0.0f;
	int					capped_ms = -1;
	bool                cap_num;
};

extern j1App* App;