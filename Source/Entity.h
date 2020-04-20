#pragma once
#include "p2Point.h"
#include "EASTL/array.h"

class SDL_Texture;

enum class EntityType : unsigned char {
	TypeAi,
	TypeBuilding,
	TypeResource
};

struct AvailableMaterials {
	eastl::array<int, 3> ShipsCopperTitanium;
};

class Entity {
public:
	Entity(EntityType type, iPoint position);
	virtual ~Entity();
	iPoint position;
	EntityType etype;
	uint MaxHealth;
	int health;
	float HealthRegen;
	SDL_Texture* sprite;
	AvailableMaterials cost;
	bool selected;
	bool selectable;
	//Collider* collider;

	//eastl::array cost[3];
	//SDL_Rect entity_rect;
public:
	virtual void Draw(float dt); 
	virtual void Update(float dt);
	//virtual void Die();
};