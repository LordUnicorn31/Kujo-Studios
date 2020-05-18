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
#include "Building.h"
#include "Resources.h"
#include "Ai.h"
#include "j1Gui.h"
#include "j1SceneTitle.h"
#include "j1Fonts.h"
#include "j1Transitions.h"
#include "j1Transitions.h"
#include "j1WinScene.h"
#include "j1LoseScene.h"
#include "j1Collisions.h"
#include "Fow.h"
//#include "Animation.h"




j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{
}


// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	startTime = SDL_GetTicks() / 1000;

	App->audio->PlayMusic("Resources/audio/music/music_space.ogg");
	Pause = App->gui->AddButton(1200, 10, { 755, 527, 39,39 }, { 871, 736, 39,39 }, { 755, 527, 39,39 }, true, false, nullptr, this);
	Info = App->gui->AddButton(750, 10, { 494,640,332,52 }, { 494,574,332,52 }, { 494,640,332,52 }, true, false, nullptr, this);
	People = App->gui->AddImage(30, 5, { 591,494,40,37 }, false, false, Info, nullptr);
	Copper = App->gui->AddImage(130, 12, { 679,501,28,29 }, false, false, Info, nullptr);
	Titanium = App->gui->AddImage(230, 12, { 641,498,30,31 }, false, false, Info, nullptr);
	App->minimap->Enable();
	App->entity->Enable();
	App->collisions->Enable();
	//Unit1 = App->gui->AddButton(0, 600, { 32,544,430,208}, { 32,544,440,208 }, { 32,544,440,208 }, true, false, nullptr, this);
	App->win->GetWindowSize(width, height);
	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");
	App->fow->SetVisibilityMap(App->map->data.width, App->map->data.height);
	camspeed = 2;

	if (tutorialActive == true)
	{
		tutorialImage = App->gui->AddImage(474, 200, { 494,574,332,52 }, false, false, nullptr, this);
		tutorialTxt = App->gui->AddText(10, 12, "'Welcome to the tutorial'", App->font->tutorialFont, { 255,255,255,255 }, 12, false, false, tutorialImage);

		tutorialRect = { 0,0,64,64 };

		questOneActive = true;
		questTwoActive = false;
		questThreeActive = false;
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

void j1Scene::Tutorial()
{
	if (questImage == nullptr)
	{
		questImage = App->gui->AddImage(1000, 260, { 1253, 858, 245, 128 }, false, false, nullptr, this);
		questOne = App->gui->AddText(15, 20, "1.Construct a Builder", App->font->Small, { 255,255,255,255 }, 12, false, false, questImage);
		questTwo = App->gui->AddText(15, 50, "2.Construct a Mine", App->font->Small, { 255,255,255,255 }, 12, false, false, questImage);
		questThree = App->gui->AddText(15, 80, "3.Collect 300 Copper", App->font->Small, { 255,255,255,255 }, 12, false, false, questImage);
	}
	if (questOneActive == true && questTwoActive == false && questThreeActive == false)
	{
		if (currentTime > 8 && tutorialTxt != nullptr && questInfoImage == nullptr)
		{
			App->gui->RemoveUiChilds(tutorialImage);
			tutorialTxt = nullptr;

			tutorialTxt = App->gui->AddText(25, 12, "'Construct a Builder'", App->font->tutorialFont, { 236,178,0,255 }, 12, false, false, tutorialImage);

			questInfoImage = App->gui->AddImage(474, 600, { 1253,728,795,129 }, true, false, nullptr, this);
			questInfo = App->gui->AddText(20, 30, "To cronstruct a Builder click in the Main Base", App->font->dialogFont, { 255,30,30,255 }, 10, false, false, questInfoImage, this);
			questInfo = App->gui->AddText(20, 75, "In the left panel click in the Builder Icon", App->font->dialogFont, { 255,30,30,255 }, 10, false, false, questInfoImage, this);

			tutorialRect.x = 610;
			tutorialRect.y = 300;

			//Falta crear el rectangulo rojo para que vean en el panel Builder
		}

		App->render->DrawQuad(tutorialRect, 255, 0, 0, 50, true, true);

		eastl::list<Entity*>::const_iterator it;

		for (it = App->entity->GetEntities().cbegin(); App->entity->GetEntities().cend() != it; ++it)
		{
			if ((*it)->etype != EntityType::TypeAi)
				continue;
			if (((Ai*)(*it))->Atype == AiType::Collector)
			{
				questOneActive = false;
				App->gui->RemoveUiChilds(tutorialImage);
				tutorialTxt = nullptr;
				App->gui->RemoveUiChilds(questInfoImage);
				questInfo == nullptr;
			}
		}

	}
	else if (questOneActive == false && questTwoActive == true && questThreeActive == false)
	{
		if (tutorialTxt != nullptr && questInfoImage != nullptr)
		{
			tutorialTxt = App->gui->AddText(25, 12, "'Construct a Mine'", App->font->tutorialFont, { 236,178,0,255 }, 12, false, false, tutorialImage);

			questInfoImage = App->gui->AddImage(474, 600, { 1253,728,795,129 }, true, false, nullptr, this);
			questInfo = App->gui->AddText(20, 30, "To cronstruct a Builder double click in the Builder", App->font->dialogFont, { 255,30,30,255 }, 10, false, false, questInfoImage, this);
			questInfo = App->gui->AddText(20, 75, "In the left panel click in the Mine Icon", App->font->dialogFont, { 255,30,30,255 }, 10, false, false, questInfoImage, this);
		}

		eastl::list<Entity*>::const_iterator it;

		for (it = App->entity->GetEntities().cbegin(); App->entity->GetEntities().cend() != it; ++it)
		{
			if ((*it)->etype != EntityType::TypeBuilding)
				continue;

			if (((Building*)(*it))->Btype == BuildingType::Mine)
			{
				questTwoActive = false;
				App->gui->RemoveUiChilds(tutorialImage);
				tutorialTxt = nullptr;
				App->gui->RemoveUiChilds(questInfoImage);
				questInfo == nullptr;
			}
		}
	}
	else if (questOneActive == false && questTwoActive == false && questThreeActive == true)
	{
		if (tutorialTxt != nullptr && questInfoImage != nullptr)
		{
			tutorialTxt = App->gui->AddText(25, 12, "'Collect 300 copper'", App->font->tutorialFont, { 236,178,0,255 }, 12, false, false, tutorialImage);

			questInfoImage = App->gui->AddImage(474, 600, { 1253,728,795,129 }, true, false, nullptr, this);
			questInfo = App->gui->AddText(20, 30, "To collect copper the Mine should be placed in copper ore", App->font->dialogFont, { 255,30,30,255 }, 10, false, false, questInfoImage, this);
			questInfo = App->gui->AddText(20, 75, "If the amount of ore collected will increase depending in the ores around", App->font->dialogFont, { 255,30,30,255 }, 10, false, false, questInfoImage, this);
		}
		eastl::list<Entity*>::const_iterator it;
		for (it = App->entity->GetEntities().cbegin(); App->entity->GetEntities().cend() != it; ++it)
		{
			if ((*it)->etype != EntityType::TypeResource)
				continue;
			if (((Resource*)(*it))->Rtype == ResourceType::Gold)
			{
				questThreeActive = false;
				App->gui->RemoveUiChilds(tutorialImage);
				tutorialTxt = nullptr;
				App->gui->RemoveUiChilds(questInfoImage);
				questInfo == nullptr;
			}
		}
	}

}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
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
	App->input->GetMousePosition(mousepos.x, mousepos.y);

	cameramovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->fow->ResetVisibilityMap();

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->fow->scouting_trail = !App->fow->scouting_trail;

	if (exitGame) {
		ret = false;
		exitGame = false;
	}

	App->map->Draw();

	if (tutorialActive == true)
	{
		Tutorial();
	}


	return ret;
}

