#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SceneMap.h"
#include "j1Input.h"
#include "j1Map.h"

SceneMap::SceneMap() : Scene(SCENES::SCENE_MAP)
{
	
}

// Destructor
SceneMap::~SceneMap()
{
}


// Called before render is available
bool SceneMap::Awake(pugi::xml_node&config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneMap::Start()
{
	App->map->Load("Mainmap.tmx");

	InitScene();

	return true;
}

// Called each loop iteration
bool SceneMap::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneMap::Update(float dt)
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

	DrawScene();
	return ret;
}

// Called each loop iteration
bool SceneMap::PostUpdate()
{
	bool ret = true;

	ExecuteTransition();
	return ret;
}


// Called before quitting
bool SceneMap::CleanUp()
{
	LOG("Freeing scene");

	App->map->CleanUp();

	return true;
}

void SceneMap::InitScene()
{
	App->map->GetMapSize(map_width, map_height);

	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
	App->render->camera.y = -40;
}

void SceneMap::DrawScene()
{
	App->map->Draw();
}

void SceneMap::ExecuteTransition()
{
	
}
