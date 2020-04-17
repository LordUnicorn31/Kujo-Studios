#pragma once
#include "Entity.h"

enum AiType {
	Collector,
	Constructor,
	Basic_Unit
};

class Ai :public Entity {
	Ai();
	~Ai();
	AiType type;
	uint direction;
	float speed;
	iPoint Destination;
	void Update();
	void Draw();
	void Move();
	void UpdateLogic();
};