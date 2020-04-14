#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1SceneTitle.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Minimap.h"
#include "j1Transitions.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Audio.h"

j1SceneTitle::j1SceneTitle() : j1Module()
{
}

// Destructor
j1SceneTitle::~j1SceneTitle()
{
}


// Called before render is available
bool j1SceneTitle::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1SceneTitle::Start()
{
	Exit = false;
	background = App->tex->Load("Resources/Title_menu/Fondo.png");
	titleLogo = App->tex->Load("Resources/Title_menu/LOGOJUEGO.png");
	Play_button = App->gui->AddButton(500, 430, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
	App->gui->AddText(68, 16, "PLAY", nullptr, { 0,0,255,255 }, 42, false, false, Play_button);
	Exit_button = App->gui->AddButton(500, 530, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
	App->gui->AddText(75, 16, "EXIT", nullptr, { 0,0,255,255 }, 42, false, false, Exit_button);
	App->audio->PlayMusic("Resources/audio/Mindustry/music/menu.ogg");
	return true;
}

// Called each loop iteration
bool j1SceneTitle::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1SceneTitle::Update(float dt)
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
		App->render->camera.x += 5;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
		App->render->camera.x -= 5;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		App->render->camera.y += 5;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		App->render->camera.y -= 5;
	}

	
	int w = App->win->GetWidth();
	int h = App->win->GetHeight();

	App->render->Blit(background, 0, 0, NULL,true, App->render->renderer, 1.5);
	App->render->Blit(titleLogo, w*1.55f, h, NULL, true, App->render->renderer, 0.2);

	//Need to create a timer
	/*if (App->input->GetKey(SDL_SCANCODE_RETURN)) {
		App->transition->FadeToBlack(App->sceneTitle, App->scene, 2.0f);
	}*/
	if (Exit) {
		ret = false;
		Exit = false;
	}
	
	/*
	//INTRO KEY
	if (App->input->GetKey(SDL_SCANCODE_RETURN)) {
		Disable();
		App->scene->Enable();
	}
	*/

	return ret;
}

// Called each loop iteration
bool j1SceneTitle::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool j1SceneTitle::CleanUp()
{
	LOG("Freeing scene");

	App->tex->UnLoad(background);
	App->tex->UnLoad(titleLogo);
	App->gui->DeleteAllUiElements();
	Play_button = nullptr;
	Exit_button = nullptr;
	
	return true;
}

void j1SceneTitle::Init()
{
	enabled = true;
	
	active = true;
}

void j1SceneTitle::ui_callback(UiElement* element) {
	if (element == Play_button) {
		//App->transition->FadeToBlack(App->sceneTitle, App->scene, 2.0f);
		App->transition->Slide(App->sceneTitle, App->scene, 2.0f);
	}
	if (element == Exit_button) {
		Exit = true;
	}
}