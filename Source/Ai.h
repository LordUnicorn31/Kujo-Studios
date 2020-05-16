#pragma once
#include "Entity.h"
#include "EASTL/vector.h"

struct Animation;

enum class AiType : unsigned char {
	Collector,
	Basic_Unit,
	Ranged_Unit,
	Special_Unit
};

class Ai :public Entity {
public:
	Ai(AiType type, iPoint Position);
	~Ai();
	AiType Atype;
	float speed;
	float DirectionAngle;
	//iPoint Destination;
	uint Damage;
	uint Range;
	bool IsMoving;
	bool OnDestination;
	bool Armed;
	bool Working;
	float WorkingTime;
	bool Building;
	float BuildingTime;
	int TotalBuildingTime;

	//GunExtraDamage
	iPoint TilePos;
	//iPoint FinalGoal;
	iPoint NextTile;
	Animation* IdleAnimaiton;
	Animation* ArmedIdleAnimation;
	//TODO:Si pot ser que no cada entity guardi el seu path per tema de memoria (o com a minima k nomes guardin path per ajuntarse i surtir del grup i que no guardin el path compartit) //Podem donarlis una id per group i id 0 implica a cap grup
	eastl::vector<iPoint> path;
	void Update(float dt);
	void Draw(float dt);
	void Move(int x,int y);
	void DoMovement();
	void UpdateMovement();
	void UpdateLogic();
	void UiFunctionallity();
};