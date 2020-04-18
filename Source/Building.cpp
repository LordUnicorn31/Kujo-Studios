#include "EntityManager.h"
#include "Building.h"
#include "j1Input.h"
#include "j1App.h"

Building::Building(BuildingType type, iPoint Position): Entity(EntityType::TypeBuilding, Position), Btype(type) {
	switch (type) {
	case BuildingType::Base:
		MaxHealth = 5000;
		health = 5000;
		HealthRegen = 5.0f;
		selected = false;
		IdleAnimation = &App->entity->Animations.BaseIdle;
		level = 1;
		OnConstruction = true;
		ConstructionTime = 0.0f;
		break;
	case BuildingType::Mine:
		MaxHealth = 500;
		health = 500;
		HealthRegen = 2.5f;
		selected = false;
		IdleAnimation= &App->entity->Animations.MineIdle;
		level = 1;
		ConstructionTime = 5.0f;
		OnConstruction = true;
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
	}
}

void Building::Draw(float dt) {
	if (OnConstruction) {

	}
	else {
		App->render->Blit(sprite, position.x, position.y, &IdleAnimation->GetCurrentFrame(dt));
	}
}

/*void Building::Die() {

}*/

void Building::LevelUp() {

}