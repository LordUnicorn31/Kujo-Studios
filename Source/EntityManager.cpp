#include "Textures.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Building.h"
#include "Ai.h"
#include "Resources.h"
#include "Application.h"
#include "Animation.h"
#include "Input.h"
#include "PathFinding.h"
#include "Map.h"
#include "p2Log.h"
#include <time.h>
#include "EASTL/vector.h"
#include "Gui.h"
#include "Fonts.h"
#include "GameScene.h"
#include "EASTL/string.h"
#include "Audio.h"
#include "Collisions.h"
#include "Particles.h"

EntityManager::EntityManager(): Module(),MineSprite(NULL),CuartelLab(NULL),BaseSprite(NULL),ShipsSprite(NULL),UpdateMsCycle((1.0f / 60.0f)),AccumulatedTime(0.0f),newgame(true),BuildButton(nullptr) {
	name = "EntityManager";
	/*
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
	Animations.AttackShip.speed = 2.5f;
	//Farmer ship
	Animations.AttackShip2.PushBack({ 242,28,61,61 });
	Animations.AttackShip2.PushBack({ 377,20,61,61 });
	Animations.AttackShip2.speed = 3.0f;

	Animations.SpecialShip.PushBack({29,324,57,57});
	Animations.SpecialShip.PushBack({131,324,57,57});
	Animations.SpecialShip.speed = 1.5f;

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
	//attack ships with improved weapoon
	Animations.ArmedAttackShip.PushBack({ 229,221,79,79 });
	Animations.ArmedAttackShip.PushBack({ 369,221,79,79 });
	Animations.ArmedAttackShip.speed = 2.5f;

	Animations.ArmedAttackShip2.PushBack({233,332,80,80});
	Animations.ArmedAttackShip2.PushBack({ 372,332,80,80 });
	Animations.ArmedAttackShip2.speed = 3.0f;

	Animations.ArmedSpecialShip.PushBack({237,110,77,77});
	Animations.ArmedSpecialShip.PushBack({377,110,77,77});
	Animations.ArmedSpecialShip.speed = 1.5f;
	//Power Generator animations
	Animations.PowerGeneratorIdle.PushBack({0,0,64,64});
	Animations.PowerGeneratorIdle.PushBack({ 64,0,64,64 });
	Animations.PowerGeneratorIdle.speed = 4.0f;
	Animations.BuildPowerGenerator.PushBack({128,0,64,64});
	*/
	BuildCost[1] = { 0,0 };
	BuildCost[2] = { 50,0 };
	BuildCost[3] = { 180,0 };
	BuildCost[4] = { 300,0 };
	BuildCost[5] = { 0,70 };
	BuildCost[6] = { 300,300 };
	BuildCost[7] = { 125,225 };
	BuildCost[8] = { 50,200 };
	BuildCost[9] = { 200,0 };
	BuildCost[10] = { 0,200 };
	BuildCost[11] = { 0,200 };
	BuildCost[12] = { 0,300 };
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
			iPoint adjacentscreen;
			for (it = adjacent.begin(); it != adjacent.end(); ++it) {
				adjacentscreen = App->map->MapToWorld((*it).x, (*it).y);
				if (rand()%2 && eastl::find(UsedTiles.begin(), UsedTiles.end(), adjacentscreen) == UsedTiles.end()) {
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
			iPoint adjacentscreen;
			for (it = adjacent.begin(); it != adjacent.end(); ++it) {
				adjacentscreen = App->map->MapToWorld((*it).x, (*it).y);
				if (rand() % 2 && eastl::find(UsedTiles.begin(), UsedTiles.end(), adjacentscreen) == UsedTiles.end()) {
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
		MineSprite = App->tex->Load("Resources/entities/drills/mine_sprite.png");
		CuartelLab = App->tex->Load("Resources/entities/barracks/barracks_lab.png");
		ShipsSprite = App->tex->Load("Resources/entities/ships/ships_spritesheet.png");
		BaseSprite = App->tex->Load("Resources/entities/bases/bases.png");
		Titanium= App->tex->Load("Resources/entities/minerals/titanium1.png");
		Copper = App->tex->Load("Resources/entities/minerals/copper1.png");
		PowerGeneratorSprite = App->tex->Load("Resources/entities/generator.png");
		buildFx = App->audio->LoadFx("Resources/audio/fx/building.wav");
		upgradeFx = App->audio->LoadFx("Resources/audio/fx/upgrade.ogg");
		shipFx = App->audio->LoadFx("Resources/audio/fx/shipBuild.wav");
		GenerateResources(15, 15);
		CreateEntity(AviableEntities::base, iPoint(610, 300));
		Resources[0] = 9999;
		Resources[1] = 9999;
	}
	Panel = App->gui->AddImage(0, 0, { 1024,0,226,720 }, true, false, false, nullptr, this);
	CopperString = App->gui->AddText(160, 20, (std::to_string(Resources[0]).c_str()), App->font->resourcesPanelFont, { 236,178,0,255 }, 20, false, false, false, App->scene->infoImage);
	TitaniumString = App->gui->AddText(262, 20, (std::to_string(Resources[1]).c_str()), App->font->resourcesPanelFont, { 236,178,0,255 }, 20, false, false, false, App->scene->infoImage);
	CurrentAction = ActionNone;
	return true;
}

void EntityManager::HandleInput() {
	static iPoint origin, mouse;
	SDL_Rect rect;
	int x, y;
	switch (CurrentAction) {
	case ActionNone:
		//SA DE OPTIMITZAR AIXO (AQUEST IF ACTUALITZA LA HUD DE TRAINING DE EDIFICIS WHILE NO ESTEM EN ACTION TRAINING)
		if (!SelectedEntities.empty()) {
			if (SelectedEntities.front()->etype== EntityType::TypeBuilding) {
				if (((Building*)SelectedEntities.front())->BuildingEntity != CurrentBuildingEntity) {
					((Building*)SelectedEntities.front())->UpdateUiFunctionallity();
					CurrentBuildingEntity = ((Building*)SelectedEntities.front())->BuildingEntity;
				}
			}
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			App->input->GetMousePosition(origin.x, origin.y);
			CurrentAction = ActionSelection;
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP && App->gui->UiUnderMouse()==nullptr) 
			CurrentAction = ActionMoving;
		break;

	case ActionSelection:
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			App->input->GetMousePosition(mouse.x, mouse.y);
			App->render->DrawQuad({ origin.x - App->render->camera.x, origin.y - App->render->camera.y, mouse.x - origin.x, mouse.y - origin.y }, 0, 200, 0, 100, false);
			App->render->DrawQuad({ origin.x - App->render->camera.x, origin.y - App->render->camera.y, mouse.x - origin.x, mouse.y - origin.y }, 0, 200, 0, 50);
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
			//Remove la ui k tenen
			CurrentAction = ActionNone;
			if (App->gui->UiUnderMouse() != nullptr)
				break;

			if (!SelectedEntities.empty())
				App->gui->RemoveUiChilds(Panel);
			eastl::list<Entity*>::iterator item;
			for (item = SelectedEntities.begin(); item != SelectedEntities.end(); ++item) {
				(*item)->selected = false;
			}
			SelectedEntities.clear();
			App->input->GetMousePosition(mouse.x, mouse.y);
			rect = { origin.x - App->render->camera.x, origin.y - App->render->camera.y, mouse.x - origin.x, mouse.y - origin.y };
			if (rect.w < 0) {
				rect.w = abs(rect.w);
				rect.x -= rect.w;
			}
			if (rect.h < 0) {
				rect.h = abs(rect.h);
				rect.y -= rect.h;
			}
			if (rect.w == 0 && rect.h == 0) {
				rect.w = 1;
				rect.h = 1;
				eastl::list<Entity*>::reverse_iterator it;
				for (it = entities.rbegin(); it != entities.rend(); ++it) {
					if ((*it)->selectable && SDL_HasIntersection(&rect, &(*it)->EntityRect)) {
						(*it)->selected = true;
						SelectedEntities.push_back((*it));
						(*it)->UiFunctionallity();
						break;
					}
				}
			}
			else {
				eastl::list<Entity*>::reverse_iterator it;
				int i = 0;
				int x = -1;
				int y = 1;
				for (it = entities.rbegin(); it != entities.rend() && i<MAXSELECTEDUNITS; ++it) {
					if ((*it)->selectable && (*it)->etype == EntityType::TypeAi && SDL_HasIntersection(&rect, &(*it)->EntityRect)) {
						(*it)->selected = true;
						SelectedEntities.push_back((*it));
						++x;
						if (x == 3) {
							x = 0;
							y += 1;
						}
						App->gui->AddHUDBar(x*66 + 2, y*46 + 200, (*it)->MaxHealth, &(*it)->health, { 1279,416,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, false, Panel, nullptr);
						switch (((Ai*)(*it))->Atype) {
						case AiType::Collector:
							App->gui->AddImage(x * 66 + 2 + 11, (y - 1) * 46 + 200 + 7, { 1291,135,39,39 },false,false,false,Panel);
							break;
						case AiType::RedShip:
							App->gui->AddImage(x * 66 + 2 + 11, (y - 1) * 46 + 200 + 7, { 1290,83,39,39 }, false, false, false, Panel);
							break;
						case AiType::BlueShip:
							App->gui->AddImage(x * 66 + 2 + 11, (y - 1) * 46 + 200 + 7, { 1291,28,39,39 }, false, false, false, Panel);
							break;
						case AiType::GreenShip:
							App->gui->AddImage(x * 66 + 2 + 11, (y - 1) * 46 + 200 + 7, { 1290,198,39,39 }, false, false, false, Panel);
							break;
						}
						++i;
					}
				}
			}
		}
		break;

	case ActionConstruction:
		App->input->GetMousePosition(x, y);
		x -= App->render->camera.x;
		y -= App->render->camera.y;
		switch (ToCreate) {
		case AviableEntities::none:
		{
			break;
		}
		case AviableEntities::mine:
		{
			SDL_Rect minerect = { 0,0,64,64 };
			App->render->Blit(MineSprite, x, y, &minerect);
			break;
		}
		case AviableEntities::cuartel:
		{
			SDL_Rect cuartelrect = { 126,64,64,64 };
			App->render->Blit(CuartelLab, x, y, &cuartelrect);
			break;
		}
		case AviableEntities::ship_factory:
		{
			SDL_Rect factoryrect = { 64,250,64,64 };
			App->render->Blit(CuartelLab, x, y, &factoryrect);
			break;
		}
		case AviableEntities::PowerGenerator:
		{
			SDL_Rect generatorrect = { 0,0,64,64 };
			App->render->Blit(PowerGeneratorSprite, x, y, &generatorrect);
			break;
		}
		}
		//dibuixar el quadradet per indicar si es pot construir alla o no
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
			//Mirar si les tiles son walkables
			iPoint Tile = App->map->WorldToMap(x, y);
			//Si o son, enviari el collector a construir (ES EL SELECTED!!!) i ferlo unselectable fins k ledifici s'acabi de construir
			//CHECK RECT WALCKABILITY
			//CHACK THAT THERE IS NO BUILDING ENTTITY IN THAT SQUARE
			if (App->gui->UiUnderMouse() == nullptr && App->pathfinding->IsWalkable(Tile, 2)) {
				eastl::list<Entity*>::iterator it;
				SDL_Rect Rect = { x,y,64,64 };
				bool build = true;
				for (it = entities.begin(); it != entities.end(); ++it) {
					if (SDL_HasIntersection(&(*it)->EntityRect, &Rect) && (*it)->etype == EntityType::TypeBuilding) {
						build = false;
						break;
					}
				}
				if (build) {
					if (EnaughResources(ToCreate)) {
						App->audio->PlayFx(buildFx);
						PayCost(ToCreate);
						App->gui->RemoveUiChilds(Panel);
						Building* NewBuilding = (Building*)CreateEntity(ToCreate, iPoint(x, y));
						((Ai*)SelectedEntities.front())->Working = true;
						((Ai*)SelectedEntities.front())->WorkingTime = NewBuilding->ConstructionTime;
						SelectedEntities.front()->selected = false;
						App->pathfinding->CreatePath(((Ai*)SelectedEntities.front())->TilePos, Tile);
						((Ai*)SelectedEntities.front())->path = *App->pathfinding->GetLastPath();
						((Ai*)SelectedEntities.front())->OnDestination = false;
						SelectedEntities.clear();
					}
					else {
						NotEnaughResourcesText = App->gui->AddText(5, 600, "Not enough resources", App->font->smallFont, { 255,0,0,0 }, 16, false, false,false, Panel);
						build = false;
						App->gui->RemoveUiElement(CopperIcon);
						App->gui->RemoveUiElement(TitaniumIcon);;
						App->gui->RemoveUiElement(Coppernum);
						App->gui->RemoveUiElement(Titaniumnum);
					}
				}
			}
			else {
				App->gui->RemoveUiElement(CopperIcon);
				App->gui->RemoveUiElement(TitaniumIcon);;
				App->gui->RemoveUiElement(Coppernum);
				App->gui->RemoveUiElement(Titaniumnum);
			}
			CurrentAction = ActionNone;
			ToCreate = AviableEntities::none;
		}
		break; 

	case ActionTraining:
		if (((Building*)SelectedEntities.front())->BuildingEntity != CurrentBuildingEntity) {
			((Building*)SelectedEntities.front())->UpdateUiFunctionallity();
			CurrentBuildingEntity = ((Building*)SelectedEntities.front())->BuildingEntity;
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
			if (App->gui->UiUnderMouse() == nullptr) {
				App->gui->RemoveUiChilds(Panel);
				SelectedEntities.front()->selected = false;
				SelectedEntities.clear();
				ToCreate = AviableEntities::none;
				CurrentAction = ActionNone;
			}
			else if (App->gui->UiUnderMouse() != BuildButton) {
				App->gui->RemoveUiElement(BuildButton);
				App->gui->RemoveUiElement(CopperIcon);
				App->gui->RemoveUiElement(TitaniumIcon);
				App->gui->RemoveUiElement(NotEnaughResourcesText);
				App->gui->RemoveUiElement(Coppernum);
				App->gui->RemoveUiElement(Titaniumnum);
				NotEnaughResourcesText = nullptr;
				BuildButton = nullptr;
				CopperIcon = nullptr;
				TitaniumIcon = nullptr;
			}
			else {
				//fer una cola de entities per crear
				if (EnaughResources(ToCreate)) {
					App->audio->PlayFx(shipFx);
					PayCost(ToCreate);
					((Building*)SelectedEntities.front())->BuildingQueue.push_back(ToCreate);
					((Building*)SelectedEntities.front())->ToBuild = true;
				}
				else {
					if (NotEnaughResourcesText == nullptr) {
						NotEnaughResourcesText = App->gui->AddText(5, 600, "Not enough resources", App->font->smallFont, { 255,0,0,0 }, 16, false, false, false, Panel);
					}
				}
			}
		}
		break;

	case ActionUpgrading:
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
			if (App->gui->UiUnderMouse() == nullptr){
				App->input->GetMousePosition(mouse.x, mouse.y);
				rect = { mouse.x - App->render->camera.x, mouse.y - App->render->camera.y,1,1 };
				eastl::list<Entity*>::iterator i;
				for (i = entities.begin(); i != entities.end(); ++i) {
					if ((*i)->etype == EntityType::TypeAi && SDL_HasIntersection(&rect, &(*i)->EntityRect)) {
						if (((Ai*)(*i))->Atype == AviableToAi(ToCreate)) {
							if (EnaughResources(ToCreate) && !((Ai*)(*i))->Armed) {
								App->audio->PlayFx(upgradeFx);
								PayCost(ToCreate);
								((Ai*)(*i))->Upgrade();
								//ToCreate = AviableEntities::none;
								//CurrentAction = ActionNone;
							}
							break;
						}
					}
				}
				App->gui->RemoveUiChilds(Panel);
				SelectedEntities.front()->selected = false;
				SelectedEntities.clear();
				CurrentAction = ActionNone;
				ToCreate = AviableEntities::none;
			}
			else {
				App->gui->RemoveUiElement(CopperIcon);
				App->gui->RemoveUiElement(TitaniumIcon);;
				App->gui->RemoveUiElement(Coppernum);
				App->gui->RemoveUiElement(Titaniumnum);
			}
		}
		break;

	case ActionMoving:
		CurrentAction = ActionNone;
		int xTile, yTile;
		App->input->GetMousePosition(xTile, yTile);
		xTile -= App->render->camera.x;
		yTile -= App->render->camera.y;
		rect = { xTile, yTile, 1, 1 };
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
		break;
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
	}
	eastl::list<Entity*>::iterator i = entities.begin();
	while (i != entities.end()) {
		if ((*i)->todie) {
			Entity* todestroy = (*i);
			++i;
			DestroyEntity(todestroy);
		}
		else
			++i;
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

bool EntityManager::PostUpdate() {
	((UiText*)CopperString)->ChangeMessage(std::to_string((int)Resources[0]).c_str());
	((UiText*)TitaniumString)->ChangeMessage(std::to_string((int)Resources[1]).c_str());
	return true;
}

bool EntityManager::CleanUp() {
	App->tex->UnLoad(MineSprite);
	App->tex->UnLoad(BaseSprite);
	App->tex->UnLoad(ShipsSprite);
	App->tex->UnLoad(Titanium);
	App->tex->UnLoad(Copper);
	App->tex->UnLoad(PowerGeneratorSprite);
	App->gui->RemoveUiElement(Panel);
	App->gui->RemoveUiElement(CopperString);
	App->gui->RemoveUiElement(TitaniumString);
	MineSprite = nullptr;
	CuartelLab = nullptr;
	BaseSprite = nullptr;
	ShipsSprite = nullptr;
	Titanium = nullptr;
	Copper = nullptr;
	PowerGeneratorSprite = nullptr;
	Panel = nullptr;
	App->audio->UnloadFx();
	return true;
}

Entity* EntityManager::CreateEntity(AviableEntities type,iPoint position) {
	Entity* ret = nullptr;
	switch (type) {
	case AviableEntities::base:
		ret = new Building(BuildingType::Base, position);
		ret->sprite = BaseSprite;
		entities.insert(eastl::find(entities.cbegin(), entities.cend(), FirstBuilding), ret);
		FirstBuilding = ret;
		break;
	case AviableEntities::mine:
		ret = new Building(BuildingType::Mine, position);
		ret->sprite = MineSprite;
		entities.insert(eastl::find(entities.cbegin(), entities.cend(), FirstBuilding), ret);
		FirstBuilding = ret;
		break;
	case AviableEntities::cuartel:
		ret = new Building(BuildingType::Cuartel, position);
		ret->sprite = CuartelLab;
		entities.insert(eastl::find(entities.cbegin(), entities.cend(), FirstBuilding), ret);
		FirstBuilding = ret;
		break;
	case AviableEntities::ship_factory:
		ret = new Building(BuildingType::Spaceship_factory, position);
		ret->sprite = CuartelLab;
		entities.insert(eastl::find(entities.cbegin(), entities.cend(), FirstBuilding), ret);
		FirstBuilding = ret;
		break;
	case AviableEntities::PowerGenerator:
		ret = new Building(BuildingType::PowerGenerator, position);
		ret->sprite = PowerGeneratorSprite;
		entities.insert(eastl::find(entities.cbegin(), entities.cend(), FirstBuilding), ret);
		FirstBuilding = ret;
		break;
	case AviableEntities::collector:
		ret = new Ai(AiType::Collector,position);
		ret->sprite = ShipsSprite;
		entities.push_back(ret);
		break;
	case AviableEntities::gold:
		ret = new Resource(ResourceType::Gold, position);
		ret->sprite = Copper;
		entities.push_front(ret);
		break;
	case AviableEntities::ore:
		ret = new Resource(ResourceType::Ore,position);
		ret->sprite = Titanium;
		entities.push_front(ret);
		break;
	case AviableEntities::redship:
		ret = new Ai(AiType::RedShip,position);
		ret->sprite = ShipsSprite;
		entities.push_back(ret);
		break;
	case AviableEntities::blueship:
		ret = new Ai(AiType::BlueShip, position);
		ret->sprite = ShipsSprite;
		entities.push_back(ret);
		break;
	case AviableEntities::greenship:
		ret = new Ai(AiType::GreenShip, position);
		ret->sprite = ShipsSprite;
		entities.push_back(ret);
		break;
	}

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity) {
	eastl::list<Entity*>::iterator it = eastl::find(entities.begin(), entities.end(), entity);
	if (it != entities.end()) {
		delete (*it);
		entities.erase(it);
	}
}

bool EntityManager::Load(pugi::xml_node& entitynode) {
	newgame=false;
	MineSprite = App->tex->Load("Resources/entities/drills/mine_sprite.png");
	CuartelLab = App->tex->Load("Resources/entities/barracks/barracks_lab.png");
	ShipsSprite = App->tex->Load("Resources/entities/ships/ships_spritesheet.png");
	BaseSprite = App->tex->Load("Resources/entities/bases/bases.png");
	Titanium = App->tex->Load("Resources/entities/minerals/titanium1.png");
	Copper = App->tex->Load("Resources/entities/minerals/copper1.png");
	PowerGeneratorSprite = App->tex->Load("Resources/entities/generator.png");
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
			case AiType::RedShip:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::redship);
				break;
			case AiType::Collector:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::collector);
				break;
			case AiType::BlueShip:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::blueship);
				break;
			case AiType::GreenShip:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::greenship);
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
			case BuildingType::PowerGenerator:
				EntityNode.append_attribute("type").set_value((int)AviableEntities::PowerGenerator);
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

