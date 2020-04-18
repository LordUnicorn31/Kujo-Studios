#include "Building.h"

Building::Building(BuildingType type, iPoint Position): Entity(EntityType::TypeBuilding, Position), Btype(type) {
	switch (type) {
	case BuildingType::Base:
		health = 5000;
		selected = false;
		tile_size = 64;
		level = 1;
		break;
	case BuildingType::Mine:
		health = 500;
		selected = false;
		tile_size = 64;
		level = 1;
		break;
	}
}

Building::~Building() {

}

void Building::Update() {

}

void Building::Draw() {

}

/*void Building::Die() {

}*/

void Building::OnConstruction() {

}