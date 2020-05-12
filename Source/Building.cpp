#include "EntityManager.h"
#include "Building.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Audio.h"

Building::Building(BuildingType type, iPoint Position): Entity(EntityType::TypeBuilding, { Position.x,Position.y,0,0 }), Btype(type) {
	switch (type) {
	case BuildingType::Base:
		EntityRect.w = 64;
		EntityRect.h = 64;
		MaxHealth = 5000;
		health = 5000;
		HealthRegen = 5.0f;
		selected = false;
		IdleAnimation = &App->entity->Animations.Base1Idle;
		ConstructionAnimation = &App->entity->Animations.Base1Idle;
		level = 1;
		OnConstruction = true;
		ConstructionTime = 0.0f;
		cost = { 0,0,0 };
		break;
	case BuildingType::Mine:
		EntityRect.w = 64;
		EntityRect.h = 64;
		MaxHealth = 500;
		health = 500;
		HealthRegen = 2.5f;
		selected = false;
		IdleAnimation= &App->entity->Animations.MineIdle;
		ConstructionAnimation = &App->entity->Animations.BuildMine;
		level = 1;
		ConstructionTime = 4.0f;
		OnConstruction = true;
		cost = { 0,1500,0 };
		break;
	case BuildingType::Cuartel:
		EntityRect.w = 64;
		EntityRect.h = 64;
		MaxHealth = 300;
		health = 300;
		HealthRegen = 2.5f;
		selected = false;
		IdleAnimation = &App->entity->Animations.CuartelIdle;
		ConstructionAnimation = &App->entity->Animations.BuildCuartel;
		level = 1;
		ConstructionTime = 4.0f;
		OnConstruction = true;
		cost = { 0,1500,0 };
		break;
	case BuildingType::Spaceship_factory:
		EntityRect.w = 64;
		EntityRect.h = 64;
		MaxHealth = 400;
		health = 400;
		HealthRegen = 2.5f;
		selected = false;
		IdleAnimation = &App->entity->Animations.LabIdle;
		ConstructionAnimation = &App->entity->Animations.BuildLab;
		level = 1;
		ConstructionTime = 4.0f;
		OnConstruction = true;
		cost = { 0,1500,0 };
		break;
	}
}

Building::~Building() {

}

void Building::Update(float dt) {
	if (health <= 0) {
		//die
	}
	if (health < MaxHealth) {
		health += HealthRegen*dt; // s'ha de mirar
	}
	else {
		health = MaxHealth;
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