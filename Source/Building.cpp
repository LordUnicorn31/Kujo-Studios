#include "EntityManager.h"
#include "Building.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Gui.h"
#include "Ai.h"

Building::Building(BuildingType type, iPoint Position): Entity(EntityType::TypeBuilding, { Position.x,Position.y,0,0 }), Btype(type),BuildingEntity(nullptr),BuildHUD(nullptr) {
	switch (type) {
	case BuildingType::Base:
		EntityRect.w = 64;
		EntityRect.h = 64;
		health = 5000;
		selected = false;
		IdleAnimation = &App->entity->Animations.Base1Idle;
		ConstructionAnimation = &App->entity->Animations.Base1Idle;
		level = 1;
		OnConstruction = true;
		ConstructionTime = 0.0f;
		CostCopperTitanium = {0,0 };
		break;
	case BuildingType::Mine:
		EntityRect.w = 64;
		EntityRect.h = 64;
		health = 500;
		selected = false;
		IdleAnimation= &App->entity->Animations.MineIdle;
		ConstructionAnimation = &App->entity->Animations.BuildMine;
		level = 1;
		ConstructionTime = 10.0f;
		OnConstruction = true;
		CostCopperTitanium = { 1500,0 };
		break;
	case BuildingType::Cuartel:
		EntityRect.w = 64;
		EntityRect.h = 64;
		health = 300;
		selected = false;
		IdleAnimation = &App->entity->Animations.CuartelIdle;
		ConstructionAnimation = &App->entity->Animations.BuildCuartel;
		level = 1;
		ConstructionTime = 10.0f;
		OnConstruction = true;
		CostCopperTitanium = { 1500,0 };
		break;
	case BuildingType::Spaceship_factory:
		EntityRect.w = 64;
		EntityRect.h = 64;
		health = 400;
		selected = false;
		IdleAnimation = &App->entity->Animations.LabIdle;
		ConstructionAnimation = &App->entity->Animations.BuildLab;
		level = 1;
		ConstructionTime = 10.0f;
		OnConstruction = true;
		CostCopperTitanium = { 1500,0 };
		break;
	case BuildingType::PowerGenerator:
		EntityRect.w = 64;
		EntityRect.h = 64;
		health = 400;
		selected = false;
		IdleAnimation = &App->entity->Animations.PowerGeneratorIdle;
		ConstructionAnimation = &App->entity->Animations.BuildPowerGenerator;
		level = 1;
		ConstructionTime = 10.0f;
		OnConstruction = true;
		CostCopperTitanium = { 1500,0 };
		break;
	}
}

Building::~Building() {

}

void Building::Update(float dt) {
	if (health <= 0) {
		//die
	}

	if (OnConstruction) {
		selectable = false;
		ConstructionTime -= dt;
		if (ConstructionTime <= 0) {
			OnConstruction = false;
			selectable = true;
		}
	}
	if (!BuildingQueue.empty()) {
		if (BuildingEntity == nullptr) {
			if (ToBuild)
				BuildingEntity = (Ai*)App->entity->CreateEntity(BuildingQueue.front(), iPoint(EntityRect.x, EntityRect.y));
		}
		else if (!BuildingEntity->Building) {
			BuildingQueue.pop_front();
			BuildingEntity = (Ai*)App->entity->CreateEntity(BuildingQueue.front(), iPoint(EntityRect.x, EntityRect.y));
			if (BuildingQueue.empty()) {
				ToBuild = false;
				BuildingEntity = nullptr;
			}
		}
	}
	//IF I DIE, KILL THE ENTITY IM BUILDING
}

void Building::Draw(float dt) {
	if (OnConstruction) {
		//App->audio->PlayFx(App->audio->LoadFx("Resources/audio/fx/Building.wav"));
		App->render->Blit(sprite, EntityRect.x, EntityRect.y, &ConstructionAnimation->GetCurrentFrame(dt));
	}
	else {
		App->render->Blit(sprite, EntityRect.x, EntityRect.y, &IdleAnimation->GetCurrentFrame(dt));
		if (selected) {
			App->render->DrawQuad(EntityRect, 0, 255, 0, 255, false);
		}
	}
	if (selected) {
		App->render->DrawQuad(EntityRect, 0, 255, 0, 255, false);
	}
}

/*void Building::Die() {

}*/

void Building::LevelUp() {

}

void Building::UiFunctionallity() {
	switch (Btype) {
	case BuildingType::Cuartel:
		App->gui->AddEntityButton(20, 240, { 1344,84,39,39 }, { 1290,83,39,39 }, { 1397,83,39,39 },AviableEntities::redship, EntityType::TypeAi, true, false, App->entity->Panel, App->entity);
		App->gui->AddEntityButton(60, 240, { 1345,28,39,39 }, { 1291,28,39,39 }, { 1397,28,39,39 }, AviableEntities::blueship, EntityType::TypeAi, true, false, App->entity->Panel, App->entity);
		App->gui->AddEntityButton(100, 240, { 1344,199,39,39 }, { 1290,198,39,39 }, { 1397,198,39,39 }, AviableEntities::greenship, EntityType::TypeAi, true, false, App->entity->Panel, App->entity);
		if (!BuildingQueue.empty()) {
			switch (BuildingEntity->Atype) {
			case AiType::Basic_Unit:
				BuildHUD = App->gui->AddHUDBar(9, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
				break;
			case AiType::Ranged_Unit:
				BuildHUD = App->gui->AddHUDBar(49, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
				break;
			case AiType::Special_Unit:
				BuildHUD = App->gui->AddHUDBar(89, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
				break;
			}
		}
		break;
	case BuildingType::Base:
		App->gui->AddEntityButton(20, 240, { 1344,136,39,39 }, { 1291,135,39,39 }, { 1397,136,39,39 },AviableEntities::collector, EntityType::TypeAi, true, false, App->entity->Panel, App->entity);
		if(!BuildingQueue.empty())
			BuildHUD = App->gui->AddHUDBar(9,281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
		break;
	}
}

void Building::UpdateUiFunctionallity() {
	App->gui->RemoveUiElement(BuildHUD);
	switch (Btype) {
	case BuildingType::Base:
		if (!BuildingQueue.empty())
			BuildHUD = App->gui->AddHUDBar(9, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
		break;
	case BuildingType::Cuartel:
		if (!BuildingQueue.empty()) {
			switch (BuildingEntity->Atype) {
			case AiType::Basic_Unit:
				BuildHUD = App->gui->AddHUDBar(9, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
				break;
			case AiType::Ranged_Unit:
				BuildHUD = App->gui->AddHUDBar(49, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
				break;
			case AiType::Special_Unit:
				BuildHUD = App->gui->AddHUDBar(89, 281, BuildingEntity->TotalBuildingTime, &BuildingEntity->BuildingTime, false, { 1279,431,61,5 }, { 1279,399,61,5 }, { 1278,382,64,8 }, false, false, App->entity->Panel, nullptr);
				break;
			}
		}
	}
}