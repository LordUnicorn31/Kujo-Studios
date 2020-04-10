#ifndef __SCENE_H__
#define __SCENE_H__

#include "j1App.h"	
#include "pugixml.hpp"
#include "p2Point.h"

struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;

enum class SCENES
{
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_MAP,
	SCENE_WINORLOSE,
	NONE
};

class Scene
{
public:
	Scene(SCENES scene_name);
	virtual ~Scene();

	virtual bool Awake(pugi::xml_node& config);					
	virtual bool Start();										
	virtual bool PreUpdate();									
	virtual bool Update(float dt);								
	virtual bool PostUpdate();									
	virtual bool CleanUp();										

public:
	virtual void InitScene();									
	virtual void DrawScene();									
	virtual SDL_Texture* SceneToTexture();						

	virtual void ExecuteTransition();							
	virtual void CameraDebugMovement(float dt);					
public:
	SCENES			scene_name;									

	int map_width;												
	int map_height;												
};

#endif // !__SCENE_H__