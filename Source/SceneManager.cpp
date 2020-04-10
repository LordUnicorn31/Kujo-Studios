#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneLogo.h"
#include "SceneMap.h"
#include "SceneWinOrLose.h"
#include "j1Render.h"
#include "j1Input.h"

#include "p2Log.h"

SceneManager::SceneManager() : current_scene(nullptr)
{
	name = "scene_manager";
}

SceneManager::~SceneManager()
{

}

bool SceneManager::Awake(pugi::xml_node& config)
{
	bool ret = true;

	ScenePushbacks();

	current_scene = *scenes.begin();

	current_scene->Awake(config);

	return ret;
}

bool SceneManager::Start()
{
	bool ret = true;

	current_scene->Start();

	return ret;
}

bool SceneManager::PreUpdate()
{
	bool ret = true;

	current_scene->PreUpdate();

	return ret;
}

bool SceneManager::Update(float dt)
{
	bool ret = true;

	current_scene->Update(dt);

	return ret;
}

bool SceneManager::PostUpdate()
{
	bool ret = true;

	current_scene->PostUpdate();

	return ret;
}

bool SceneManager::CleanUp()
{
	bool ret = true;

	eastl::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		RELEASE((*item));
	}
	scenes.clear();

	return ret;
}


void SceneManager::SwitchScene(SCENES scene_name)
{
	current_scene->CleanUp();

	eastl::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			current_scene = (*item);
		}
	}

	if (current_scene != nullptr)
	{
		current_scene->Start();
	}
}

void SceneManager::LoadScene(SCENES scene_name)
{
	eastl::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			if (next_scene == nullptr)
			{
				next_scene = (*item);
			}
			else
			{
				next_scene->CleanUp();

				next_scene = (*item);
			}
		}
	}

	next_scene->Start();
}

void SceneManager::UnloadScene(Scene* scene_to_unload)
{
	eastl::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item) == scene_to_unload)
		{
			if ((*item) == current_scene)
			{
				if (next_scene != nullptr)															// Cleaning up current_scene. next_scene is re-assigned to current_scene first.
				{
					Scene* tmp = current_scene;

					current_scene = next_scene;

					next_scene = tmp;

					tmp = nullptr;

					next_scene->CleanUp();

					next_scene = nullptr;
				}
				else
				{
					LOG("UNLOAD SCENE ERROR: Two scenes were not active at the same time.");
				}

				break;
			}
			else
			{
				if (current_scene != nullptr)
				{
					(*item)->CleanUp();

					next_scene = nullptr;
				}
				else
				{
					LOG("UNLOAD SCENE ERROR: Two scenes were not active at the same time.");
				}

				break;
			}
		}
	}
}

// ---------------- CREATE SCENE METHODS ----------------
Scene* SceneManager::CreateScene(SCENES scene_name)
{
	Scene* item = nullptr;

	switch (scene_name)
	{
	case SCENES::SCENE_TITLE:

		item = new SceneTitle();

		break;

	case SCENES::SCENE_MAP:

		item = new SceneMap();

		break;

	case SCENES::SCENE_LOGO:
		
		item = new SceneLogo();

		break;

	}


	if (item != nullptr)
	{
		scenes.push_back(item);
	}

	return item;
}

void SceneManager::ScenePushbacks()
{
	CreateScene(SCENES::SCENE_TITLE);
	CreateScene(SCENES::SCENE_LOGO);
	CreateScene(SCENES::SCENE_MAP);
	CreateScene(SCENES::SCENE_WINORLOSE);
}