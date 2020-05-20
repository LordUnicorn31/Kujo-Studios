#pragma once
#include "EASTL/list.h"
#include "EASTL/string.h"
#include "Module.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class GameScene;
class SceneLogo;
class SceneTitle;
class SceneTutorial;
class Map;
class Module;
class Audio;
class Map;
class Minimap;
class Fonts;
class Gui;
class Transitions;
class PathFinding;
class EntityManager;
class Collisions;
class WinScene;
class LoseScene;
class Particles;
//class DialogSystem;
class Fow;




class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

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
	Window* win;
	Render* render;
	Textures* tex;
	GameScene* scene;
	SceneLogo* sceneLogo;
	SceneTitle* sceneTitle;
	SceneTutorial* sceneTutorial;
	Input* input;
	Audio* audio;
	Map* map;
	Minimap* minimap;
	Fonts* font;
	Gui* gui;
	Transitions* transition;
	PathFinding* pathfinding;
	EntityManager* entity;
	Collisions* collisions;
	WinScene* winscene;
	LoseScene* losescene;
	Particles* particle;
	//DialogSystem* dialog;
	Fow* fow;
	

	bool SavedProgress;

private:

	eastl::list<Module*>	modules;
	int					argc;
	char** args;

	eastl::string			title;
	eastl::string			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	eastl::string			load_game;
	mutable eastl::string	save_game;

	PerfTimer			ptimer;
	uint64				frame_count = 0;
	Timer				startup_time;
	Timer				frame_time;
	Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float               dt = 0.0f;
	int					capped_ms = -1;
	bool                cap_num;
};

extern App* App;