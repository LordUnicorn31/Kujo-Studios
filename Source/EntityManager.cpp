#include "j1Textures.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Building.h"
#include "Ai.h"
#include "Resources.h"
#include "j1App.h"
#include "Animation.h"
#include "j1Input.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "p2Log.h"
#include <time.h>
#include "EASTL/vector.h"

EntityManager::EntityManager(): j1Module(),MineSprite(NULL),CuartelLab(NULL),BaseSprite(NULL),ShipsSprite(NULL),UpdateMsCycle((1.0f / 60.0f)),AccumulatedTime(0.0f),newgame(true) {
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
	//attack ship
	Animations.AttackShip.PushBack({ 24,23,66,66 });
	Animations.AttackShip.PushBack({ 121,21,66,66 });
	//Farmer ship
	Animations.AttackShip2.PushBack({ 242,28,61,61 });
	Animations.AttackShip2.PushBack({ 377,20,61,61 });

	Animations.FarmerShip.PushBack({29,147,52,52});
	Animations.FarmerShip.PushBack({131,147,52,52 });
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
	//building mine
	Animations.BuildMine.PushBack({ 256,64,64,64});
	//Idle cuartel
	Animations.CuartelIdle.PushBack({126,64,64,64});
	Animations.CuartelIdle.PushBack({ 0,0,64,64 });
	Animations.CuartelIdle.PushBack({ 126,64,64,64 });
	Animations.CuartelIdle.PushBack({ 128,0,64,64 });
	Animations.CuartelIdle.PushBack({ 126,64,64,64 });
	Animations.CuartelIdle.PushBack({ 0,64,64,64 });
	//Building Cuartels
	Animations.BuildCuartel.PushBack({ 64,0,64,64 });
	//Building Lab
	Animations.LabIdle.PushBack({ 64,250,64,64 });
	Animations.LabIdle.PushBack({ 128,250,64,64 });
	//Lab Idle
	Animations.BuildLab.PushBack({ 0,250,64,64 });
}

EntityManager::~EntityManager() {

}

void EntityManager::Init() {
	active = true;
	enabled = false;
}

void EntityManager::GenerateResources(int n_gold, int n_ore) {
	eastl::vector<iPoint> UsedTiles;
	int i = 0;
	iPoint randompostile;
	iPoint randomposmap;
	srand(time(0));
	while (i < n_gold) {
		randompostile=iPoint(1 + (rand() % 100), 1 + (rand() % 100));
		if (App->pathfinding->IsWalkable(randompostile)&& eastl::find(UsedTiles.begin(),UsedTiles.end(), randompostile)==UsedTiles.end()) {
			randomposmap = App->map->MapToWorld(randompostile.x, randompostile.y);
			CreateEntity(AviableEntities::gold, randomposmap);
			eastl::vector<iPoint>adjacent=App->pathfinding->FindWalkableAdjacents(randompostile);
			eastl::vector<iPoint>::iterator it;
			for (it = adjacent.begin(); it != adjacent.end(); ++it) {
				if (rand()%2) {
					iPoint adjacentscreen = App->map->MapToWorld((*it).x, (*it).y);
					CreateEntity(AviableEntities::gold, adjacentscreen);
					UsedTiles.push_back(adjacentscreen);
				}
			}
			UsedTiles.push_back(randompostile);
			++i;
			LOG("Gold number %d created", i);
		}
	}
	i = 0;
	while (i < n_ore) {
		randompostile = iPoint(1 + (rand() % 100), 1 + (rand() % 100));

		if (App->pathfinding->IsWalkable(randompostile) && eastl::find(UsedTiles.begin(), UsedTiles.end(), randompostile) == UsedTiles.end()) {
			randomposmap = App->map->MapToWorld(randompostile.x, randompostile.y);
			CreateEntity(AviableEntities::ore, randomposmap);
			eastl::vector<iPoint>adjacent = App->pathfinding->FindWalkableAdjacents(randompostile);
			eastl::vector<iPoint>::iterator it;
			for (it = adjacent.begin(); it != adjacent.end(); ++it) {
				if (rand() % 2) {
					iPoint adjacentscreen = App->map->MapToWorld((*it).x, (*it).y);
					CreateEntity(AviableEntities::ore, adjacentscreen);
					UsedTiles.push_back(adjacentscreen);
				}
			}
			UsedTiles.push_back(randompostile);
			++i;
			LOG("Ore number %d created", i);
		}
	}
}

