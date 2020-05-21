#include "Module.h"

struct SDL_Texture;


class GameScene : public Module
{
public:

	GameScene();

	// Destructor
	virtual ~GameScene();

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

	void Init();

	void Tutorial();

	void ui_callback(UiElement* element);

	void cameramovement(float time);

	bool tutorialActive;

	UiElement* infoImage;

private:

	//Top Right
	UiElement* peopleImage;
	UiElement* copperImage;
	UiElement* titaniumImage;

	//Pause Window
	UiElement* pauseButton;
	UiElement* pauseWindow;
	UiElement* continueButton;
	UiElement* saveButton;
	UiElement* optionsButton;
	UiElement* titleButton;

	//Options Window/Menu/Image
	UiElement* optionsMenu;
	UiElement* backButton;
	UiElement* fullScreen;

	int buttonFx;

	iPoint mousePos;
	int camSpeed;
	uint width;
	uint height;

	//Timer
	float startTime;
	float currentTime;
};