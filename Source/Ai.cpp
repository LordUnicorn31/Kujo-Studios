#include "EntityManager.h"
#include "Ai.h"
#include "Application.h"
#include "PathFinding.h"
#include "Input.h"
#include "Map.h"
#include "Window.h"
#include "Gui.h"
#include "Audio.h"
//#include "Collisions.h"

Ai::Ai(AiType type, iPoint Position) : Entity(EntityType::TypeAi, { Position.x,Position.y,0,0 }), Atype(type), speed(0.0f),  DirectionAngle(270.0f), Damage(0), Range(0), UpgradedDamage(0), UpgradedRange(0), UpgradedSpeed(0.0f), IsMoving(false), OnDestination(true),Armed(false),Working(true),WorkingTime(0.0f),Building(true),BuildingTime(0.0f),TotalBuildingTime(0) {
    switch (Atype) {
	case AiType::RedShip:
        MaxHealth = 100;
		health = (float)MaxHealth;
		Damage = 40;
		Range = 200;
        UpgradedDamage = 50;
        UpgradedRange = 250;
		speed = 5.0f;
        UpgradedSpeed = 6.0f;
		//IdleAnimaiton = App->entity->Animations.AttackShip;
        IdleAnimation.PushBack({ 24,23,66,66 });
        IdleAnimation.PushBack({ 121,21,66,66 });
        IdleAnimation.speed = 2.5f;
        ArmedIdleAnimation.PushBack({ 229,221,79,79 });
        ArmedIdleAnimation.PushBack({ 369,221,79,79 });
        ArmedIdleAnimation.speed = 2.5f;
		selectable = true;
		EntityRect.w = 54;
		EntityRect.h = 51;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
        TotalBuildingTime = 10;
        BuildingTime = 10.0f;
		break;
    case AiType::BlueShip:
        MaxHealth = 60;
        health = (float)MaxHealth;
        Damage = 60;
        Range = 350;
        UpgradedDamage = 75;
        UpgradedRange = 400;
        speed = 6.0f;
        UpgradedSpeed = 7.0f;
        IdleAnimation.PushBack({ 242,28,61,61 });
        IdleAnimation.PushBack({ 377,20,61,61 });
        IdleAnimation.speed = 3.0f;
        ArmedIdleAnimation.PushBack({ 237,110,77,77 });
        ArmedIdleAnimation.PushBack({ 377,110,77,77 });
        ArmedIdleAnimation.speed = 3.0f;
        selectable = true;
        EntityRect.w = 58;
        EntityRect.h = 58;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
        TotalBuildingTime = 10;
        BuildingTime = 10.0f;
        break;
	case AiType::Collector:
        MaxHealth = 50;
        health = (float)MaxHealth;
		Damage = 0;
		Range = 100;
        UpgradedDamage = 0;
        UpgradedRange = 100;
		speed = 3.0f;
        UpgradedSpeed = 4.0f;
        IdleAnimation.PushBack({ 29,147,52,52 });
        IdleAnimation.PushBack({ 131,147,52,52 });
        IdleAnimation.speed = 2.0f;
        ArmedIdleAnimation = IdleAnimation;
		selectable = true;
		EntityRect.w = 46;
		EntityRect.h = 46;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
        TotalBuildingTime = 10;
        BuildingTime = 10.0f;
		break;
    case AiType::GreenShip:
        MaxHealth = 150;
        health = (float)MaxHealth;
        Damage = 100;
        Range = 100;
        UpgradedDamage = 150;
        UpgradedRange = 120;
        UpgradedSpeed = 3.0f;
        speed = 2.0f;
        IdleAnimation.PushBack({ 29,324,57,57 });
        IdleAnimation.PushBack({ 131,324,57,57 });
        IdleAnimation.speed = 1.5f;
        ArmedIdleAnimation.PushBack({ 233,332,80,80 });
        ArmedIdleAnimation.PushBack({ 372,332,80,80 });
        ArmedIdleAnimation.speed = 1.5f;
        selectable = true;
        EntityRect.w = 58;
        EntityRect.h = 58;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
        TotalBuildingTime = 10;
        BuildingTime = 10.0f;
        break;
	}
    //collider = App->collisions->AddCollider(EntityRect, COLLIDER_AI, App->entity);
}

Ai::~Ai() {

}

