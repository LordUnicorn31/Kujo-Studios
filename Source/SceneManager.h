#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "EASTL/vector.h"
#include "j1Module.h"
#include "Scene.h"

class SceneManager : public j1Module
{
public:
	SceneManager();
	~SceneManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


public:
	void	ScenePushbacks();										
	
	void	SwitchScene(SCENES scene_name);							
	void	LoadScene(SCENES scene_name);							
	void	UnloadScene(Scene* scene_to_unload);					

	Scene* CreateScene(SCENES scene_name);

public:
	Scene* current_scene;							
	Scene* next_scene;								

private:
	eastl::vector<Scene*>		scenes;								
};

#endif // !__SCENE_MANAGER_H__