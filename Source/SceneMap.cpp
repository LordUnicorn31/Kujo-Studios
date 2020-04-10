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

	CameraDebugMovement(dt);

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

	App->render->camera.x = 0;										// Hem de decidir on comenza el player.
	App->render->camera.y = 0;
}

void SceneMap::DrawScene()
{
	App->map->Draw();
}

void SceneMap::ExecuteTransition()
{
	
}
