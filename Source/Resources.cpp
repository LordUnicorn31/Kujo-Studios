#include "Resources.h"

Resource::Resource(ResourceType type, iPoint Position) : Entity(EntityType::TypeResource, {Position.x,Position.y,0,0}), Rtype(type) {

}

Resource::~Resource() {

}

void Resource::Update(float dt) {

}

void Resource::Draw(float dt) {

}