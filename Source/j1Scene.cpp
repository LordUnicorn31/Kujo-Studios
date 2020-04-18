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

j1Scene::j1Scene() : j1Module()
{	
}

// Destructor
j1Scene::~j1Scene()
{
}


// Called before render is available
bool j1Scene::Awake(pugi::xml_node&config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Mainmap.tmx");
	App->minimap->Enable();
	App->entity->Enable();
	App->audio->PlayMusic("Resources/audio/music/Space.ogg");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
		App->render->camera.x+=5;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
		App->render->camera.x-=5;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		App->render->camera.y+=5;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		App->render->camera.y-=5;
	}

	App->map->Draw();
	return ret;
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

	return true;
}

void j1Scene::Init()
{
	enabled = false;

	active = true;
}