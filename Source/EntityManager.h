#pragma once
#include "j1Module.h"
#include "Entity.h"
#include "EASTL/list.h"

class EntityManager :public j1Module {
public:

	EntityManager();

	virtual ~EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	void UpdateEntity(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

	//Entity* CreateEntity(type);
	//bool DestroyEntity(Entity*);
private:
	//eastl::list <Entity*>entities;
	//eastl::list <Entity*>ia_entities;
};