void EntityManager::ui_callback(UiElement* element) {
	if (element->type==UiTypes::EButton) {
		if (((UiEntityButton*)element)->entitytype == EntityType::TypeBuilding) {
			CurrentAction = ActionConstruction;
			ToCreate = ((UiEntityButton*)element)->entity;
			CopperIcon = App->gui->AddImage(20, 550, { 679,501,28,29 }, false, false, false, Panel, nullptr);
			TitaniumIcon = App->gui->AddImage(110, 550, { 641,498,30,31 }, false, false, false, Panel, nullptr);
			Coppernum = App->gui->AddText(55, 550, std::to_string(((int)GetCost(ToCreate)[0])).c_str(), App->font->resourcesPanelFont, { 16, 173, 171,255 }, 20, false, false, false, Panel, nullptr);
			Titaniumnum = App->gui->AddText(145, 550, std::to_string(((int)GetCost(ToCreate)[1])).c_str(), App->font->resourcesPanelFont, { 16, 173, 171,255 }, 20, false, false, false, Panel, nullptr);
			App->gui->RemoveUiElement(NotEnaughResourcesText);
		}
		else if (((UiEntityButton*)element)->entitytype == EntityType::TypeAi) {
			if (((UiEntityButton*)element)->entity == AviableEntities::redship || ((UiEntityButton*)element)->entity == AviableEntities::blueship || ((UiEntityButton*)element)->entity == AviableEntities::greenship || ((UiEntityButton*)element)->entity == AviableEntities::collector) {
				CurrentAction = ActionTraining;
				ToCreate = ((UiEntityButton*)element)->entity;
				BuildButton = App->gui->AddButton(25, 625, { 1281,486,163,49 }, { 1450,486,163,49 }, { 1626,486,163,49 }, true, false, false, Panel, this);
				App->gui->AddText(55, 16, "BUILD", App->font->smallFont, { 65,175,94 }, 42, false, false, false, BuildButton);
				CopperIcon = App->gui->AddImage(20, 550, { 679,501,28,29 }, false, false, false, Panel, nullptr);
				TitaniumIcon = App->gui->AddImage(110, 550, { 641,498,30,31 }, false, false, false, Panel, nullptr);
				Coppernum = App->gui->AddText(55, 550, std::to_string(((int)GetCost(ToCreate)[0])).c_str(), App->font->resourcesPanelFont, { 16, 173, 171,255 }, 20, false, false, false, Panel, nullptr);
				Titaniumnum = App->gui->AddText(145, 550, std::to_string(((int)GetCost(ToCreate)[1])).c_str(), App->font->resourcesPanelFont, { 16, 173, 171,255 }, 20, false, false, false, Panel, nullptr);
				App->gui->RemoveUiElement(NotEnaughResourcesText);
			}
			else {
				CurrentAction = ActionUpgrading;
				ToCreate = ((UiEntityButton*)element)->entity;
				CopperIcon = App->gui->AddImage(20, 550, { 679,501,28,29 }, false, false, false, Panel, nullptr);
				TitaniumIcon = App->gui->AddImage(110, 550, { 641,498,30,31 }, false, false, false, Panel, nullptr);
				Coppernum = App->gui->AddText(55, 550, std::to_string(((int)GetCost(ToCreate)[0])).c_str(), App->font->resourcesPanelFont, { 16, 173, 171,255 }, 20, false, false, false, Panel, nullptr);
				Titaniumnum = App->gui->AddText(145, 550, std::to_string(((int)GetCost(ToCreate)[1])).c_str(), App->font->resourcesPanelFont, { 16, 173, 171,255 }, 20, false, false, false, Panel, nullptr);
				App->gui->RemoveUiElement(NotEnaughResourcesText);
			}
		}
	}
}

