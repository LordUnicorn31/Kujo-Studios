#pragma once
#include "Entity.h"
#include "SDL_rect.h"
#include "EASTL/list.h"

class SDL_Texture;
class Ai;
class Animation;

enum class BuildingType : unsigned char {
	Mine,
	Cuartel,
	Spaceship_factory,
	Base,
	PowerGenerator
};


class Building : public Entity {
public:
	Building(BuildingType type, iPoint Position);
	~Building();
	BuildingType Btype;
	//uint tile_size;
	Animation IdleAnimation;
	Animation ConstructionAnimation;
	float ConstructionTime;
	//float ConstructionSpeed;
	uint level;
	bool OnConstruction;
	void Update(float dt);
	void Draw(float dt);
	//void Die();
	void LevelUp();
	void UiFunctionallity();
	void UpdateUiFunctionallity();
	eastl::list<AviableEntities>BuildingQueue;
	Ai* BuildingEntity;
	bool ToBuild;
	UiElement* BuildHUD;
};