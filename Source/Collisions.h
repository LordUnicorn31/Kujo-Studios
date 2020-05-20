#pragma once
#ifndef __Collisions_H__
#define __Collisions_H__

#define MAX_COLLIDERS 100

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_BUILDING,
	COLLIDER_AI,
	COLLIDER_RESOURCE,
	COLLIDER_ENEMY,
	COLLIDER_PARTICLES,

	NUM_COLLIDER_TYPES
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	bool active = true;
	COLLIDER_TYPE type;
	Module* callback = nullptr;
	Collider();

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
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

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[NUM_COLLIDER_TYPES][NUM_COLLIDER_TYPES];
	bool debug = false;
	
};

#endif // __Collision_H__