const eastl::list<Entity*>& EntityManager::GetEntities()const {
	return entities;
}

bool EntityManager::EnaughResources(AviableEntities toBuild) {
	eastl::array<float,2>EntityCost= BuildCost[(uint)toBuild];
	if (Resources[0] >= EntityCost[0] && Resources[1] >= EntityCost[1])
		return true;
	return false;
}

void EntityManager::PayCost(AviableEntities toPay) {
	eastl::array<float, 2>EntityCost = BuildCost[(uint)toPay];
	Resources[0] -= EntityCost[0];
	Resources[1] -= EntityCost[1];
}

const eastl::array<float, 2> EntityManager::GetCost(AviableEntities Entity)const {
	return BuildCost[(uint)Entity];
}

AiType EntityManager::AviableToAi(AviableEntities aviable) {
	switch (aviable) {
	case AviableEntities::redship:
		return AiType::RedShip;
	case AviableEntities::blueship:
		return AiType::BlueShip;
	case AviableEntities::greenship:
		return AiType::GreenShip;
	case AviableEntities::upgradedredship:
		return AiType::RedShip;
	case AviableEntities::upgradedblueship:
		return AiType::BlueShip;
	case AviableEntities::upgradedgreenship:
		return AiType::GreenShip;
	case AviableEntities::collector:
		return AiType::Collector;
	}
	return AiType::None;
}

const Entity* EntityManager::GetBase() const {
	eastl::list<Entity*>::const_iterator it;
	for (it = entities.cbegin(); it != entities.cend(); ++it) {
		if ((*it)->etype == EntityType::TypeBuilding)
			if (((Building*)(*it))->Btype == BuildingType::Base)
				return (*it);
	}
}

void EntityManager::OnCollision(Collider*c1,Collider*c2) {
	switch (c1->type) {
	case COLLIDER_ALLY_RANGE:
		//disparar cap el ally
		if (!((Ai*)c1->entity)->shooting) {
			App->particle->AddParticle(App->particle->shot, c1->entity->EntityRect.x, c1->entity->EntityRect.y, 10, 0, COLLIDER_ENEMY_PARTICLE, ParticleType::SHOT, ((Ai*)c1->entity)->DirectionAngle, 1.0f, ((Ai*)c1->entity)->Damage, 1000);
			((Ai*)c1->entity)->shooting = true;
		}
		break;
	}
}