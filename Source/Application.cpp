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
#include "SceneTitle.h"
#include "SceneTutorial.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "Audio.h"
#include "Minimap.h"
#include "Fonts.h"
#include "Gui.h"
#include "Transitions.h"
#include "Pathfinding.h"
#include "EntityManager.h"
#include "Collisions.h"
#include "WinScene.h"
#include "LoseScene.h"
#include "Particles.h"
//#include "DialogSystem.h"
#include "Fow.h"

#include "SDL.h"

Application::Application(int argc, char* args[]) : argc(argc), args(args),save_game("Resources/save.xml"),load_game("Resources/save.xml")
{
	PERF_START(ptimer);
	freeze = false;
	want_to_save = want_to_load = false;

	input = new Input();
	win = new Window();
	render = new Render();
	tex = new Textures();
	particle = new Particles();
	sceneLogo = new SceneLogo();
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
	//dialog = new DialogSystem();
	fow = new Fow();
	

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp

	AddModule(audio);
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(scene);
	AddModule(sceneTitle);
	AddModule(sceneLogo);
	AddModule(sceneTutorial);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(entity);
	AddModule(collisions);
	AddModule(minimap);
	AddModule(font);
	AddModule(winscene);
	AddModule(losescene);
	AddModule(gui);
	AddModule(transition);
	
	AddModule(particle);
	//AddModule(dialog);
	AddModule(fow);
	

	// render last to swap buffer
	AddModule(render);

	/*modules.reserve(6);
	modules.emplace_back(input);
	modules[0]->Init();
	modules.emplace_back(win);
	modules[1]->Init();
	modules.emplace_back(tex);
	modules[2]->Init();
	modules.emplace_back(scene);
	modules[3]->Init();
	modules.emplace_back(map);
	modules[4]->Init();
	modules.emplace_back(render);
	modules[5]->Init();*/

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
		SavedProgress = config.child("SavedProgress").child_value();
		int cap = app_config.attribute("framerate_cap").as_int(-1);
		cap_num = cap;

		if (cap > 0)
		{
			capped_ms = 1000 / cap;
		}
	}

	if (ret == true)
	{
		/*item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}*/
		
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
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	if (freeze)
		dt = 0;
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{

	if (want_to_save == true)
		SavegameNow();

	if (want_to_load == true)
		LoadGameNow();

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	static char title[256];
	sprintf_s(title, 256, "FPS: %i Av.FPS: %.2f Last Frame Ms: %u Cap: %d VSync: %d",
		frames_on_last_update, avg_fps, last_frame_ms, cap_num, App->render->VSync);
	App->win->SetTitle(title);

	if (capped_ms > 0 && last_frame_ms < capped_ms)
	{
		SDL_Delay(capped_ms - last_frame_ms);
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
	/*p2List_item<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false || !pModule->IsEneabled()) {
			continue;
		}

		ret = item->data->Update(dt);
	}*/

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

	if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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
	want_to_load = true;
}

// ---------------------------------------
void Application::SaveGame() const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
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

	pugi::xml_parse_result result = data.load_file(load_game.c_str());

	if (result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.c_str());

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
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.c_str(), result.description());

	want_to_load = false;
	return ret;
}

bool Application::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.c_str());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;

	root = data.append_child("game_state");

	/*p2List_item<Module*>* item = modules.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->Save(root.append_child(item->data->name.GetString()));
		item = item->next;
	}*/

	eastl::list<Module*>::const_iterator it;
	for (it = modules.begin(); it != modules.end() && ret == true; ++it) {
		pugi::xml_node ModuleNode = root.append_child((*it)->name.c_str());
		ret = (*it)->Save(ModuleNode);
	}

	if (ret == true)
	{
		data.save_file(save_game.c_str());
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (it.mpNode->mValue != NULL) ? (*it)->name.c_str() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}