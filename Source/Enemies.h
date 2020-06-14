#pragma once
#include "Module.h"
#include "EASTL/vector.h"
#include "EASTL/list.h"
#include "p2Point.h"
#include "SDL_rect.h"
#include "Animation.h"
#define DURATION 0.0f
#define GROUPSPAWNPRATIO 10.0f

enum class EnemyType {
	none,
	wraith
};
struct SDL_Texture;
class Enemy {
public:
	Enemy(EnemyType type, iPoint Position);
	~Enemy();
	SDL_Rect EnemyRect;
	EnemyType etype;
	float health;
	int MaxHealth;
	SDL_Texture* sprite;
	//Collider* collider;
public:
	//void Die();

	float speed;
	float DirectionAngle;
	//iPoint Destination;
	uint Damage;
	uint Range;
	bool IsMoving;
	bool OnDestination;
	iPoint TilePos;
	iPoint NextTile;
	Animation IdleAnimation;
	eastl::vector<iPoint> path;
	void Update(float dt);
	void Draw(float dt);
	void Move(int x, int y);
	void DoMovement();
	void UpdateMovement();
	void UpdateLogic();
};

class Enemies : public Module
{
public:

	Enemies();

	// Destructor
	virtual ~Enemies();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	void Init();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool DoLogic;
	float AccumulatedTime;
	float UpdateMsCycle;

	//COLLISION CALLBACK
	float EndTime;
	float NextSpawn;
	bool AllSpawned;
	SDL_Texture* EnemySprite;
	eastl::list<Enemy*>enemies;
	void SpawnEnemies();
};