void Ai::Update(float dt) {
    if (Working) {
        selectable = false;
        WorkingTime -= dt;
        if (WorkingTime <= 0) {
            Working = false;
            selectable = true;
        }
    }

    if (Building) {
        selectable = false;
        BuildingTime -= dt;
        if (BuildingTime <= 0) {
            Building = false;
            selectable = true;
        }
    }
    
    if (!OnDestination)
        UpdateMovement();

    /*if (health < 0)
        die*/
}

void Ai::UpdateLogic() {
    if (IsMoving)
        DoMovement();
}

void Ai::Draw(float dt) {
    //TODO: quan la nau recorre a vegades les diagonals va tremolant al canviar d'angles molt rapid
    if (!Building) {
        if (!Armed)
            App->render->Blit(sprite, EntityRect.x, EntityRect.y, &IdleAnimation.GetCurrentFrame(dt), true, App->render->renderer, (float)App->win->GetScale(), 1.0f, DirectionAngle);
        else
            App->render->Blit(sprite, EntityRect.x, EntityRect.y, &ArmedIdleAnimation.GetCurrentFrame(dt), true, App->render->renderer, (float)App->win->GetScale(), 1.0f, DirectionAngle);
        
        if (selected) {
            App->render->DrawQuad(EntityRect, 0, 255, 0, 255, false);
        }
        for (int i = 0; i != path.size(); ++i) {
            App->render->DrawQuad({ path[i].x * 32,path[i].y * 32,32,32 }, 255, 0, 0, 127, true);
        }
    }
}

void Ai::DoMovement() {
    //state = movestate::movenon
    bool MovementPerformed= false;
    if (NextTile.x < TilePos.x)
    {
        DirectionAngle = 270.0f;
        MovementPerformed = true;
        EntityRect.x -= (int)speed;
        if ((EntityRect.x - NextTile.x * App->map->data.tileWidth) <= 0)
        {
            TilePos.x--;
        }
    }
    else if (NextTile.x > TilePos.x)
    {
        DirectionAngle = 90.0f;
        MovementPerformed = true;
        EntityRect.x += (int)speed;
        if ((EntityRect.x - NextTile.x * App->map->data.tileWidth) >= 0)
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
        EntityRect.y -= (int)speed;
        if ((EntityRect.y - NextTile.y * App->map->data.tileHeight) <= 0)
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
        EntityRect.y += (int)speed;
        if ((EntityRect.y - NextTile.y * App->map->data.tileHeight) >= 0)
        {
            TilePos.y++;
        }
    }

    if (!MovementPerformed) {
        IsMoving = false;
    }
    
}

void Ai::Move(int x, int y) {
    NextTile.x += x;
    NextTile.y += y;
    IsMoving = true;
    //_speed = speed;
}

void Ai::UpdateMovement()
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

    /*if (IsMoving) {

        
        App->audio->PlayFx(App->audio->LoadFx("Resources/audio/fx/spaceshipmov.wav"), -1);
        App->audio->FxVolume(1);
        
    }

    else {
        if (OnDestination == true) App->audio->UnloadFx();
    }*/
    
       
    
        
}

void Ai::UiFunctionallity() {
    switch (Atype) {
    case AiType::Collector:
        //App->gui->AddText(82,240,)
        App->gui->AddEntityButton(20, 240, { 1344,251,39,39 }, { 1290,250,39,39 }, { 1398,251,39,39 },AviableEntities::cuartel,EntityType::TypeBuilding, true, false, false, App->entity->Panel, App->entity);
        App->gui->AddEntityButton(60, 240, { 1346,306,39,39 }, { 1290,305,39,39 }, { 1398,306,39,39 }, AviableEntities::ship_factory, EntityType::TypeBuilding, true, false, false, App->entity->Panel, App->entity);
        App->gui->AddEntityButton(100, 240, { 1645,308,39,39 }, { 1590,307,39,39 }, { 1698,308,39,39 }, AviableEntities::mine, EntityType::TypeBuilding, true, false, false, App->entity->Panel, App->entity);
        App->gui->AddEntityButton(140, 240, { 1645,250,39,39 }, { 1590,249,39,39 }, { 1698,250,39,39 }, AviableEntities::PowerGenerator, EntityType::TypeBuilding, true, false, false, App->entity->Panel, App->entity);
        break;
    }
}

void Ai::Upgrade() {
    Damage = UpgradedDamage;
    Range = UpgradedRange;
    speed = UpgradedSpeed;
    Armed = true;
}