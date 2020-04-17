#pragma once
#include "Entity.h"

enum BuildingType {
	Mine,
	Spaceship_factory,
	Base
};

class Building : public Entity {
	BuildingType type;
	uint tile_size;
	float ConstructionRatio;
	float ConstructionSpeed;
	void Update();
	void Draw();
	void OnConstruction();
};