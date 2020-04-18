#include "Resources.h"

Resource::Resource(ResourceType type,iPoint Position): Entity(EntityType::TypeResource, Position), Rtype(type) {

}

Resource::~Resource() {

}

void Resource::Update(float dt) {

}

void Resource::Draw(float dt) {

}