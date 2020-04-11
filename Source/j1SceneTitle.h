
#include "j1Module.h"

struct SDL_Texture;

class j1SceneTitle : public j1Module
{
public:

	j1SceneTitle();

	// Destructor
	virtual ~j1SceneTitle();

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

private:

	SDL_Texture*	background;
	SDL_Texture*	titleLogo;


};