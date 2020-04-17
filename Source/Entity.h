#pragma once
#include "p2Point.h"

class SDL_Texture;

enum class EntityType : unsigned char {
	TypeAi,
	TypeBuilding,
	TypeResource
};

class Entity {
public:
	Entity(EntityType type, iPoint position);
	virtual ~Entity();
	iPoint position;
	EntityType etype;
	int health;
	SDL_Texture* sprite;
	bool selected;
	//Collider* collider;

	//eastl::array cost[3];
	//SDL_Rect entity_rect;
	//bool available;
public:
	virtual void Draw(); 
	virtual void Update();
	//virtual void Die();
};