#pragma once
#include "EASTL/array.h"
#include "SDL_rect.h"

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
	Entity(EntityType type, SDL_Rect entityrect);
	virtual ~Entity();
	SDL_Rect EntityRect;
	EntityType etype;
	int health;
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
	virtual void UpdateLogic();
	//virtual void Die();
};