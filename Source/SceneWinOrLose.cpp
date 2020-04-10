#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SceneWinOrLose.h"
#include "j1Input.h"
#include "j1Map.h"

SceneWinOrLose::SceneWinOrLose() : Scene(SCENES::SCENE_WINORLOSE)
{

}

// Destructor
SceneWinOrLose::~SceneWinOrLose()
{
}


// Called before render is available
bool SceneWinOrLose::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneWinOrLose::Start()
{

	InitScene();

	return true;
}

// Called each loop iteration
bool SceneWinOrLose::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneWinOrLose::Update(float dt)
{
	bool ret = true;
	CameraDebugMovement(dt);
	DrawScene();
	return ret;
}

// Called each loop iteration
bool SceneWinOrLose::PostUpdate()
{
	bool ret = true;

	ExecuteTransition();
	return ret;
}


// Called before quitting
bool SceneWinOrLose::CleanUp()
{
	LOG("Freeing scene");

	App->map->CleanUp();

	return true;
}

void SceneWinOrLose::InitScene()
{
	

	App->render->camera.x = 0;										// Hem de decidir on comenza el player.
	App->render->camera.y = 0;
}

void SceneWinOrLose::DrawScene()
{
	
}

void SceneWinOrLose::ExecuteTransition()
{

}
