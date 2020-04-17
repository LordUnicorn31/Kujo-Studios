#pragma once
#include "j1Module.h"
#include "EASTL/list.h"
#include "p2Point.h"

class Entity;
class SDL_Texture;
enum class EntityType : unsigned char;

enum class AvibleEntities: unsigned char {
	base,
	mine,
	ship_factory,
	collector,
	basicunit,
	gold,
	ore
};

class EntityManager :public j1Module {
public:

	EntityManager();
	~EntityManager();

	void Init();
	bool Start();
	bool Update(float dt);
	void UpdateAll(float dt,bool DoLogic);
	bool CleanUp();

	Entity* CreateEntity(AvibleEntities type,iPoint position);
	void DestroyEntity(Entity*entity);
private:
	eastl::list <Entity*>entities;
	bool DoLogic;
	float AccumulatedTime;
	float UpdateMsCycle;
	SDL_Texture* MineSprite;
	SDL_Texture* Base;
	SDL_Texture* Ships;
	//max_resouces[]
	//current_resouces[]
};