#pragma once
#include "Entity.h"

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
	uint tile_size;
	//float ConstructionRatio;
	//float ConstructionSpeed;
	uint level;
	void Update();
	void Draw();
	//void Die();
	void OnConstruction();
};