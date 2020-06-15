#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "GameScene.h"
#include "Input.h"
#include "Map.h"
#include "Minimap.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Gui.h"
#include "SceneTitle.h"
#include "Fonts.h"
#include "Transitions.h"
#include "WinScene.h"
#include "LoseScene.h"
#include "Collisions.h"
#include "Fow.h"
#include "QuestManager.h"
#include "Enemies.h"
#include "Particles.h"
//#include "Animation.h"

GameScene::GameScene() : Module()
{
	name = "scene";
}

// Destructor
GameScene::~GameScene()
{
}


// Called before render is available
bool GameScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool GameScene::Start()
{
	startTime = (float)SDL_GetTicks() / 1000;

	App->audio->PlayMusic("Resources/audio/music/game.ogg");
	pauseButton = App->gui->AddButton(1200, 10, { 755, 527, 39,39 }, { 871, 736, 39,39 }, { 755, 527, 39,39 }, true, false, false, nullptr, this);
	infoImage = App->gui->AddImage(750, 10, { 494,640,332,52 }, true, false, false, nullptr, this);
	peopleImage = App->gui->AddImage(30, 5, { 591,494,40,37 }, false, false, false, infoImage, nullptr);
	copperImage = App->gui->AddImage(130, 12, { 679,501,28,29 }, false, false, false, infoImage, nullptr);
	titaniumImage = App->gui->AddImage(230, 12, { 641,498,30,31 }, false, false, false, infoImage, nullptr);

	App->minimap->Enable();
	App->entity->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->quest->Enable();
	App->win->GetWindowSize(width, height);
	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");
	App->fow->SetVisibilityMap(App->map->data.width, App->map->data.height);
	camSpeed = 2;

	/*SDL_ShowCursor(SDL_ENABLE);*/
	return true;
}

// Called each loop iteration
bool GameScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool GameScene::Update(float dt)
{
	int a, b;
	App->input->GetMousePosition(a,b);
	if(App->input->GetKey(SDL_SCANCODE_1)==KEY_UP)
		App->particle->AddParticle(App->particle->shot, a, b, 50, 1, COLLIDER_TYPE::COLLIDER_ALLY_PARTICLE, ParticleType::SHOT, 180, 10, 0, 100);

	bool ret = true;

	currentTime = SDL_GetTicks() / 1000 - startTime;

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
	App->input->GetMousePosition(mousePos.x, mousePos.y);

	cameramovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->fow->ResetVisibilityMap();

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->fow->scouting_trail = !App->fow->scouting_trail;

	App->map->Draw();
	
	return ret;
}

void GameScene::cameramovement(float dt)
{
	/*if (mousepos.x == 0) {
		App->render->camera.x += camspeed * (dt * 1000);
	}*/
	if (-App->render->camera.x + App->render->camera.w +64 < (App->map->data.tileWidth * App->map->data.width) && (mousePos.x > (width -30) / App->win->scale)) {
		App->render->camera.x -= (int)(camSpeed * (dt * 1000));
	}
	if (App->render->camera.x < 180 && (mousePos.x < 30 / App->win->scale)){
		App->render->camera.x += (int)(camSpeed * (dt * 1000));
	}
	if (-App->render->camera.y + App->render->camera.h +32< (App->map->data.tileHeight * App->map->data.height) && (mousePos.y > (height -30) / App->win->scale)) {
		App->render->camera.y -= (int)(camSpeed * (dt * 1000));
	}
	if (App->render->camera.y < -64 && (mousePos.y < 30 / App->win->scale)) {
		App->render->camera.y += (int)(camSpeed * (dt * 1000));
	}
}

// Called each loop iteration
bool GameScene::PostUpdate()
{
	App->render->Rendermouse();
	bool ret = true;

	return ret;
}


// Called before quitting
bool GameScene::CleanUp()
{
	LOG("Freeing scene");

	App->map->CleanUp();
	App->gui->DeleteAllUiElements();
	App->audio->UnloadFx();
	App->audio->UnloadMusic();
	pauseButton = nullptr;
	infoImage = nullptr;
	peopleImage = nullptr;
	copperImage = nullptr;
	titaniumImage = nullptr;

	return true;
}

void GameScene::Init()
{
	enabled = false;

	active = true;
}

