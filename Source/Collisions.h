#pragma once
#ifndef __Collisions_H__
#define __Collisions_H__

#define MAX_COLLIDERS 200

#include "Module.h"
class Entity;
class Enemy;
struct Particle;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_ALLY,
	COLLIDER_ENEMY,
	COLLIDER_ENEMY_PARTICLE,
	COLLIDER_ALLY_PARTICLE,
	COLLIDER_ENEMY_RANGE,
	COLLIDER_ALLY_RANGE,

	NUM_COLLIDER_TYPES
};

struct Collider
{
	SDL_Rect rect;
	bool toDelete = false;
	bool active = true;
	COLLIDER_TYPE type;
	Module* callback = nullptr;
	Entity* entity;
	Enemy* enemy;
	Particle* particle;
	Collider();

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr, Entity* entity = nullptr, Enemy* enemy = nullptr, Particle* particle = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback),
		entity(entity),
		enemy(enemy),
		particle(particle)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class Collisions : public Module
{
public:

	Collisions();
	~Collisions();

	void Init();
	bool PreUpdate() override;
	bool Update(float dt);
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr,Entity*entity=nullptr,Enemy*enemy=nullptr, Particle* particle = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[NUM_COLLIDER_TYPES][NUM_COLLIDER_TYPES];
	bool debug = false;
	
};

#endif // __Collision_H__