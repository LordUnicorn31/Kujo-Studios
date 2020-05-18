#include "j1Module.h"

struct SDL_Texture;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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

	void ui_callback(UiElement* element);

	void cameramovement(float time);

	UiElement* Info;
private:
	UiElement* Pause;
	UiElement* People;
	UiElement* Copper;
	UiElement* Titanium;
	UiElement* Settings_window;
	UiElement* Exit_button;
	UiElement* Continue_button;
	UiElement* fullScreen;
	UiElement* SaveButton;
	UiElement* options;
	UiElement* OptionsMenu;
	UiElement* BackButton;
	int buttonFx;
	bool exitGame;
	iPoint mousepos;
	int camspeed;
	uint width;
	uint height;
};