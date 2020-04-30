/*#pragma once
#include "j1Module.h"
#include "EASTL/list.h"

class Entity;

class MovementManager :public j1Module {
public:

	MovementManager();
	~MovementManager();

	void Init();
	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void AddEntity(Entity*entity);

private:
	eastl::list <Entity*>MovingEntities;
};*/