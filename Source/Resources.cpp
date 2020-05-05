#include "EntityManager.h"
#include "Resources.h"

Resource::Resource(ResourceType type, iPoint Position) : Entity(EntityType::TypeResource, {Position.x,Position.y,32,32}), Rtype(type) {

}

Resource::~Resource() {

}

void Resource::Update(float dt) {

}

void Resource::Draw(float dt) {
	App->render->Blit(sprite, EntityRect.x, EntityRect.y);
}