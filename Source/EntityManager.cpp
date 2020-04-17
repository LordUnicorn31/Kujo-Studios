#include "EntityManager.h"
#include "Entity.h"
#include "Building.h"
#include "Ai.h"
#include "Resources.h"

EntityManager::EntityManager(): j1Module() {
	name = "EntityManager";
	MineSprite = nullptr;
	Base = nullptr;
	Ships = nullptr;
}

EntityManager::~EntityManager() {

}

void EntityManager::Init() {
	active = true;
	enabled = false;
}

bool EntityManager::Start() {
	//Load the initial entities

	return true;
}

void EntityManager::UpdateAll(float dt,bool DoLogic) {
	if (DoLogic) {
		eastl::list<Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); ++it) {
			(*it)->Update();
			//(*it)->Kill();
		}
	}
	eastl::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Draw();
	}
}

bool EntityManager::Update(float dt) {
	AccumulatedTime += dt;
	if (AccumulatedTime >= UpdateMsCycle)
		DoLogic = true;
	UpdateAll(dt, DoLogic);
	if (DoLogic == true) {
		AccumulatedTime = 0.0f;
		DoLogic = false;
	}
	return true;
}

bool EntityManager::CleanUp() {

	return true;
}

Entity* EntityManager::CreateEntity(AvibleEntities type,iPoint position) {
	Entity* ret = nullptr;
	switch (type) {
	case AvibleEntities::base:
		ret = new Building(BuildingType::Base, position);
		ret->sprite = Base;
		break;
	case AvibleEntities::mine:
		ret = new Building(BuildingType::Mine, position);
		ret->sprite = MineSprite;
		break;
	case AvibleEntities::collector:
		//ret = new Resource(ResourceType::);
		break;
	case AvibleEntities::gold:
		//ret = new Resource(ResourceType::);
		break;
	case AvibleEntities::ore:
		//ret = new Resource(ResourceType::);
		break;
	case AvibleEntities::basicunit:
		//ret = new Resource(ResourceType::);
		break;
	}

	if (ret != nullptr)
		entities.push_back(ret);

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity) {

}