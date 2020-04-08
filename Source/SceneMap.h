#pragma once

#include "j1Module.h"
#include "Scene.h"

struct SDL_Texture;

class SceneMap : public Scene
{
public:

	SceneMap();

	// Destructor
	virtual ~SceneMap();

	// Called before render is available
	bool Awake(pugi::xml_node&config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	void InitScene();								

	void DrawScene();								

	void ExecuteTransition();

};