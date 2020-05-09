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
#include "j1LoseScene.h"

j1LoseScene::j1LoseScene() : j1Module()
{
	name = "loseScene";
}

// Destructor
j1LoseScene::~j1LoseScene()
{
}


// Called before render is available
bool j1LoseScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1LoseScene::Start()
{

	background = App->tex->Load("Resources/Title_menu/Fondo.png");
	losetext = App->tex->Load("Resources/Lose_screen/lose_screen.png");
	App->audio->PlayMusic("Resources/Lose_screen/Epic Fall.ogg");
	return true;
}

// Called each loop iteration
bool j1LoseScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1LoseScene::Update(float dt)
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

	App->render->Blit(background, 0, 0, NULL, true, App->render->renderer, 1.5);
	App->render->Blit(losetext, w * 1.55f, h, NULL, true, App->render->renderer, 0.2);

	//Need to create a timer
	/*if (App->input->GetKey(SDL_SCANCODE_RETURN)) {
		App->transition->FadeToBlack(App->sceneTitle, App->scene, 2.0f);
	}*/

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
bool j1LoseScene::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool j1LoseScene::CleanUp()
{
	LOG("Freeing scene");

	App->tex->UnLoad(background);
	App->tex->UnLoad(losetext);
	/*App->audio->CleanUp();*/


	return true;
}

void j1LoseScene::Init()
{
	enabled = false;

	active = true;
}

