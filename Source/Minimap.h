#include "SDL.h"
#include "Application.h"
#include "Module.h"
#include "p2Point.h"


struct SDL_Texture;
struct SDL_Rect;

//enum class entity_display{DISPLAY_RECT,DISPLAY_ENTITY,DISPLAY_ICON};

class Minimap : public Module
{
public:
	Minimap();
	virtual ~Minimap();

	bool Awake(pugi::xml_node& config);

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Scale();
	void Descale();

	void Load();

	void Init();

public:
	bool display;
	iPoint position;
	//entity_display entities_mode;

private:
	
	bool MinimapCoords(int& map_x, int& map_y);
	void DrawCamera();
	void MinimapBorders();
	//void DrawEntitiesRectangle();
	//void DrawEntities();
	//void DrawEntitiesIcon();
	void DrawMinimap();

private:
	SDL_Texture* minimapTex = nullptr;
	int size;
	float minimapScale;
	int minimapWidth;
	int minimapHeight;

};

