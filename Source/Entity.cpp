#include "Entity.h"

Entity::Entity(EntityType type, iPoint Position): etype(type), sprite(nullptr), position(Position),selectable (false) {}

Entity::~Entity() {

}

void Entity::Update(float dt) {

}

void Entity::Draw(float dt) {

}

/*void Entity::Die() {

}*/