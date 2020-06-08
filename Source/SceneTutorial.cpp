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
#include "SceneTutorial.h"
#include "PathFinding.h"
#include "LoseScene.h"

SceneTutorial::SceneTutorial() : Module()
{
	name = "loseScene";

	captain.PushBack({ 0,247,230,230 });
	captain.PushBack({ 230,247,230,230 });
	captain.PushBack({ 460,247,230,230 });
	captain.PushBack({ 230,247,230,230 });
	captain.loop = true;

	girl.PushBack({ 0,0,230,230 });
	girl.PushBack({ 230,0,230,230 });
	girl.PushBack({ 460,0,230,230 });
	girl.PushBack({ 230,0,230,230 });
	girl.loop = true;
}

// Destructor
SceneTutorial::~SceneTutorial()
{
}

// Called before render is available
bool SceneTutorial::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneTutorial::Start()
{
	startTime = (float)(SDL_GetTicks() / 1000);

	background = App->tex->Load("Resources/gui/base.png");
	character = App->tex->Load("Resources/gui/char.png");
	
	//audios
	App->audio->PlayMusic("Resources/audio/music/music_sadpiano.ogg");
	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");
	heyFx = App->audio->LoadFx("Resources/audio/fx/hey.wav");
	App->audio->PlayFx(heyFx);
	girlFx = App->audio->LoadFx("Resources/audio/fx/girl.wav");
	captainFx = App->audio->LoadFx("Resources/audio/fx/captain.wav");

	App->audio->FxVolume(25);
	App->audio->MusicVolume(25);
	return true;
}

// Called each loop iteration
bool SceneTutorial::PreUpdate()
{
	

	return true;
}

// Called each loop iteration
bool SceneTutorial::Update(float dt)
{
	bool ret = true;
	
	currentTime = SDL_GetTicks()/1000 - startTime;

	App->render->Blit(background, 0, 0, NULL, true, App->render->renderer);


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

	if (currentTime < 4.00f)
	{
		App->render->Blit(character, 525, 200, &girl.GetCurrentFrame(dt));
	}
	if (currentTime >= 4 )
	{
		App->render->Blit(character, 850, 200, &girl.GetCurrentFrame(dt));
		App->render->Blit(character, 290, 200, &captain.GetCurrentFrame(dt));
		if(currentTime == 4 && wakeupImage == nullptr && answerYes == nullptr && answerNo == nullptr)
		{
			wakeupImage = App->gui->AddImage(290, 430, { 1253,728,795,129 }, true, false, false, nullptr, this);
			wakeupTxt = App->gui->AddText(20, 45, "Wake Up! Are you OK? You seem a bit confused", App->font->dialogFont, { 152,30,30,255 }, 10, false, false, false, wakeupImage, this);
			App->audio->PlayFx(girlFx);

			answerYes = App->gui->AddButton(288, 560, { 0,315,802,41 }, { 0,356,802,41 }, { 0,356,802,41 }, true, false, false, nullptr, this);
			answerYesTxt = App->gui->AddText(230, 4, "I'm fine relax Alice", App->font->dialogFont, { 16, 173, 171,255 }, 12, false, false, false, answerYes, this);
			answerNo = App->gui->AddButton(288, 602, { 0,315,802,41 }, { 0,356,802,41 }, { 0,356,802,41 }, true, false, false, nullptr, this);
			answerNoTxt = App->gui->AddText(230, 4, "No I'm not Ok! Where am I?", App->font->dialogFont, { 16, 173, 171,255 }, 12, false, false, false, answerNo, this);
		}

		if (currentTime > 4 && answerYes == nullptr && continueButton == nullptr)
		{
			continueButton = App->gui->AddButton(288, 560, { 0,315,802,41 }, { 0,356,802,41 }, { 0,356,802,41 }, true, false, false, nullptr, this);
			App->gui->AddText(230, 4, "Start your Adventure", App->font->dialogFont, { 16, 173, 171,255 }, 12, false, false, false, continueButton, this);

			continueFake = App->gui->AddButton(288, 602, { 0,315,802,41 }, { 0,356,802,41 }, { 0,356,802,41 }, true, false, false, nullptr, this);
			App->gui->AddText(230, 4, "Run Away", App->font->dialogFont, { 16, 173, 171,255 }, 12, false, false, false, continueFake, this);

		}
	}

	return ret;
}

void SceneTutorial::CreateButtons()
{
	
}

// Called each loop iteration
bool SceneTutorial::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool SceneTutorial::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(background);
	App->tex->UnLoad(character);
	App->audio->UnloadFx();
	App->gui->DeleteAllUiElements();

	return true;
}

void SceneTutorial::Init()
{
	enabled = false;

	active = true;
}

void SceneTutorial::ui_callback(UiElement* element)
{
	if (element == answerYes)
	{
		App->audio->PlayFx(buttonFx);
		App->audio->PlayFx(captainFx);
		App->gui->RemoveUiElement(wakeupTxt);
		wakeupTxt = nullptr;
		App->gui->RemoveUiElement(answerNo);
		answerNo = nullptr;
		App->gui->RemoveUiElement(answerYes);
		answerYes = nullptr;
		wakeupTxt = App->gui->AddText(20, 45, "Glad to hear that. Everything is prepared to leave", App->font->dialogFont, { 152,30,30,255 }, 10, false, false,false, wakeupImage, this);
		App->audio->PlayFx(girlFx);

	}
	if (element == answerNo)
	{
		App->audio->PlayFx(buttonFx);
		App->audio->PlayFx(captainFx);
		App->gui->RemoveUiElement(wakeupTxt);
		wakeupTxt = nullptr;
		App->gui->RemoveUiElement(answerNo);
		answerNo = nullptr;
		App->gui->RemoveUiElement(answerYes);
		answerYes = nullptr;
		wakeupTxt = App->gui->AddText(20, 45, "Hey, don't talk to me like that. It's time to leave", App->font->dialogFont, { 152,30,30,255 }, 10, false, false,false, wakeupImage, this);
		App->audio->PlayFx(girlFx);
		
	}

	if (element == continueButton) {
		App->gui->DeleteAllUiElements();
		App->audio->PlayFx(buttonFx);
		App->map->Load("mainmap.tmx");
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);

		App->scene->tutorialActive = true;

		App->transition->Slide(App->sceneTutorial, App->scene, 2.0f);
	}

	if (element == continueFake)
	{
		App->gui->DeleteAllUiElements();
		App->audio->PlayFx(buttonFx);
		App->transition->Slide(App->sceneTutorial, App->losescene, 2.0f);
	}
}