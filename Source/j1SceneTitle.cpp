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
#include "j1Pathfinding.h"

j1SceneTitle::j1SceneTitle() : j1Module()
{
	name = "sceneTitle";
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
	titleLogo = App->tex->Load("Resources/Title_menu/LOGONEW.png");


	NewGameButton = App->gui->AddButton(500, 390, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
	App->gui->AddText(15, 16, "NEW GAME", nullptr, { 0,255,0,255 }, 42, false, false, NewGameButton);
	ContinueButton = App->gui->AddButton(500, 470, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
	App->gui->AddText(20, 16, "CONTINUE", nullptr, { 0,255,0,255 }, 42, false, false, ContinueButton);
	exitButton = App->gui->AddButton(500, 630, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
	App->gui->AddText(75, 16, "EXIT", nullptr, { 255,0,0,255 }, 42, false, false, exitButton);
	optionsButton = App->gui->AddButton(500, 550, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
	App->gui->AddText(32, 16, "OPTIONS", nullptr, { 0, 255, 255 }, 42, false, false, optionsButton);
	App->gui->AddText(10, 690, "2020 KUJO STUDIOS", App->font->Small, { 255,255,255 }, 42, false, false);
	

	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");

	App->audio->PlayMusic("Resources/audio/music/ObservingTheStar.ogg");
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
	
	int w = App->win->GetWidth();
	int h = App->win->GetHeight();

	App->render->Blit(background, 0, 0, NULL,true, App->render->renderer, 1.5);
	App->render->Blit(titleLogo, w*1.6f, h*0.6f, NULL, true, App->render->renderer, 0.2);

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
	/*App->audio->CleanUp();*/
	NewGameButton = nullptr;
	ContinueButton = nullptr;
	exitButton = nullptr;
	
	return true;
}

void j1SceneTitle::Init()
{
	enabled = false;
	
	active = true;
}

void j1SceneTitle::ui_callback(UiElement* element) {
	if (element == NewGameButton) {	
		App->audio->PlayFx(buttonFx);
		App->map->Load("Mainmap.tmx");
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
		//App->transition->FadeToBlack(App->sceneTitle, App->scene, 2.0f);
		App->transition->Slide(App->sceneTitle, App->scene, 2.0f);
		/*if (exitButton !=nullptr) {
			App->gui->RemoveUiElement(exitButton);
			exitButton = nullptr;
		}*/
	}
	else if (element == ContinueButton) {
		App->LoadGame();
		App->map->Load("Mainmap.tmx");
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
		App->transition->Slide(App->sceneTitle, App->scene, 2.0f);
	}
	else if (element == exitButton) {
		App->audio->PlayFx(buttonFx);
		Exit = true;
	}
	else if (element == optionsButton) {
		App->audio->PlayFx(buttonFx);
		
		optionsMenu=App->gui->AddButton(400, 250, { 20,540,446,465 }, { 20,540,446,465 }, { 20,540,446,465 }, true, false, nullptr, this);
		backButton= App->gui->AddButton(430, 270, { 806,368,35,24 }, { 815,246,35,24 }, { 806,368,35,24 }, true, false, nullptr, this);
		fullScreen = App->gui->AddButton(500, 450, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
		App->gui->AddText(55, 25, "FULLSCREEN", App->font->Small, { 255,255,255 }, 42, false, false, fullScreen);
		App->gui->AddText(150, 20, "OPTIONS MENU", App->font->Small, { 255,255,255 }, 42, false, false, optionsMenu);
	}
	else if (element == backButton) {
		App->gui->RemoveUiElement(backButton);
		App->gui->RemoveUiElement(optionsMenu);
		App->gui->RemoveUiElement(fullScreen);
	}
	else if (element == fullScreen) {

		App->win->Fullscreen();
	}
	
}