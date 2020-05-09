#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1SceneLogo.h"
#include "j1SceneTitle.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Minimap.h"
#include "j1Transitions.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Audio.h"

j1SceneLogo::j1SceneLogo() : j1Module()
{
	name = "sceneLogo";
}

// Destructor
j1SceneLogo::~j1SceneLogo()
{
}


// Called before render is available
bool j1SceneLogo::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1SceneLogo::Start()
{
	rect = { 0,0,App->win->width, App->win->height };

	r = 0;

	hat = App->tex->Load("Resources/Logo/LOGOgorra.png");
	kujo = App->tex->Load("Resources/Logo/LOGOkujo.png");
	studios = App->tex->Load("Resources/Logo/LOGOstudios.png");
	App->audio->PlayFx(App->audio->LoadFx("Resources/audio/fx/intro.wav"));
	return true;
}

// Called each loop iteration
bool j1SceneLogo::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1SceneLogo::Update(float dt)
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

	App->render->DrawQuad(rect, 150, 0, 0, r);
	

	App->render->Blit(kujo, w*1.55f, h*1.55, NULL, true, App->render->renderer, 0.2);
	App->render->Blit(studios, w*1.55f, h*3.10f, NULL, true, App->render->renderer, 0.2);
	App->render->Blit(hat, w*2.95f, h*1.40, NULL, true, App->render->renderer, 0.2);

	r ++;


	if (r == 255)
	{
		r--;
		App->transition->FadeToBlack(App->sceneLogo, App->sceneTitle, 2.0f);
	}

	return ret;
}

// Called each loop iteration
bool j1SceneLogo::PostUpdate()
{
	bool ret = true;
	
	return ret;
}


// Called before quitting
bool j1SceneLogo::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(hat);
	App->tex->UnLoad(kujo);
	App->tex->UnLoad(studios);
	hat = nullptr;
	kujo = nullptr;
	studios = nullptr;
	return true;
}

void j1SceneLogo::Init()
{
	enabled = true;

	active = true;
}
