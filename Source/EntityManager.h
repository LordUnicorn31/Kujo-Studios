#pragma once
#include "j1Module.h"
#include "EASTL/list.h"
#include "p2Point.h"
#include "j1Render.h"
#include "Animation.h"

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

struct EntitiesAnimations {
	Animation MineIdle;
	Animation Base1Idle;
	Animation Base2Idle;
	Animation Base3Idle;
	Animation Base4Idle;
	Animation Base5Idle;
	Animation Upgrade1;
	Animation Upgrade2;
	Animation Upgrade3;
	Animation Upgrade4;
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

	EntitiesAnimations Animations;

private:
	eastl::list <Entity*>entities;
	bool DoLogic;
	float AccumulatedTime;
	float UpdateMsCycle;
	SDL_Texture* MineSprite;
	SDL_Texture* BaseSprite;
	SDL_Texture* ShipsSprite;
	//max_resouces[]
	//current_resouces[]
};