bool EntityManager::Start() {
	//Load the initial entities
	if (newgame) {
		MineSprite = App->tex->Load("Resources/entities/drills/MineSprite.png");
		CuartelLab = App->tex->Load("Resources/entities/Cuarteles/cuartel + Lab.png");
		ShipsSprite = App->tex->Load("Resources/entities/ships/ships_spritesheet.png");
		BaseSprite = App->tex->Load("Resources/entities/bases/bases.png");
		Titanium= App->tex->Load("Resources/entities/Minerals/titanium1.png");
		Copper = App->tex->Load("Resources/entities/Minerals/copper1.png");
		GenerateResources(10, 10);
		CreateEntity(AviableEntities::ship_factory, iPoint(280, 300));
		CreateEntity(AviableEntities::cuartel, iPoint(280, 380));
		CreateEntity(AviableEntities::mine, iPoint(350, 300));
		CreateEntity(AviableEntities::collector, iPoint(400, 370));
		CreateEntity(AviableEntities::basicunit, iPoint(450, 370));
		CreateEntity(AviableEntities::collector, iPoint(500, 300));
		CreateEntity(AviableEntities::basicunit, iPoint(560, 370));
		CreateEntity(AviableEntities::collector, iPoint(610, 300));
		CreateEntity(AviableEntities::basicunit, iPoint(660, 370));
		CreateEntity(AviableEntities::collector, iPoint(710, 300));
		CreateEntity(AviableEntities::basicunit, iPoint(770, 370));
		CreateEntity(AviableEntities::collector, iPoint(840, 300));
		CreateEntity(AviableEntities::basicunit, iPoint(910, 370));
	}

	return true;
}

void EntityManager::HandleInput() {
	//TODO: Ordenar el handle input del entity manager
	static iPoint origin, mouse;
	SDL_Rect rect;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		App->input->GetMousePosition(origin.x, origin.y);
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		App->input->GetMousePosition(mouse.x, mouse.y);
		App->render->DrawQuad({ origin.x - App->render->camera.x, origin.y - App->render->camera.y, mouse.x - origin.x, mouse.y - origin.y }, 0, 200, 0, 100, false);
		App->render->DrawQuad({ origin.x - App->render->camera.x, origin.y - App->render->camera.y, mouse.x - origin.x, mouse.y - origin.y }, 0, 200, 0, 50);
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
		rect = { origin.x - App->render->camera.x, origin.y - App->render->camera.y, mouse.x - origin.x, mouse.y - origin.y };
		if (rect.w < 0) {
			rect.w = abs(rect.w);
			rect.x -= rect.w;
		}
		if (rect.h < 0) {
			rect.h = abs(rect.h);
			rect.y -= rect.h;
		}
		eastl::list<Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); ++it) {
			if ((*it)->selectable) {
				(*it)->selected = false;
				if (SDL_HasIntersection(&rect, &(*it)->EntityRect)) {
					(*it)->selected = true;
				}
			}
		}
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) {
		int xTile, yTile;
		App->input->GetMousePosition(xTile, yTile);
		xTile -= App->render->camera.x;
		yTile -= App->render->camera.y;
		iPoint MouseTile(App->map->WorldToMap(xTile, yTile));
		eastl::list<Entity*>::iterator it;
		eastl::list<Ai*> GroupAi;
		for (it = entities.begin(); it != entities.end(); ++it) {
			if ((*it)->etype == EntityType::TypeAi && (*it)->selected) {
				GroupAi.push_back((Ai*)(*it));
			}
		}
		//TODO: ARA CREAR LA FUNCIO AL MODUL PATHFINDING K REBI LA LLISTA I ENS CALCULI EL PATH PER TOTS
		if (GroupAi.size() > 1) {
			if (!App->pathfinding->CalculateGroupPath(GroupAi, MouseTile)) {
				eastl::list<Ai*>::iterator i;
				for (i = GroupAi.begin(); i != GroupAi.end(); ++i) {
					if ((*i)->TilePos != MouseTile) {
						if (App->pathfinding->CreatePath((*i)->TilePos, MouseTile) != -1) {
							(*i)->path = *App->pathfinding->GetLastPath();
							//FinalGoal.x = path.back().x;
							//FinalGoal.y = path.back().y;
							(*i)->path.erase((*i)->path.begin());
							(*i)->OnDestination = false;
						}
					}
				}
			}
		}
		else if (GroupAi.size() == 1) {
			Ai* ai = (*GroupAi.begin());
			if (ai->TilePos != MouseTile) {
				if (App->pathfinding->CreatePath(ai->TilePos, MouseTile) != -1) {
					ai->path = *App->pathfinding->GetLastPath();
					//FinalGoal.x = path.back().x;
					//FinalGoal.y = path.back().y;
					ai->path.erase((*GroupAi.begin())->path.begin());
					ai->OnDestination = false;
				}
			}
		}
	}
}

bool EntityManager::Update(float dt) {
	HandleInput();
	AccumulatedTime += (dt);
	if (AccumulatedTime >= UpdateMsCycle)
		DoLogic = true;
	UpdateAll(dt, DoLogic);
	if (DoLogic == true) {
		AccumulatedTime = 0.0f;
		DoLogic = false;
	}
	return true;
}

