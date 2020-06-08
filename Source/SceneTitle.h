
#pragma once
#include "Module.h"

struct SDL_Texture;
class UiElement;

class SceneTitle : public Module
{
public:

	SceneTitle();

	// Destructor
	virtual ~SceneTitle();

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

	void ButtonsAnimation();

private:
	//Main Buttons
	UiElement* newGameButton;
	UiElement* continueButton;
	UiElement* exitButton;
	UiElement* optionsButton;
	//Options Menu
	UiElement* optionsMenu;
	UiElement* backButton;
	UiElement* fullScreen;
	UiElement* about;
	UiElement* fxSlider;
	UiElement* soundSlider;
	UiElement* sliderbarMus;
	UiElement* sliderbarFx;

	SDL_Texture*	background;
	SDL_Texture*	titleLogo;

	int buttonFx;
	
	bool Exit;

};