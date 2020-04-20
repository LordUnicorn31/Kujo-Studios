#include "Ai.h"

Ai::Ai(AiType type, iPoint Position) : Entity(EntityType::TypeAi, Position),Atype(type) {
	switch (Atype) {
	case AiType::Basic_Unit:
		MaxHealth = 100;
		HealthRegen = 3.0f;
		health = 100;
		Damage = 40;
		Range = 200;
		speed = 100;
		break;
	case AiType::Collector:
		MaxHealth = 50;
		HealthRegen = 1.0f;
		health = 50;
		Damage = 0;
		Range = 100;
		speed = 200;
	}
}

Ai::~Ai() {

}

void Ai::Update(float dt) {

}

void Ai::Draw(float dt) {

}

void Ai::Move() {

}

void Ai::UpdateLogic() {

}