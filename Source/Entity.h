#pragma once
#include "p2Point.h"

enum EntityType {
	Ai,
	Building,
	Resource
};

class SDL_Texture;

class Entity {
public:
	Entity();
	virtual ~Entity();
	iPoint Position;
	EntityType type;
	int health;
	int CreationTime;
	SDL_Texture* sprite;
	bool selected;
	Collider* collider;
	//eastl::array cost[3];
	//SDL_Rect entity_rect;
	//bool available;
public:
	virtual void Draw(); 
	virtual void Update();
	virtual void Die();
};