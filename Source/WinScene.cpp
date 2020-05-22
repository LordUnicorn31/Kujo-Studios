#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "GameScene.h"
#include "SceneTitle.h"
#include "Input.h"
#include "Map.h"
#include "Minimap.h"
#include "Transitions.h"
#include "Gui.h"
#include "Fonts.h"
#include "Audio.h"
#include "WinScene.h"

WinScene::WinScene() : Module()
{
	name = "winScene";
}

// Destructor
WinScene::~WinScene()
{
}


// Called before render is available
bool WinScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool WinScene::Start()
{

	background = App->tex->Load("Resources/gui/background.png");
	winText = App->tex->Load("Resources/gui/win_text.png");
	App->audio->PlayMusic("Resources/audio/music/interstellar_odyssey.ogg");

	titleButton = App->gui->AddButton(500, 600, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, nullptr, this);
	App->gui->AddText(10, 25, "MAIN MENU", App->font->smallFont, { 255,255,255 }, 42, false, false, titleButton);
	return true;
}

// Called each loop iteration
bool WinScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool WinScene::Update(float dt)
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
	App->render->Blit(winText, (int)(w * 1.55f), h, NULL, true, App->render->renderer, 0.2f);

	return ret;
}

// Called each loop iteration
bool WinScene::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool WinScene::CleanUp()
{
	LOG("Freeing scene");

	App->tex->UnLoad(background);
	App->tex->UnLoad(winText);
	App->audio->UnloadMusic();

	return true;
}

void WinScene::Init()
{
	enabled = false;

	active = true;
}

void WinScene::ui_callback(UiElement* element) {
	if (element == titleButton) {
		App->audio->PlayFx(buttonFx);
		App->transition->FadeToBlack(App->winscene, App->sceneTitle, 2.0f);
		App->audio->UnloadMusic();
		App->gui->RemoveUiElement(titleButton);
	}
}

