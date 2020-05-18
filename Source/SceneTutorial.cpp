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
#include "SceneTutorial.h"
#include "j1Pathfinding.h"

SceneTutorial::SceneTutorial() : j1Module()
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
	startTime = SDL_GetTicks() / 1000;

	character = App->tex->Load("Resources/gui/char.png");
	
	App->audio->PlayMusic("Resources/audio/music/music_sadpiano.ogg");

	buttonFx = App->audio->LoadFx("Resources/audio/fx/beep.wav");
	heyFx = App->audio->LoadFx("Resources/audio/fx/hey.wav");
	App->audio->PlayFx(heyFx);

	girlFx = App->audio->LoadFx("Resources/audio/fx/girl.wav");

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

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->map->Load("Mainmap.tmx");
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
		App->transition->FadeToBlack(App->sceneTutorial, App->scene, 2.0f);
	}
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
	if (currentTime >= 4)
	{
		App->render->Blit(character, 755, 200, &girl.GetCurrentFrame(dt));
		if(currentTime == 4)
		{
			wakeupButton = App->gui->AddImage(200.5f, 430, { 1253,728,795,129 }, true, false, nullptr, this);
			App->gui->AddText(2, 45, "Wake Up!; Are you OK, you seem a bit confused", App->font->dialogFont, { 255, 255, 255, 255 }, 10, false, false, wakeupButton, this);
			App->audio->PlayFx(girlFx);
		}
	}

	//App->render->Blit(character, 50, 200, &captain.GetCurrentFrame(dt));

	return ret;
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



	App->audio->PlayFx(buttonFx);
	App->map->Load("Mainmap.tmx");
	int w, h;
	uchar* data = NULL;
	if (App->map->CreateWalkabilityMap(w, h, &data))
		App->pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);
	App->transition->Slide(App->sceneTutorial, App->scene, 2.0f);
}