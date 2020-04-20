#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Minimap.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Gui.h"

j1Scene::j1Scene() : j1Module()
{	
}

// Destructor
j1Scene::~j1Scene()
{
}


// Called before render is available
bool j1Scene::Awake(pugi::xml_node&config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Mainmap.tmx");
	App->minimap->Enable();
	App->entity->Enable();
	App->audio->PlayMusic("Resources/audio/music/Space.ogg");
	Pause = App->gui->AddButton(1200, 10, { 755, 527, 39,39 }, { 871, 736, 39,39 }, { 755, 527, 39,39 }, true, false, nullptr, this);
	Info = App->gui->AddButton(750, 10, { 494,640,332,52 }, { 494,574,332,52 }, { 494,640,332,52 }, true, false, nullptr, this);
	People = App->gui->AddImage(780, 15, { 591,494,40,37 }, false, false, nullptr, this);
	Copper = App->gui->AddImage(880, 22, { 679,501,28,29 }, false, false, nullptr, this);
	Titanium = App->gui->AddImage(980, 22, { 641,498,30,31 }, false, false, nullptr, this);
	//Unit1 = App->gui->AddButton(227, 650, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
		App->render->camera.x+=5;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
		App->render->camera.x-=5;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		App->render->camera.y+=5;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		App->render->camera.y-=5;
	}

	App->map->Draw();
	return ret;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	App->map->CleanUp();
	App->gui->DeleteAllUiElements();
	Pause = nullptr;
	Info = nullptr;
	People = nullptr;
	Copper = nullptr;
	Titanium = nullptr;

	return true;
}

void j1Scene::Init()
{
	enabled = false;

	active = true;
}

void j1Scene::ui_callback(UiElement* element) {
	if (element == Pause) {
		App->audio->PlayFx(App->audio->LoadFx("Resources/audio/fx/beep.wav"));
		App->freeze = !App->freeze;
	}
}