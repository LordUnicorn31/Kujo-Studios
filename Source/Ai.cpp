#include "EntityManager.h"
#include "Ai.h"
#include "j1App.h"
#include "j1Pathfinding.h"
#include "j1Input.h"
#include "j1Map.h"

Ai::Ai(AiType type, iPoint Position) : Entity(EntityType::TypeAi, { Position.x,Position.y,0,0 }), Atype(type), IsMoving(false) {
	switch (Atype) {
	case AiType::Basic_Unit:
		MaxHealth = 100;
		HealthRegen = 3.0f;
		health = 100;
		Damage = 40;
		Range = 200;
		speed = 5;
		IdleAnimaiton = &App->entity->Animations.AttackShip;
		cost = { 1,50,0 };
		selectable = true;
		EntityRect.w = 58;
		EntityRect.h = 58;
        TilePos = App->map->WorldToMap(EntityRect.x, EntityRect.y);
        NextTile = TilePos;
        OnDestination = true;
		break;
	case AiType::Collector:
		MaxHealth = 50;
		HealthRegen = 1.0f;
		health = 50;
		Damage = 0;
		Range = 100;
		speed = 3;
		IdleAnimaiton = &App->entity->Animations.FarmerShip;
		cost = { 1,50,0 };
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
    if (selected && App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) {
        int xTile, yTile;
        App->input->GetMousePosition(xTile,yTile);
        xTile -= App->render->camera.x;
        yTile -= App->render->camera.y;
        iPoint MouseTile(App->map->WorldToMap(xTile,yTile));

        if (TilePos != MouseTile) {
            //path = App->pathfinding->FindPath(MouseTile);
            if (App->pathfinding->CreatePath(TilePos, MouseTile) != -1) {
                path = *App->pathfinding->GetLastPath();
                FinalGoal.x = path.back().x;
                FinalGoal.y = path.back().y;
                path.erase(path.begin());
                OnDestination = false;
            }
        }
    }

    if (!OnDestination)
        UpdateMovement();
}

void Ai::UpdateLogic() {
    if (IsMoving)
        DoMovement();
}

void Ai::Draw(float dt) {
	App->render->Blit(sprite, EntityRect.x, EntityRect.y, &IdleAnimaiton->GetCurrentFrame(dt));
	if (selected) {
		App->render->DrawQuad(EntityRect, 0, 255, 0, 255,false);
	}
}

void Ai::DoMovement() {
    if (NextTile.x < TilePos.x)
    {
        EntityRect.x -= speed;
        if ((EntityRect.x - NextTile.x * App->map->data.tile_width) <= 0)
        {
            TilePos.x--;
        }
    }
    else if (NextTile.x > TilePos.x)
    {
        EntityRect.x += speed;
        if ((EntityRect.x - NextTile.x * App->map->data.tile_width) >= 0)
        {
            TilePos.x++;
        }
    }
    else if (NextTile.y < TilePos.y)
    {
        EntityRect.y -= speed;
        if ((EntityRect.y - NextTile.y * App->map->data.tile_height) <= 0)
        {
            TilePos.y--;
        }
    }
    else if (NextTile.y > TilePos.y)
    {
        EntityRect.y += speed;
        if ((EntityRect.y - NextTile.y * App->map->data.tile_height) >= 0)
        {
            TilePos.y++;
        }
    }
    else
    {
        IsMoving = false;
    }
}

void Ai::Move(int x, int y) {
    NextTile.x = TilePos.x + x;
    NextTile.y = TilePos.y + y;
    IsMoving = true;
    //_speed = speed;
}

void Ai::UpdateMovement()
{
    if (!IsMoving) {

        if (!path.empty())
        {
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
            else if (TilePos.y < wantedYTile)
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
            }
        }
        else
        {
            OnDestination = true;
        }
    }
}