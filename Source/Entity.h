#pragma once
#include "EASTL/array.h"
#include "SDL_rect.h"

struct SDL_Texture;
class UiElement;
//class Collider;

enum class EntityType : unsigned char {
	TypeAi,
	TypeBuilding,
	TypeResource
};

class Entity {
public:
	Entity(EntityType type, SDL_Rect entityrect);
	virtual ~Entity();
	SDL_Rect EntityRect;
	EntityType etype;
	float health;
	int MaxHealth;
	SDL_Texture* sprite;
	bool selected;
	bool selectable;
	bool todie;
	//Collider* collider;
	//SDL_Rect entity_rect;
public:
	virtual void Draw(float dt); 
	virtual void Update(float dt);
	virtual void UpdateLogic();
	virtual void UiFunctionallity();
	//virtual void Die();
};