void j1Scene::cameramovement(float dt)
{
	/*if (mousepos.x == 0) {
		App->render->camera.x += camspeed * (dt * 1000);
	}*/
	if (-App->render->camera.x + App->render->camera.w +64 < (App->map->data.tile_width * App->map->data.width) && (mousepos.x > (width -30) / App->win->scale)) {
		App->render->camera.x -= camspeed * (dt * 1000);
	}
	if (App->render->camera.x < 180 && (mousepos.x < 30 / App->win->scale)){
		App->render->camera.x += camspeed * (dt * 1000);
	}
	if (-App->render->camera.y + App->render->camera.h +32< (App->map->data.tile_height * App->map->data.height) && (mousepos.y > (height -30) / App->win->scale)) {
		App->render->camera.y -= camspeed * (dt * 1000);
	}
	if (App->render->camera.y < -64 && (mousepos.y < 30 / App->win->scale)) {
		App->render->camera.y += camspeed * (dt * 1000);
	}
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
		App->audio->UnloadMusic();
		App->audio->PlayMusic("Resources/audio/music/music_options.ogg");
		App->audio->MusicVolume(5);
		if (Pause != nullptr) {
			if (Settings_window == nullptr) {
				Settings_window = App->gui->AddImage(400, 150, { 0, 512, 483, 512 }, false, false);
				
				App->gui->AddText(170, 50, "PAUSE", NULL, { 236,178,0,255 }, 32, false, false, Settings_window);
				Exit_button = App->gui->AddButton(120, 370, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(78, 16, "EXIT", NULL, { 152,30,30,255 }, 32, false, false, Exit_button);
				Continue_button = App->gui->AddButton(120, 110, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(23, 15, "CONTINUE", NULL, { 65,175,94,255 }, 32, false, false, Continue_button);
				options = App->gui->AddButton(120, 280, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(37, 15, "OPTIONS", NULL, { 16, 173, 171,255 }, 32, false, false, options);
				SaveButton = App->gui->AddButton(120, 190, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, Settings_window, this);
				App->gui->AddText(63, 16, "SAVE", NULL, { 194, 103, 6,255 }, 32, false, false, SaveButton);
				App->freeze = true;
				
			
			}
			else {
				App->freeze = false;
				App->gui->RemoveUiElement(Settings_window);
				Settings_window = nullptr;
				App->audio->UnloadMusic();
				App->audio->PlayMusic("Resources/audio/music/music_space.ogg");

			}
		}
	}
	if (element == Exit_button) {
		exitGame = true;
	}
	if (element == Continue_button) {
		App->audio->PlayFx(buttonFx);
		App->audio->UnloadMusic();
		App->audio->PlayMusic("Resources/audio/music/music_space.ogg");

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
	if (element == options) {
		App->audio->PlayFx(buttonFx);
		OptionsMenu = App->gui->AddImage(400, 150, { 20,540,446,465 }, true, false, nullptr, this);
		BackButton = App->gui->AddButton(430, 200, { 806,368,35,24 }, { 815,246,35,24 }, { 806,368,35,24 }, true, false, nullptr, this);
		fullScreen = App->gui->AddButton(500, 450, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, true, false, nullptr, this);
		App->gui->AddText(55, 25, "FULLSCREEN", App->font->Small, { 255,255,255 }, 42, false, false, fullScreen);
		App->gui->AddText(150, 20, "OPTIONS MENU", App->font->Small, { 236,178,0 }, 42, false, false, OptionsMenu);
		App->gui->AddText(70, 100, "FX", App->font->Small, { 236,178,0 }, 42, false, false, OptionsMenu);
		App->gui->AddText(30, 175, "MUSIC", App->font->Small, { 236,178,0 }, 42, false, false, OptionsMenu);
		FxSlider = App->gui->AddSlider(100, 100, true, false, OptionsMenu, this, 76);
		MusSlider = App->gui->AddSlider(100, 175, true, false, OptionsMenu, this, 76);
	}

	else if (element == BackButton) {
		App->gui->RemoveUiElement(BackButton);
		App->gui->RemoveUiElement(OptionsMenu);
		App->gui->RemoveUiElement(fullScreen);
		App->gui->RemoveUiElement(FxSlider);
		App->gui->RemoveUiElement(MusSlider);
		
		
	}
}