#include "j1Module.h"
#include "Scene.h"


class SceneWinOrLose : public Scene
{
public:

	SceneWinOrLose();

	// Destructor
	virtual ~SceneWinOrLose();

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

public:
	void InitScene();

	void DrawScene();

	void ExecuteTransition();

};