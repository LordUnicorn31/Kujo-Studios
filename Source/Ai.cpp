#include "EntityManager.h"
#include "Ai.h"
#include "j1App.h"
#include "j1Pathfinding.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Window.h"
#include "j1Gui.h"

Ai::Ai(AiType type, iPoint Position) : Entity(EntityType::TypeAi, { Position.x,Position.y,0,0 }), Atype(type), IsMoving(false), DirectionAngle(270.0f),Armed(false),Working(false),WorkingTime(0.0f) {
	switch (Atype) {
	case AiType::Basic_Unit:
        MaxHealth = 100;
		health = MaxHealth;
		Damage = 40;
		Range = 200;
		speed = 5;
		IdleAnimaiton = &App->entity->Animations.AttackShip;
        ArmedIdleAnimation = &App->entity->Animations.ArmedAttackShip;
        CostCopperTitanium = { 50,0 };
		selectable = true;
		EntityRect.w = 54;
		EntityRect.h = 51;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
		break;
    case AiType::Ranged_Unit:
        MaxHealth = 60;
        health = MaxHealth;
        Damage = 60;
        Range = 350;
        speed = 6;
        IdleAnimaiton = &App->entity->Animations.AttackShip2;
        ArmedIdleAnimation = &App->entity->Animations.ArmedAttackShip2;
        CostCopperTitanium = { 80,0 };
        selectable = true;
        EntityRect.w = 58;
        EntityRect.h = 58;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
        break;
	case AiType::Collector:
        MaxHealth = 50;
        health = MaxHealth;
		Damage = 0;
		Range = 100;
		speed = 3;
		IdleAnimaiton = &App->entity->Animations.FarmerShip;
        ArmedIdleAnimation = &App->entity->Animations.FarmerShip;
        CostCopperTitanium = { 50,0 };
		selectable = true;
		EntityRect.w = 46;
		EntityRect.h = 46;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
		break;
    case AiType::Special_Unit:
        MaxHealth = 150;
        health = MaxHealth;
        Damage = 100;
        Range = 100;
        speed = 2;
        IdleAnimaiton = &App->entity->Animations.SpecialShip;
        ArmedIdleAnimation = &App->entity->Animations.ArmedSpecialShip;
        CostCopperTitanium = { 150,10 };
        selectable = true;
        EntityRect.w = 58;
        EntityRect.h = 58;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
        break;
	}
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
    
    if (!OnDestination)
        UpdateMovement();

    if (health < 0)
        health = MaxHealth;
}

void Ai::UpdateLogic() {
    if (IsMoving)
        DoMovement();
    health -= 0.7f;
}

void Ai::Draw(float dt) {
    //TODO: quan la nau recorre a vegades les diagonals va tremolant al canviar d'angles molt rapid
    if(!Armed)
        App->render->Blit(sprite, EntityRect.x, EntityRect.y, &IdleAnimaiton->GetCurrentFrame(dt),true,App->render->renderer,App->win->GetScale(),1.0f,DirectionAngle);
    else
        App->render->Blit(sprite, EntityRect.x, EntityRect.y, &ArmedIdleAnimation->GetCurrentFrame(dt), true, App->render->renderer, App->win->GetScale(), 1.0f, DirectionAngle);
	if (selected) {
		App->render->DrawQuad(EntityRect, 0, 255, 0, 255,false);
	}
    for (int i = 0; i != path.size(); ++i) {
        App->render->DrawQuad({path[i].x*32,path[i].y*32,32,32}, 255, 0, 0, 127,true);
    }
}

void Ai::DoMovement() {
    //state = movestate::movenon
    bool MovementPerformed= false;
    if (NextTile.x < TilePos.x)
    {
        DirectionAngle = 270.0f;
        MovementPerformed = true;
        EntityRect.x -= speed;
        if ((EntityRect.x - NextTile.x * App->map->data.tile_width) <= 0)
        {
            TilePos.x--;
        }
    }
    else if (NextTile.x > TilePos.x)
    {
        DirectionAngle = 90.0f;
        MovementPerformed = true;
        EntityRect.x += speed;
        if ((EntityRect.x - NextTile.x * App->map->data.tile_width) >= 0)
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
        EntityRect.y -= speed;
        if ((EntityRect.y - NextTile.y * App->map->data.tile_height) <= 0)
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
        EntityRect.y += speed;
        if ((EntityRect.y - NextTile.y * App->map->data.tile_height) >= 0)
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
}

void Ai::UiFunctionallity() {
    switch (Atype) {
    case AiType::Collector:
        App->gui->AddEntityButton(20, 240, { 1344,251,39,39 }, { 1290,250,39,39 }, { 1398,251,39,39 },AviableEntities::cuartel,EntityType::TypeBuilding, true, false, App->entity->Panel, App->entity);
        App->gui->AddEntityButton(60, 240, { 1346,306,39,39 }, { 1290,305,39,39 }, { 1398,306,39,39 }, AviableEntities::ship_factory, EntityType::TypeBuilding, true, false, App->entity->Panel, App->entity);
        App->gui->AddEntityButton(100, 240, { 1645,308,39,39 }, { 1590,307,39,39 }, { 1698,308,39,39 }, AviableEntities::mine, EntityType::TypeBuilding, true, false, App->entity->Panel, App->entity);
        App->gui->AddEntityButton(140, 240, { 1645,250,39,39 }, { 1590,249,39,39 }, { 1698,250,39,39 }, AviableEntities::PowerGenerator, EntityType::TypeBuilding, true, false, App->entity->Panel, App->entity);
        break;
    }
}