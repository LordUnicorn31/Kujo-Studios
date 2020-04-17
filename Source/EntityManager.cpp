#include "EntityManager.h"

EntityManager::EntityManager(): j1Module() {
	name = "EntityManager";
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

void EntityManager::UpdateEntities(float dt) {

}

bool EntityManager::Update(float dt) {

	return true;
}

bool EntityManager::CleanUp() {

	return true;
}

Entity* EntityManager::CreateEntity(EntityType type) {

	return nullptr;
}

void EntityManager::DestroyEntity(Entity* entity) {

}