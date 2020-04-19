#include "j1Textures.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Building.h"
#include "Ai.h"
#include "Resources.h"
#include "j1App.h"
#include "Animation.h"

EntityManager::EntityManager(): j1Module(),MineSprite(NULL),BaseSprite(NULL),ShipsSprite(NULL),UpdateMsCycle((1000.0f / 20.0f)),AccumulatedTime(0.0f) {
	name = "EntityManager";

	//Loading all the entities animations
	//BaseIdle1
	Animations.Base1Idle.PushBack({ 0,0,64,64 });
	Animations.Base1Idle.PushBack({ 64,0,64,64 });
	Animations.Base1Idle.speed = 2.0f;
	//Base2
	Animations.Base2Idle.PushBack({ 0,64,96,96 });
	Animations.Base2Idle.PushBack({ 96,64,96,96 });
	Animations.Base2Idle.PushBack({ 192,64,96,96 });
	Animations.Base2Idle.speed = 2.0f;
	//base3
	Animations.Base3Idle.PushBack({ 0,160,96,96 });
	Animations.Base3Idle.PushBack({ 96,160,96,96 });
	Animations.Base3Idle.PushBack({ 192,160,96,96 });
	Animations.Base3Idle.speed = 2.0f;
	//base4
	Animations.Base4Idle.PushBack({ 0,256,128,128 });
	Animations.Base4Idle.PushBack({ 128,256,128,128 });
	Animations.Base4Idle.speed = 2.0f;
	//base5
	Animations.Base5Idle.PushBack({ 0,384,128,128 });
	Animations.Base5Idle.PushBack({ 128,384,128,128 });
	Animations.Base5Idle.speed = 2.0f;
	//1st upgrade
	Animations.Upgrade1.PushBack({ 288,64,96,96 });
	//2nd upgrade
	Animations.Upgrade2.PushBack({ 288,160,96,96 });
	//3rd upgrade
	Animations.Upgrade3.PushBack({ 256,256,128,128 });
	//last upgrade
	Animations.Upgrade4.PushBack({ 264,392,112,112 });
	//MineIdle
	Animations.MineIdle.PushBack({ 0,0,64,64 });
	Animations.MineIdle.PushBack({ 64,0,64,64 });
	Animations.MineIdle.PushBack({ 128,0,64,64 });
	Animations.MineIdle.PushBack({ 192,0,64,64 });
	Animations.MineIdle.PushBack({ 256,0,64,64 });
	Animations.MineIdle.PushBack({ 320,0,64,64 });
	Animations.MineIdle.PushBack({ 384,0,64,64 });
	Animations.MineIdle.PushBack({ 448,0,64,64 });
	Animations.MineIdle.PushBack({ 0,64,64,64 });
	Animations.MineIdle.PushBack({ 64,64,64,64 });
	Animations.MineIdle.PushBack({ 128,64,64,64 });
	Animations.MineIdle.speed = 2.0f;
}

EntityManager::~EntityManager() {

}

void EntityManager::Init() {
	active = true;
	enabled = false;
}

bool EntityManager::Start() {
	//Load the initial entities
	MineSprite =App->tex->Load("Resources/entities/drills/MineSprite.png");
	ShipsSprite =App->tex->Load("Resources/entities/ships/ships_spritesheet.png");
	BaseSprite =App->tex->Load("Resources/entities/bases/bases.png");

	CreateEntity(AvibleEntities::mine, iPoint(640, 360));

	return true;
}

void EntityManager::UpdateAll(float dt,bool DoLogic) {
	if (DoLogic) {
		eastl::list<Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); ++it) {
			(*it)->Update(dt);
			//(*it)->Kill();
		}
	}
	eastl::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Draw(dt);
	}
}

bool EntityManager::Update(float dt) {
	AccumulatedTime += (dt*1000.0f);
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
	App->tex->UnLoad(MineSprite);
	App->tex->UnLoad(BaseSprite);
	App->tex->UnLoad(ShipsSprite);
	MineSprite = nullptr;
	BaseSprite = nullptr;
	ShipsSprite = nullptr;
	return true;
}

Entity* EntityManager::CreateEntity(AvibleEntities type,iPoint position) {
	Entity* ret = nullptr;
	switch (type) {
	case AvibleEntities::base:
		ret = new Building(BuildingType::Base, position);
		ret->sprite = BaseSprite;
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