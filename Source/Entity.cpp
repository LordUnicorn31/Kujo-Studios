#include "Entity.h"

Entity::Entity(EntityType type, iPoint Position): etype(type), sprite(nullptr), position(Position) {}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::Draw() {

}

/*void Entity::Die() {

}*/