void GameScene::ui_callback(UiElement* element) {
	if (element == pauseButton) {
		App->audio->PlayMusic("Resources/audio/music/music_options.ogg", 0.0f);
		if (pauseButton != nullptr) {
			if (pauseWindow == nullptr) {

				pauseWindow = App->gui->AddImage(400, 150, { 0, 512, 483, 512 }, false, false);
				App->gui->AddText(170, 50, "PAUSE", NULL, { 236,178,0,255 }, 32, false, false, false, pauseWindow);
				continueButton = App->gui->AddButton(120, 110, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, pauseWindow, this);
				App->gui->AddText(23, 15, "CONTINUE", NULL, { 65,175,94,255 }, 32, false, false, false, continueButton);
				saveButton = App->gui->AddButton(120, 190, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, pauseWindow, this);
				App->gui->AddText(63, 16, "SAVE", NULL, { 194, 103, 6,255 }, 32, false, false, false, saveButton);
				optionsButton = App->gui->AddButton(120, 280, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, pauseWindow, this);
				App->gui->AddText(37, 15, "OPTIONS", NULL, { 16, 173, 171,255 }, 32, false, false, false, optionsButton);
				titleButton = App->gui->AddButton(120, 370, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, pauseWindow, this);
				App->gui->AddText(0, 16, "MAIN MENU", NULL, { 152,30,30,255 }, 32, false, false, false, titleButton);
				App->freeze = true;				
			
			}
			else {
				App->freeze = false;
				App->gui->RemoveUiElement(pauseWindow);
				pauseWindow = nullptr;
				App->audio->PlayMusic("Resources/audio/music/game.ogg", 0.0f);

			}
		}
	}
	if (element == titleButton) {
		//Create The Funtionality
		App->audio->PlayFx(buttonFx);
		App->transition->FadeToBlack(App->scene, App->sceneTitle);

	}
	if (element == continueButton) {
		App->audio->PlayMusic("Resources/audio/music/game.ogg", 0.0f);
		App->audio->PlayFx(buttonFx);
		App->freeze = false;
		if (pauseWindow != nullptr) {
			App->gui->RemoveUiElement(pauseWindow);
			pauseWindow = nullptr;
		}
	}
	if (element == fullScreen) {
		App->audio->PlayFx(buttonFx);
		App->win->Fullscreen();
	}
	if (element == saveButton) {
		App->audio->PlayFx(buttonFx);
		App->SaveGame();
	}
	if (element == optionsButton) {
		App->audio->PlayFx(buttonFx);
		optionsMenu = App->gui->AddButton(400, 250, { 20,540,446,465 }, { 20,540,446,465 }, { 20,540,446,465 }, true, false, false, nullptr, this);
		backButton = App->gui->AddButton(30, 20, { 806,368,35,24 }, { 815,246,35,24 }, { 806,368,35,24 }, true, false, false, optionsMenu, this);
		fullScreen = App->gui->AddButton(100, 300, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, false, optionsMenu, this);
		musSlider = App->gui->AddSlider(115, 200, App->audio->GetMusicVolume(), MIX_MAX_VOLUME, true, false, false, optionsMenu, this);
		fxSlider = App->gui->AddSlider(115, 100, App->audio->GetFxVolume(), MIX_MAX_VOLUME, true, false, false, optionsMenu, this);
		App->gui->AddText(55, 25, "FULLSCREEN", App->font->smallFont, { 255,255,255 }, 42, false, false, false, fullScreen);
		App->gui->AddText(150, 20, "OPTIONS MENU", App->font->smallFont, { 236,178,0 }, 42, false, false, false, optionsMenu);
		App->gui->AddText(70, 100, "FX", App->font->smallFont, { 236,178,0 }, 42, false, false, false, optionsMenu);
		App->gui->AddText(50, 200, "MUSIC", App->font->smallFont, { 236,178,0 }, 42, false, false, false, optionsMenu);
	}
	if (element == backButton) {
		App->gui->RemoveUiElement(optionsMenu);
		App->audio->PlayFx(buttonFx);
	}
	if (element == musSlider) {
		App->audio->MusicVolume(((UiSlider*)element)->value);
	}
	if (element == fxSlider) {
		App->audio->FxVolume(((UiSlider*)element)->value);
	}
}

