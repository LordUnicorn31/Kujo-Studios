#pragma once
#include "Entity.h"

enum ResourceType {
	Ore,
	Gold
};

class Resource : public Entity {
	ResourceType type;
	void Update();
	void Draw();
};