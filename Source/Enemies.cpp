#include "Application.h"
#include "Enemies.h"
#include "EntityManager.h"
#include "Map.h"
#include "Textures.h"
#include "Pathfinding.h"
#include "Entity.h"
#include "Collisions.h"
#include "Particles.h"
#include "Input.h"
#include "GameScene.h"


Enemies::Enemies() : Module(), UpdateMsCycle((1.0f / 60.0f)), AccumulatedTime(0.0f)
{
	name = "Enemies";
}

// Destructor
Enemies::~Enemies()
{
}


// Called before render is available
bool Enemies::Awake(pugi::xml_node& config)
{
	bool ret = true;
	return ret;
}

void Enemies::Init() {
	active = true;
	enabled = false;
}

// Called before the first frame
bool Enemies::Start()
{
    EnemySprite = App->tex->Load("Resources/entities/ships/evil_ships.png");
    AllSpawned = false;
	EndTime = DURATION;
	NextSpawn = GROUPSPAWNPRATIO;
	return true;
}

// Called each loop iteration
bool Enemies::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Enemies::Update(float dt)
{
    if(App->scene->tutorialActive)
    {

    if (EndTime > 0) {
        NextSpawn -= dt;
        EndTime -= dt;
        if (NextSpawn <= 0) {
            SpawnEnemies();
            NextSpawn = GROUPSPAWNPRATIO;
        }
    }
    else {
        AllSpawned = true;
    }
    AccumulatedTime += (dt);
    if (AccumulatedTime >= UpdateMsCycle)
        DoLogic = true;
    eastl::list<Enemy*>::iterator it;
    for (it = enemies.begin(); it != enemies.end(); ++it) {
        (*it)->Update(dt);
        if (DoLogic)
            (*it)->UpdateLogic();
        (*it)->Draw(dt);
    }
    eastl::list<Enemy*>::iterator i = enemies.begin();
    while (i != enemies.end()) {
        if ((*i)->todie) {
            Enemy* todestroy = (*i);
            ++i;
            DestroyEnemy(todestroy);
        }
        else
            ++i;
    }
    if (DoLogic == true) {
        AccumulatedTime = 0.0f;
        DoLogic = false;
    }
    }
    return true;
}

void Enemies::DestroyEnemy(Enemy*enemy) {
    eastl::list<Enemy*>::iterator it = eastl::find(enemies.begin(), enemies.end(), enemy);
    if (it != enemies.end()) {
        delete (*it);
        enemies.erase(it);
    }
}

// Called each loop iteration
bool Enemies::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool Enemies::CleanUp()
{
    App->tex->UnLoad(EnemySprite);
	return true;
}

void Enemies::SpawnEnemies() {
    Enemy* enemy = nullptr;
    enemy = new Enemy(EnemyType::wraith,App->map->MapToWorld(64,10));
    enemies.push_back(enemy);
    enemy = new Enemy(EnemyType::wraith, App->map->MapToWorld(80, 86));
    enemies.push_back(enemy);
    enemy = new Enemy(EnemyType::wraith, App->map->MapToWorld(56, 79));
    enemies.push_back(enemy);
    enemy = new Enemy(EnemyType::wraith, App->map->MapToWorld(34, 73));
    enemies.push_back(enemy);
}

void Enemies::OnCollision(Collider* c1, Collider* c2) {
    switch (c1->type) {
    case COLLIDER_ENEMY_RANGE:
        //disparar cap el ally
        if (!c1->enemy->shooting) {
            App->particle->AddParticle(App->particle->shot, c1->enemy->EnemyRect.x, c1->enemy->EnemyRect.y, 10, 0, COLLIDER_ENEMY_PARTICLE, ParticleType::SHOT, c1->enemy->DirectionAngle, 1.0f,c1->enemy->Damage, 1000);
            c1->enemy->shooting = true;
        }
        break;
    }
}





Enemy::Enemy(EnemyType type,iPoint Position):etype(type),todie(false),shooting(false){
    switch (type) {
    case EnemyType::wraith:
        EnemyRect = { Position.x,Position.y,65,65 };
        MaxHealth = 400;
        health = MaxHealth;
        sprite = App->enemies->EnemySprite;
        speed = 2.0f;
        Damage = 50;
        Range = 200;
        IsMoving = false;
        OnDestination = false;
        TilePos = App->map->WorldToMap(EnemyRect.x, EnemyRect.y);
        NextTile = TilePos;
        IdleAnimation.PushBack({ 30, 494, 65, 65 });
        IdleAnimation.PushBack({ 154, 494, 65, 65 });
        IdleAnimation.speed = 1.5f;
        App->pathfinding->CreatePath(App->map->WorldToMap(EnemyRect.x, EnemyRect.y), App->map->WorldToMap(App->entity->GetBase()->EntityRect.x, App->entity->GetBase()->EntityRect.y));
        path = *App->pathfinding->GetLastPath();
        rechargetime = 1.0f;
        currentcharge = rechargetime;
        collider = App->collisions->AddCollider(EnemyRect, COLLIDER_ENEMY, App->enemies,nullptr,this);
        rangecollider = App->collisions->AddCollider({ EnemyRect.x + EnemyRect.w/2 - Range/2, EnemyRect.y + EnemyRect.h/2 - Range/2, Range, Range }, COLLIDER_ENEMY_RANGE, App->enemies,nullptr,this);
        break;
    }
}

