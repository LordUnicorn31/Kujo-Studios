#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SceneTitle.h"
#include "j1Input.h"
#include "j1Map.h"

SceneTitle::SceneTitle() : Scene(SCENES::SCENE_TITLE)
{

}

// Destructor
SceneTitle::~SceneTitle()
{
}


// Called before render is available
bool SceneTitle::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneTitle::Start()
{

	InitScene();

	return true;
}

// Called each loop iteration
bool SceneTitle::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneTitle::Update(float dt)
{
	bool ret = true;
	CameraDebugMovement(dt);
	DrawScene();
	return ret;
}

// Called each loop iteration
bool SceneTitle::PostUpdate()
{
	bool ret = true;

	ExecuteTransition();
	return ret;
}


// Called before quitting
bool SceneTitle::CleanUp()
{
	LOG("Freeing scene");

	App->map->CleanUp();

	return true;
}

void SceneTitle::InitScene()
{
	
	App->render->camera.x = 0;										// Hem de decidir on comenza el player.
	App->render->camera.y = 0;
}

void SceneTitle::DrawScene()
{
	
}

void SceneTitle::ExecuteTransition()
{

}
