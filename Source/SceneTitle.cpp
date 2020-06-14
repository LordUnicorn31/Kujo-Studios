#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "GameScene.h"
#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "Input.h"
#include "Map.h"
#include "Minimap.h"
#include "Transitions.h"
#include "Gui.h"
#include "Fonts.h"
#include "Audio.h"
#include "PathFinding.h"
#include "Application.h"

SceneTitle::SceneTitle() : Module()
{
	name = "sceneTitle";
}

// Destructor
SceneTitle::~SceneTitle()
{
}


// Called before render is available
bool SceneTitle::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneTitle::Start()
{
	Exit = false;
	background = App->tex->Load("Resources/gui/background.png");
	titleLogo = App->tex->Load("Resources/gui/logo.png");	

	App->gui->AddText(10, 690, "2020 KUJO STUDIOS", App->font->smallFont, { 255,255,255,255 }, 16, false, false);

	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");

	App->audio->PlayMusic("Resources/audio/music/observing_star.ogg");
	return true;
}

// Called each loop iteration
bool SceneTitle::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneTitle::Update(float dt)
{
	bool ret = true;
	
	int w = App->win->GetWidth();
	int h = App->win->GetHeight();

	App->render->Blit(background, 0, 0, NULL,true, App->render->renderer, 1.5f);
	App->render->Blit(titleLogo, (int)2194, 0, NULL, true, App->render->renderer, 0.2f);

	if (newGameButton == nullptr || continueButton == nullptr || exitButton == nullptr || optionsButton == nullptr) {
		ButtonsAnimation();
	}

	if (Exit) {
		ret = false;
		Exit = false;
	}

	
	
	return ret;
}

// Called each loop iteration
bool SceneTitle::PostUpdate()
{
	App->render->Rendermouse();
	bool ret = true;

	return ret;
}


// Called before quitting
bool SceneTitle::CleanUp()
{
	LOG("Freeing scene");

	App->tex->UnLoad(background);
	App->tex->UnLoad(titleLogo);
	App->gui->DeleteAllUiElements();
	newGameButton = nullptr;
	continueButton = nullptr;
	exitButton = nullptr;
	
	return true;
}

void SceneTitle::Init()
{
	enabled = false;
	
	active = true;
}

void SceneTitle::ui_callback(UiElement* element) {
	if (element == newGameButton) {
		App->audio->PlayFx(buttonFx);
		App->transition->FadeToBlack(App->sceneTitle, App->sceneTutorial, 2.0f);
		App->audio->UnloadMusic();
	}
	else if (element == continueButton) {
		App->LoadGame();
		App->audio->PlayFx(buttonFx);
		App->map->Load("mainmap.tmx");
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
		App->transition->Slide(App->sceneTitle, App->scene, 2.0f);
		App->scene->tutorialActive = true;
	}
	else if (element == exitButton) {
		App->audio->PlayFx(buttonFx);
		Exit = true;
	}
	else if (element == optionsButton) {
		App->audio->PlayFx(buttonFx);

		optionsMenu = App->gui->AddImage(400, 250, { 20,540,446,465 }, true, false,false, nullptr, this);
		backButton = App->gui->AddButton(30, 40, { 806,368,35,24 }, { 815,246,35,24 }, { 806,368,35,24 }, true, false, false, optionsMenu, this);
		fullScreen = App->gui->AddButton(100, 250, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, optionsMenu, this);
		about = App->gui->AddButton(100, 350, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false,false, optionsMenu, this);
		sliderbarFx = App->gui->AddSlider(115, 100, App->audio->GetFxVolume(), MIX_MAX_VOLUME,true, false, false, optionsMenu, this);
		sliderbarMus = App->gui->AddSlider(115, 175, App->audio->GetMusicVolume(), MIX_MAX_VOLUME, true, false, false, optionsMenu, this);
		App->gui->AddText(55, 25, "FULLSCREEN", App->font->smallFont, { 255,255,255 }, 42, false, false, false, fullScreen);
		App->gui->AddText(150, 35, "OPTIONS MENU", App->font->smallFont, { 236,178,0 }, 42, false, false, false, optionsMenu);
		App->gui->AddText(70, 100, "FX", App->font->smallFont, { 236,178,0 }, 42, false, false, false, optionsMenu);
		App->gui->AddText(50, 175, "MUSIC", App->font->smallFont, { 236,178,0 }, 42, false, false, false, optionsMenu);
		App->gui->AddText(65, 25, "ABOUT US", App->font->smallFont, { 255,255,255 }, 42, false, false, false, about);

	}
	else if (element == backButton) {
		App->audio->PlayFx(buttonFx);
		App->gui->RemoveUiElement(optionsMenu);
	}
	else if (element == fullScreen) {
		App->audio->PlayFx(buttonFx);
		App->win->Fullscreen();
	}
	else if (element == about) {
		App->audio->PlayFx(buttonFx);
		ShellExecuteA(NULL, "open", "https://github.com/LordUnicorn31/Kujo-Studios", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (element == sliderbarFx) {
		App->audio->FxVolume(((UiSlider*)element)->value);
	}
	else if (element == sliderbarMus) {
		App->audio->MusicVolume(((UiSlider*)element)->value);
	}
}


void SceneTitle::ButtonsAnimation()
{

	newGameButton = App->gui->AddButton((int)525.5f, 340, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, nullptr, this);
	App->gui->AddText(15, 16, "NEW GAME", nullptr, { 236,178,0,255 }, 32, false, false, false, newGameButton);
	continueButton = App->gui->AddButton((int)525.5f, 420, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, nullptr, this);
	App->gui->AddText(20, 16, "CONTINUE", nullptr, { 65,175,94,255 }, 32, false, false, false, continueButton);
	optionsButton = App->gui->AddButton((int)525.5f, 500, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, nullptr, this);
	App->gui->AddText(32, 16, "OPTIONS", nullptr, { 16, 173, 171 }, 32, false, false, false, optionsButton);
	exitButton = App->gui->AddButton((int)525.5f, 580, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, nullptr, this);
	App->gui->AddText(75, 16, "EXIT", nullptr, { 152,30,30,255 }, 32, false, false, false, exitButton);

}