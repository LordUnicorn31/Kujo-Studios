#include "EntityManager.h"
#include "Resources.h"
#include "Building.h"

Resource::Resource(ResourceType type, iPoint Position) : Entity(EntityType::TypeResource, {Position.x,Position.y,32,32}), Rtype(type) {
}

Resource::~Resource() {

}

void Resource::Update(float dt) {

}

void Resource::UpdateLogic() {
	eastl::list<Entity*>::const_iterator it;
	for (it = App->entity->GetEntities().cbegin(); it != App->entity->GetEntities().cend(); ++it) {
		if ((*it)->etype != EntityType::TypeBuilding)
			continue;
		if (((Building*)(*it))->Btype == BuildingType::Mine) {
			if (SDL_HasIntersection(&(*it)->EntityRect, &EntityRect) && (*it)->selectable) {
				switch (Rtype) {
				case ResourceType::Gold:
					if (App->entity->Resources[0] < MAXRESOURCES)
						App->entity->Resources[0] += 0.01f;
					break;
				case ResourceType::Ore:
					if (App->entity->Resources[1] < MAXRESOURCES)
						App->entity->Resources[1] += 0.01f;
					break;
				}
			}
		}
	}
}

void Resource::Draw(float dt) {
	App->render->Blit(sprite, EntityRect.x, EntityRect.y);
}