void EntityManager::UpdateAll(float dt, bool DoLogic) {
	eastl::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Update(dt);
		if (DoLogic)
			(*it)->UpdateLogic();
		(*it)->Draw(dt);
		//(*it)->Kill();
	}
	/*if (DoLogic) {
		eastl::list<Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); ++it) {
			(*it)->Update(dt);
			//(*it)->Kill();
		}
	}
	eastl::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Draw(dt);
	}*/
}

bool EntityManager::CleanUp() {
	App->tex->UnLoad(MineSprite);
	App->tex->UnLoad(BaseSprite);
	App->tex->UnLoad(ShipsSprite);
	App->tex->UnLoad(Titanium);
	App->tex->UnLoad(Copper);
	MineSprite = nullptr;
	CuartelLab = nullptr;
	BaseSprite = nullptr;
	ShipsSprite = nullptr;
	Titanium = nullptr;
	Copper = nullptr;
	return true;
}

Entity* EntityManager::CreateEntity(AviableEntities type,iPoint position) {
	Entity* ret = nullptr;
	switch (type) {
	case AviableEntities::base:
		ret = new Building(BuildingType::Base, position);
		ret->sprite = BaseSprite;
		break;
	case AviableEntities::mine:
		ret = new Building(BuildingType::Mine, position);
		ret->sprite = MineSprite;
		break;
	case AviableEntities::cuartel:
		ret = new Building(BuildingType::Cuartel, position);
		ret->sprite = CuartelLab;
		break;
	case AviableEntities::ship_factory:
		ret = new Building(BuildingType::Spaceship_factory, position);
		ret->sprite = CuartelLab;
		break;
	case AviableEntities::collector:
		ret = new Ai(AiType::Collector,position);
		ret->sprite = ShipsSprite;
		break;
	case AviableEntities::gold:
		ret = new Resource(ResourceType::Gold, position);
		ret->sprite = Copper;
		break;
	case AviableEntities::ore:
		ret = new Resource(ResourceType::Ore,position);
		ret->sprite = Titanium;
		break;
	case AviableEntities::basicunit:
		ret = new Ai(AiType::Basic_Unit,position);
		ret->sprite = ShipsSprite;
		break;
	}

	if (ret != nullptr)
		entities.push_back(ret);

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity) {

}

bool EntityManager::Load(pugi::xml_node& entitynode) {
	newgame=false;
	MineSprite = App->tex->Load("Resources/entities/drills/MineSprite.png");
	CuartelLab = App->tex->Load("Resources/entities/Cuarteles/cuartel + Lab.png");
	ShipsSprite = App->tex->Load("Resources/entities/ships/ships_spritesheet.png");
	BaseSprite = App->tex->Load("Resources/entities/bases/bases.png");
	Titanium = App->tex->Load("Resources/entities/Minerals/titanium1.png");
	Copper = App->tex->Load("Resources/entities/Minerals/copper1.png");
	int iterations = entitynode.child("numEntities").attribute("value").as_uint();
	pugi::xml_node CurrentEntity = entitynode.child("entity");
	for (int i = 0; i != iterations; ++i) {
		CreateEntity((AviableEntities)CurrentEntity.attribute("type").as_int(), iPoint(CurrentEntity.attribute("x").as_int(), CurrentEntity.attribute("y").as_int()));
		CurrentEntity=CurrentEntity.next_sibling();
	}
	return true;
}

bool EntityManager::Save(pugi::xml_node& managernode) {
	managernode.append_child("numEntities").append_attribute("value").set_value(entities.size());
	eastl::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it) {
		pugi::xml_node EntityNode = managernode.append_child("entity");
		EntityNode.append_attribute("x").set_value((*it)->EntityRect.x);
		EntityNode.append_attribute("y").set_value((*it)->EntityRect.y);
		switch ((*it)->etype) {
		case EntityType::TypeAi:
			switch (((Ai*)(*it))->Atype) {
			case AiType::Basic_Unit:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::basicunit);
				break;
			case AiType::Collector:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::collector);
				break;
			}
			break;
		case EntityType::TypeBuilding:
			switch (((Building*)(*it))->Btype) {
			case BuildingType::Base:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::base);
				break;
			case BuildingType::Mine:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::mine);
				break;
			case BuildingType::Cuartel:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::cuartel);
				break;
			case BuildingType::Spaceship_factory:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::ship_factory);
				break;
			}
			break;
		case EntityType::TypeResource:
			switch (((Resource*)(*it))->Rtype) {
			case ResourceType::Gold:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::gold);
				break;
			case ResourceType::Ore:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::ore);
				break;
			}
			break;
		}
	}
	return true;
}