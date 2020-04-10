#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SceneLogo.h"
#include "j1Input.h"
#include "j1Map.h"

SceneLogo::SceneLogo() : Scene(SCENES::SCENE_LOGO)
{

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

	InitScene();

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
	CameraDebugMovement(dt);
	DrawScene();
	return ret;
}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	bool ret = true;

	ExecuteTransition();
	return ret;
}


// Called before quitting
bool SceneLogo::CleanUp()
{
	LOG("Freeing scene");

	App->map->CleanUp();

	return true;
}

void SceneLogo::InitScene()
{
	App->map->GetMapSize(map_width, map_height);

	App->render->camera.x = 0;										// Hem de decidir on comenza el player.
	App->render->camera.y = 0;
}

void SceneLogo::DrawScene()
{
	
}

void SceneLogo::ExecuteTransition()
{

}
