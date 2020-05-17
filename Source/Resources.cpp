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
	Building* Mine;
	eastl::list<Entity*>::const_iterator it;
	for (it = App->entity->GetEntities().cbegin(); it != App->entity->GetEntities().cend(); ++it) {
		if ((*it)->etype != EntityType::TypeBuilding)
			continue;
		if (((Building*)(*it))->Btype == BuildingType::Mine) {
			Mine = (Building*)(*it);
			if (SDL_HasIntersection(&Mine->EntityRect, &EntityRect) && Mine->selectable) {
				switch (Rtype) {
				case ResourceType::Gold:
					if(Mine->StorageCT[0] != Mine->MaxStorage)
						++Mine->StorageCT[0];
					break;
				case ResourceType::Ore:
					if (Mine->StorageCT[1] != Mine->MaxStorage)
						++Mine->StorageCT[1];
					break;
				}
			}
		}
	}
}

void Resource::Draw(float dt) {
	App->render->Blit(sprite, EntityRect.x, EntityRect.y);
}