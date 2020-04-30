#pragma once
#include "Entity.h"
#include "EASTL/vector.h"

struct Animation;

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
	uint Damage;
	uint Range;
	bool IsMoving;
	bool OnDestination;
	iPoint TilePos;
	iPoint FinalGoal;
	iPoint NextTile;
	Animation* IdleAnimaiton;
	eastl::vector<iPoint> path;
	void Update(float dt);
	void Draw(float dt);
	void Move(int x,int y);
	void DoMovement();
	void UpdateMovement();
	void UpdateLogic();
};