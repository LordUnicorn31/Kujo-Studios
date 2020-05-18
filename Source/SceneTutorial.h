#pragma once
#include "j1Module.h"
#include "Animation.h"

struct SDL_Texture;
class UiElement;

class SceneTutorial : public j1Module
{
public:

	SceneTutorial();

	// Destructor
	virtual ~SceneTutorial();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

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

	void Init();

	void ui_callback(UiElement* element);


private:

	SDL_Texture* character = nullptr;

	Animation captain;
	Animation girl;

	UiElement* wakeupButton;

	int heyFx;
	int buttonFx;
	int girlFx;
	int captainFx;


	float startTime;
	float currentTime;
};