#include "EntityManager.h"
#include "Building.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Gui.h"

Building::Building(BuildingType type, iPoint Position): Entity(EntityType::TypeBuilding, { Position.x,Position.y,0,0 }), Btype(type) {
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
		ConstructionTime = 4.0f;
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
		ConstructionTime = 4.0f;
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
		ConstructionTime = 4.0f;
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
		if (ConstructionTime <= 0)
			OnConstruction = false;
	}
	else{
	//level up
	//functionallity
		selectable = true;
	}
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
		App->gui->AddButton(20, 240, { 1344,84,39,39 }, { 1290,83,39,39 }, { 1397,83,39,39 }, true, false, App->entity->Panel, App->entity);
		App->gui->AddButton(60, 240, { 1345,28,39,39 }, { 1291,28,39,39 }, { 1398,28,39,39 }, true, false, App->entity->Panel, App->entity);
		App->gui->AddButton(100, 240, { 1344,199,39,39 }, { 1290,198,39,39 }, { 1397,198,39,39 }, true, false, App->entity->Panel, App->entity);
		break;
	}
}