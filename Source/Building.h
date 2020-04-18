#pragma once
#include "Entity.h"
#include "SDL_rect.h"
#include "Animation.h"

class SDL_Texture;

enum class BuildingType : unsigned char {
	Mine,
	Spaceship_factory,
	Base
};


class Building : public Entity {
public:
	Building(BuildingType type, iPoint Position);
	~Building();
	BuildingType Btype;
	//uint tile_size;
	Animation* IdleAnimation;
	float ConstructionTime;
	//float ConstructionSpeed;
	uint level;
	bool OnConstruction;
	void Update(float dt);
	void Draw(float dt);
	//void Die();
	void LevelUp();
};