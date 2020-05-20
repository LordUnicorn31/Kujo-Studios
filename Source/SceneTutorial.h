#pragma once
#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
class UiElement;

class SceneTutorial : public Module
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
	
	void CreateButtons();

private:

	SDL_Texture* background = nullptr;
	SDL_Texture* character = nullptr;

	Animation captain;
	Animation girl;

	UiElement* skip;
	UiElement* wakeupTxt;
	UiElement* wakeupImage;
	UiElement* answerYesTxt;
	UiElement* answerYes;
	UiElement* answerNoTxt;
	UiElement* answerNo;
	UiElement* continueButton;
	UiElement* continueFake;

	int heyFx;
	int buttonFx;
	int girlFx;
	int captainFx;


	float startTime;
	float currentTime;
};