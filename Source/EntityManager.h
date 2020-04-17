#pragma once
#include "j1Module.h"
#include "Entity.h"
#include "EASTL/list.h"

class EntityManager :public j1Module {
public:

	EntityManager();
	~EntityManager();

	void Init();
	bool Start();
	bool Update(float dt);
	void UpdateEntities(float dt);
	bool CleanUp();

	Entity* CreateEntity(EntityType type);
	void DestroyEntity(Entity*entity);
private:
	eastl::list <Entity*>entities;
	//max_resouces[]
	//current_resouces[]
};