Enemy::~Enemy() {}

void Enemy::Update(float dt) {

    if (!OnDestination)
        UpdateMovement();

    /*if (App->input->GetKey(SDL_SCANCODE_1) == KEY_UP)
        health = 0;
    if (health <= 0) {
        todie = true;
        if (collider != nullptr)
            collider->toDelete = true;
        if (rangecollider != nullptr)
            rangecollider->toDelete = true;
    }*/

    if (shooting) {
        currentcharge -= dt;
        if (currentcharge <= 0) {
            currentcharge = rechargetime;
            shooting = false;
        }
    }
        
}

void Enemy::UpdateLogic() {
    if (IsMoving && !shooting)
        DoMovement();
}

void Enemy::Draw(float dt) {
    //TODO: quan la nau recorre a vegades les diagonals va tremolant al canviar d'angles molt rapid
    App->render->Blit(sprite, EnemyRect.x, EnemyRect.y, &IdleAnimation.GetCurrentFrame(dt), true, App->render->renderer, App->win->GetScale(), 1.0f, DirectionAngle);    
    /* TO DRAW THE ENEMIES PATH ON SCREEN
    for (int i = 0; i != path.size(); ++i) {
        App->render->DrawQuad({ path[i].x * 32,path[i].y * 32,32,32 }, 255, 0, 0, 127, true);
    }*/
}

void Enemy::DoMovement() {
    //state = movestate::movenon
    bool MovementPerformed = false;
    if (NextTile.x < TilePos.x)
    {
        DirectionAngle = 270.0f;
        MovementPerformed = true;
        EnemyRect.x -= speed;
        if ((EnemyRect.x - NextTile.x * App->map->data.tileWidth) <= 0)
        {
            TilePos.x--;
        }
    }
    else if (NextTile.x > TilePos.x)
    {
        DirectionAngle = 90.0f;
        MovementPerformed = true;
        EnemyRect.x += speed;
        if ((EnemyRect.x - NextTile.x * App->map->data.tileWidth) >= 0)
        {
            TilePos.x++;
        }
    }
    if (NextTile.y < TilePos.y)
    {
        if (MovementPerformed && DirectionAngle == 90.0f) {
            DirectionAngle = 45.0f;
        }
        else if (MovementPerformed && DirectionAngle == 270.0f) {
            DirectionAngle = 315.0f;
        }
        else
            DirectionAngle = 0.0f;
        MovementPerformed = true;
        EnemyRect.y -= speed;
        if ((EnemyRect.y - NextTile.y * App->map->data.tileHeight) <= 0)
        {
            TilePos.y--;
        }
    }
    else if (NextTile.y > TilePos.y)
    {
        if (MovementPerformed && DirectionAngle == 90.0f) {
            DirectionAngle = 135.0f;
        }
        else if (MovementPerformed && DirectionAngle == 270.0f) {
            DirectionAngle = 225.0f;
        }
        else
            DirectionAngle = 180.0f;
        MovementPerformed = true;
        EnemyRect.y += speed;
        if ((EnemyRect.y - NextTile.y * App->map->data.tileHeight) >= 0)
        {
            TilePos.y++;
        }
    }

    if (!MovementPerformed) {
        IsMoving = false;
    }
    else {
        collider->SetPos(EnemyRect.x, EnemyRect.y);
        rangecollider->SetPos(EnemyRect.x + EnemyRect.w/2 - Range/2, EnemyRect.y + EnemyRect.h/2 - Range/2);
    }
}

void Enemy::Move(int x, int y) {
    NextTile.x += x;
    NextTile.y += y;
    IsMoving = true;
    //_speed = speed;
}

void Enemy::UpdateMovement()
{
    if (!IsMoving) {

        if (!path.empty())
        {
            //TODO: Update units walkabilitiy position in the pathfinder
            int wantedXTile = path[0].x;
            int wantedYTile = path[0].y;

            if (TilePos.x < wantedXTile)
            {
                Move(1, 0);
            }
            else if (TilePos.x > wantedXTile)
            {
                Move(-1, 0);
            }
            if (TilePos.y < wantedYTile)
            {
                Move(0, 1);
            }
            else if (TilePos.y > wantedYTile)
            {
                Move(0, -1);
            }

            path.erase(path.begin());
            if (path.empty()) {
                /*if (App->pathfinding->CreatePath(_goalX, _goalY) !=- 1)
                    path = App->pathfinding->GetLastPath();*/
                    //TODO: Arreglar aquest if i el que calgui de aquesta classe per el correcte funcionament del group movement
            }
        }
        else
        {
            OnDestination = true;
        }
    }
}
