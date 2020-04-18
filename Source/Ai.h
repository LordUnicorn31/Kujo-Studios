#pragma once
#include "Entity.h"

enum class AiType : unsigned char {
	Collector,
	Constructor,
	Basic_Unit
};

class Ai :public Entity {
public:
	Ai(AiType type, iPoint Position);
	~Ai();
	AiType Atype;
	uint direction;
	float speed;
	iPoint Destination;
	void Update(float dt);
	void Draw(float dt);
	void Move();
	void UpdateLogic();
};