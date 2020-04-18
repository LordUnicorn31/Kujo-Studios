#pragma once
#include "Entity.h"

enum class ResourceType : unsigned char {
	Ore,
	Gold
};

class Resource : public Entity {
public:
	Resource(ResourceType type, iPoint position);
	~Resource();
	ResourceType Rtype;
	void Update(float dt);
	void Draw(float dt);
};