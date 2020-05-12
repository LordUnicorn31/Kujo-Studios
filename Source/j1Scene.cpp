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
#include "j1SceneTitle.h"
#include "j1Fonts.h"
#include "j1Transitions.h"
#include "j1Transitions.h"
#include "j1WinScene.h"
#include "j1LoseScene.h"
#include "j1Collisions.h"


j1Scene::j1Scene() : j1Module()
{	
	name = "scene";
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
	App->minimap->Enable();
	App->entity->Enable();
	App->collisions->Enable();
	App->audio->PlayMusic("Resources/audio/music/Space.ogg");
	Pause = App->gui->AddButton(1200, 10, { 755, 527, 39,39 }, { 871, 736, 39,39 }, { 755, 527, 39,39 }, true, false, nullptr, this);
	Info = App->gui->AddButton(750, 10, { 494,640,332,52 }, { 494,574,332,52 }, { 494,640,332,52 }, true, false, nullptr, this);
	People = App->gui->AddImage(780, 15, { 591,494,40,37 }, false, false, nullptr, this);
	Copper = App->gui->AddImage(880, 22, { 679,501,28,29 }, false, false, nullptr, this);
	Titanium = App->gui->AddImage(980, 22, { 641,498,30,31 }, false, false, nullptr, this);
	//Unit1 = App->gui->AddButton(0, 600, { 32,544,430,208}, { 32,544,440,208 }, { 32,544,440,208 }, true, false, nullptr, this);

	Panel = App->gui->AddImage(0, 0, { 1024,0,226,720 }, false, false, nullptr, this);
	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");

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
	if (App->input->GetKey(SDL_SCANCODE_L)) {
		App->transition->FadeToBlack(App->scene, App->winscene, 2.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_M)) {
		App->transition->FadeToBlack(App->scene, App->losescene, 2.0f);
	}
	
	

	if (exitGame) {
		ret = false;
		exitGame = false;
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
		if (Pause != nullptr) {
			if (Settings_window == nullptr) {
				Settings_window = App->gui->AddImage(400, 150, { 0, 512, 483, 512 }, false, false);
				App->gui->AddText(170, 50, "PAUSE", NULL, { 0,0,255,255 }, 42, false, false, Settings_window);
				Exit_button = App->gui->AddButton(120, 370, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(78, 16, "EXIT", NULL, { 0,0,255,255 }, 42, false, false, Exit_button);
				Continue_button = App->gui->AddButton(120, 110, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(23, 15, "CONTINUE", NULL, { 0,0,255,255 }, 36, false, false, Continue_button);
				fullScreen = App->gui->AddButton(120, 280, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(55, 25, "FULLSCREEN", App->font->Small, { 255,255,255 }, 42, false, false, fullScreen);
				SaveButton = App->gui->AddButton(120, 190, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(63, 16, "SAVE", NULL, { 0,0,255,255 }, 42, false, false, SaveButton);
				App->freeze = true;
			}
			else {
				App->freeze = false;
				App->gui->RemoveUiElement(Settings_window);
				Settings_window = nullptr;
			}
		}
	}
	if (element == Exit_button) {
		exitGame = true;
	}
	if (element == Continue_button) {
		App->freeze = false;
		if (Settings_window != nullptr) {
			App->gui->RemoveUiElement(Settings_window);
			Settings_window = nullptr;
		}
	}
	if (element == fullScreen) {

		App->win->Fullscreen();
	}
	if (element == SaveButton) {
		App->SaveGame();
	}
}