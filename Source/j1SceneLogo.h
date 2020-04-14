#include "j1Module.h"

struct SDL_Rect;
struct SDL_Texture;

class j1SceneLogo : public j1Module
{
public:

	j1SceneLogo();

	// Destructor
	virtual ~j1SceneLogo();

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

	SDL_Texture* hat;
	SDL_Texture* kujo;
	SDL_Texture* studios;

	float r = 0;
	SDL_Rect rect;
};