#include "p2Defs.h"
#include "p2Log.h"

#include "Application.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "GameScene.h"
#include "SceneLogo.h"
#include "SceneIntro.h"
#include "SceneTitle.h"
#include "SceneTutorial.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "Audio.h"
#include "Minimap.h"
#include "Fonts.h"
#include "Gui.h"
#include "Transitions.h"
#include "PathFinding.h"
#include "EntityManager.h"
#include "Collisions.h"
#include "WinScene.h"
#include "LoseScene.h"
#include "Particles.h"
#include "DialogSystem.h"
#include "QuestManager.h"
#include "Fow.h"
#include "Enemies.h"

#include "SDL.h"

Application::Application(int argc, char* args[]) : argc(argc), args(args), saveGame("Resources/save.xml"), loadGame("Resources/save.xml")
{
	PERF_START(ptimer);
	freeze = false;
	wantToSave = wantToLoad = false;

	input = new Input();
	win = new Window();
	render = new Render();
	tex = new Textures();
	particle = new Particles();
	quest = new QuestManager();
	sceneLogo = new SceneLogo();
	sceneIntro = new SceneIntro();
	sceneTitle = new SceneTitle();
	sceneTutorial = new SceneTutorial();
	scene = new GameScene();
	audio = new Audio();
	map = new Map();
	pathfinding = new PathFinding();
	minimap = new Minimap();
	font = new Fonts();
	gui = new Gui();
	transition = new Transitions();
	entity = new EntityManager();
	collisions = new Collisions();
	winscene = new WinScene();
	losescene = new LoseScene();
	dialog = new DialogTree();
	fow = new Fow();
	enemies = new Enemies();
	

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp

	AddModule(audio);
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(scene);
	AddModule(sceneTitle);
	AddModule(sceneIntro);
	AddModule(sceneLogo);
	AddModule(sceneTutorial);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(entity);
	AddModule(enemies);
	AddModule(collisions);
	AddModule(minimap);
	AddModule(font);
	AddModule(winscene);
	AddModule(losescene);
	AddModule(particle);
	AddModule(gui);
	AddModule(transition);
	AddModule(dialog);
	AddModule(quest);
	AddModule(fow);
	

	// render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
Application::~Application()
{
	// release modules
	eastl::list <Module*> ::reverse_iterator it;
	for (it = modules.rbegin(); it != modules.rend(); it++) 
	{
		RELEASE(*it);
	}
	modules.clear();
}

void Application::AddModule(Module* module)
{
	module->Init();
	bool a=modules.empty();
	modules.push_back(module);
}

// Called before render is available
bool Application::Awake()
{
	PERF_START(ptimer);
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;

	config = LoadConfig(config_file);

	if (config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title=app_config.child("title").child_value();
		organization=app_config.child("organization").child_value();
		savedProgress = config.child("SavedProgress").child_value();
		int cap = app_config.attribute("framerate_cap").as_int(-1);
		capNum = cap;

		if (cap > 0)
		{
			cappedMs = 1000 / cap;
		}
	}

	if (ret == true)
	{
		
		eastl::list <Module*> ::iterator it;
		for (it = modules.begin(); it != modules.end() && ret == true; ++it) 
		{
			pugi::xml_node config2 = config.child((*it)->name.c_str());
			ret = (*it)->Awake(config2);
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool Application::Start()
{
	PERF_START(ptimer);
	bool ret = true;

	eastl::list <Module*> ::iterator it;
	for (it = modules.begin(); it != modules.end() && ret == true; ++it)
	{
		if ((*it)->IsEneabled())
			ret = (*it)->Start();
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration

bool Application::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node Application::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("Resources/config.xml");

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;

	dt = frameTime.ReadSec();
	if (freeze)
		dt = 0;
	frameTime.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{

	if (wantToSave == true)
		SavegameNow();

	if (wantToLoad == true)
		LoadGameNow();

	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	float avg_fps = float(frameCount) / startupTime.ReadSec();
	float seconds_since_startup = startupTime.ReadSec();
	uint32 last_frame_ms = frameTime.Read();
	uint32 frames_on_last_update = prevLastSecFrameCount;

	static char title[256];
	sprintf_s(title, 256, "FPS: %i Av.FPS: %.2f Last Frame Ms: %u Cap: %d VSync: %d",
		frames_on_last_update, avg_fps, last_frame_ms, capNum, App->render->vSync);
	App->win->SetTitle(title);

	if (cappedMs > 0 && last_frame_ms < cappedMs)
	{
		SDL_Delay(cappedMs - last_frame_ms);
	}
}

// Call modules before each loop iteration
bool Application::PreUpdate()
{
	bool ret = true;

	eastl::list <Module*> ::iterator it;
	for (it = modules.begin(); it != modules.end() && ret == true; ++it)
	{
		if ((*it)->active == false || !(*it)->IsEneabled())
			continue;
		ret = (*it)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool Application::DoUpdate()
{
	bool ret = true;

	eastl::list <Module*> ::iterator it;
	for (it = modules.begin(); it != modules.end() && ret == true; ++it)
	{
		if ((*it)->active == false || !(*it)->IsEneabled())
			continue;
		ret = (*it)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool Application::PostUpdate()
{
	bool ret = true;

	eastl::list <Module*> ::iterator it;
	for (it = modules.begin(); it != modules.end() && ret == true; ++it)
	{
		if ((*it)->active == false || !(*it)->IsEneabled())
			continue;
		ret = (*it)->PostUpdate();
	}

	//Exit with ESCAPE
	/*if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/

	return ret;
}

// Called before quitting
bool Application::CleanUp()
{
	PERF_START(ptimer);
	bool ret = true;

	eastl::list<Module*>::reverse_iterator it;
	for (it= modules.rbegin(); it != modules.rend(); it++)
	{
		if ((*it)->IsEneabled())
			ret = (*it)->CleanUp();
	}

	PERF_PEEK(ptimer);

	return ret;
}

// ---------------------------------------
int Application::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* Application::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* Application::GetTitle() const
{
	return title.c_str();
}

// ---------------------------------------
const char* Application::GetOrganization() const
{
	return organization.c_str();
}

// ---------------------------------------
float Application::GetDT() const
{
	return dt;
}

// Load / Save
void Application::LoadGame()
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	wantToLoad = true;
}

// ---------------------------------------
void Application::SaveGame() const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	wantToSave = true;
}

// ---------------------------------------
void Application::GetSaveGames(eastl::list<eastl::string>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

bool Application::LoadGameNow()
{
	bool ret = true;

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(loadGame.c_str());

	if (result != NULL)
	{
		LOG("Loading new Game State from %s...", loadGame.c_str());

		root = data.child("game_state");

		eastl::list<Module*>::iterator it;
		for (it = modules.begin(); it != modules.end() && ret == true; ++it) {
			pugi::xml_node ModuleNode = root.child((*it)->name.c_str());
			ret = (*it)->Load(ModuleNode);
		}

		data.reset();
		if (ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", ((*it) != NULL) ? (*it)->name.c_str() : "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", loadGame.c_str(), result.description());

	wantToLoad = false;
	return ret;
}

bool Application::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", saveGame.c_str());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;

	root = data.append_child("game_state");

	eastl::list<Module*>::const_iterator it;
	for (it = modules.begin(); it != modules.end() && ret == true; ++it) {
		pugi::xml_node ModuleNode = root.append_child((*it)->name.c_str());
		ret = (*it)->Save(ModuleNode);
	}

	if (ret == true)
	{
		data.save_file(saveGame.c_str());
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (it.mpNode->mValue != NULL) ? (*it)->name.c_str() : "unknown");

	data.reset();
	wantToSave = false;
	return ret;
}