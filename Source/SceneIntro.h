#include "Module.h"

struct SDL_Rect;
struct SDL_Texture;

class SceneIntro : public Module
{
public:

	SceneIntro();

	// Destructor
	virtual ~SceneIntro();

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

	SDL_Texture* img1;
	SDL_Texture* img2;
	SDL_Texture* img3;
	float s = 0;
	SDL_Rect rect;

	UiElement* mouseImage;
};