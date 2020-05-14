#pragma once
#include "j1Module.h"
#include "EASTL/list.h"
#include "p2Point.h"
#include "j1Render.h"
#include "Animation.h"

class Entity;
class SDL_Texture;
enum class EntityType : unsigned char;
class UiElement;

enum class AviableEntities: unsigned char {
	base,
	mine,
	cuartel,
	ship_factory,
	collector,
	greenship,
	blueship,
	redship,
	gold,
	ore,
	PowerGenerator
};

struct EntitiesAnimations {
	Animation BuildMine;
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
	Animation BuildCuartel;
	Animation CuartelIdle;
	Animation BuildLab;
	Animation LabIdle;
	Animation FarmerShip;
	Animation AttackShip;
	Animation AttackShip2;
	Animation SpecialShip;
	Animation ArmedAttackShip;
	Animation ArmedAttackShip2;
	Animation ArmedSpecialShip;
	Animation PowerGeneratorIdle;
	Animation BuildPowerGenerator;
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

	Entity* CreateEntity(AviableEntities type, iPoint position);
	void DestroyEntity(Entity* entity);

	EntitiesAnimations Animations;
	UiElement* Panel;

private:
	bool newgame;
	void GenerateResources(int n_gold, int n_ore);
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);
	eastl::list <Entity*>entities;
	eastl::list<Entity*>SelectedEntities;
	bool DoLogic;
	float AccumulatedTime;
	float UpdateMsCycle;
	SDL_Texture* MineSprite;
	SDL_Texture* CuartelLab;
	SDL_Texture* BaseSprite;
	SDL_Texture* ShipsSprite;
	SDL_Texture* Copper;
	SDL_Texture* Titanium;
	SDL_Texture* PowerGeneratorSprite;
	void HandleInput();
	//max_resouces[]
	//current_resouces[]
};