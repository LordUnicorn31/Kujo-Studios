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
#include "LoseScene.h"

LoseScene::LoseScene() : Module()
{
	name = "loseScene";
}

// Destructor
LoseScene::~LoseScene()
{
}

// Called before render is available
bool LoseScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool LoseScene::Start()
{

	background = App->tex->Load("Resources/gui/background.png");
	loseText = App->tex->Load("Resources/gui/lose_screen.png");
	App->audio->PlayMusic("Resources/audio/music/epic_fall.ogg");

	titleButton = App->gui->AddButton(500, 600, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, nullptr, this);
	App->gui->AddText(55, 25, "MAIN MENU", App->font->smallFont, { 255,255,255 }, 42, false, false, false, titleButton);

	return true;
}

// Called each loop iteration
bool LoseScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool LoseScene::Update(float dt)
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
	App->render->Blit(loseText, w * 1.55f, h, NULL, true, App->render->renderer, 0.2);

	return ret;
}

// Called each loop iteration
bool LoseScene::PostUpdate()
{
	App->render->Rendermouse();
	bool ret = true;

	return ret;
}


// Called before quitting
bool LoseScene::CleanUp()
{
	LOG("Freeing scene");

	App->tex->UnLoad(background);
	App->tex->UnLoad(loseText);
	App->audio->UnloadMusic();


	return true;
}

void LoseScene::Init()
{
	enabled = false;

	active = true;
}

void LoseScene::ui_callback(UiElement* element) {
	if (element == titleButton) {
		App->audio->PlayFx(buttonFx);
		App->transition->FadeToBlack(App->losescene, App->sceneTitle, 2.0f);
		App->audio->UnloadMusic();
		App->gui->RemoveUiElement(titleButton);
	}
}


