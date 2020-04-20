#include "EntityManager.h"
#include "Ai.h"
#include "j1App.h"

Ai::Ai(AiType type, iPoint Position) : Entity(EntityType::TypeAi, Position),Atype(type) {
	switch (Atype) {
	case AiType::Basic_Unit:
		MaxHealth = 100;
		HealthRegen = 3.0f;
		health = 100;
		Damage = 40;
		Range = 200;
		speed = 100;
		IdleAnimaiton = &App->entity->Animations.AttackShip;
		cost = { 1,50,0 };
	case AiType::Collector:
		MaxHealth = 50;
		HealthRegen = 1.0f;
		health = 50;
		Damage = 0;
		Range = 100;
		speed = 200;
		IdleAnimaiton = &App->entity->Animations.FarmerShip;
		cost = { 1,50,0 };
	}
}

Ai::~Ai() {

}

void Ai::Update(float dt) {
	if (selected) {
		App->render->DrawQuad({ position.x,position.y,size,size }, 255, 255, 255, 255);
	}
}

void Ai::Draw(float dt) {
	App->render->Blit(sprite, position.x, position.y, &IdleAnimaiton->GetCurrentFrame(dt));
}

void Ai::Move() {

}

void Ai::UpdateLogic() {

}