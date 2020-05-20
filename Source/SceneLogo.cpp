#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "Input.h"
#include "Map.h"
#include "Minimap.h"
#include "Transitions.h"
#include "Gui.h"
#include "Fonts.h"
#include "Audio.h"
#include "Particles.h"

SceneLogo::SceneLogo() : Module()
{
	name = "sceneLogo";
}

// Destructor
SceneLogo::~SceneLogo()
{
}


// Called before render is available
bool SceneLogo::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneLogo::Start()
{
	rect = { 0,0,App->win->width, App->win->height };

	r = 0;

	hat = App->tex->Load("Resources/gui/logo_cap.png");
	kujo = App->tex->Load("Resources/gui/logo_kujo.png");
	studios = App->tex->Load("Resources/gui/logo_studios.png");
	App->audio->PlayFx(App->audio->LoadFx("Resources/audio/fx/intro.wav"));

	return true;
}

// Called each loop iteration
bool SceneLogo::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneLogo::Update(float dt)
{
	
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_A)) 
	{
		App->particle->AddParticle(App->particle->shot, 200, 200, 1, COLLIDER_TYPE::COLLIDER_PARTICLES, ParticleType::SHOT, 45, 10);
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



	int w = App->win->GetWidth();
	int h = App->win->GetHeight();

	App->render->DrawQuad(rect, 150, 0, 0, (Uint8)r);
	
	App->render->Blit(kujo, (int)(w*1.55f),(int) (h*1.55), NULL, true, App->render->renderer, 0.2f);
	App->render->Blit(studios,(int) (w*1.55f), (int)(h*3.10f), NULL, true, App->render->renderer, 0.2f);
	App->render->Blit(hat, (int)(w*2.95f), (int)(h*1.40), NULL, true, App->render->renderer, 0.2f);

	r++;

	if (r == 255)
	{
		r--;
		App->transition->FadeToBlack(App->sceneLogo, App->sceneTitle, 2.0f);
	}

	return ret;
}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	bool ret = true;
	
	return ret;
}


// Called before quitting
bool SceneLogo::CleanUp()
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

void SceneLogo::Init()
{
	enabled = true;

	active = true;
}
