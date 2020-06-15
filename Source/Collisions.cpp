#include "Application.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Module.h"
#include "p2Log.h"
#include "Entity.h"
#include "GameScene.h"
#include "Map.h"

Collisions::Collisions()
{
	name = "collisions";

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_ALLY][COLLIDER_ALLY] = false;
	matrix[COLLIDER_ALLY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ALLY][COLLIDER_ENEMY_PARTICLE] = true;
	matrix[COLLIDER_ALLY][COLLIDER_ALLY_PARTICLE] = false;
	matrix[COLLIDER_ALLY][COLLIDER_ENEMY_RANGE] = false;
	matrix[COLLIDER_ALLY][COLLIDER_ALLY_RANGE] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_ALLY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_PARTICLE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ALLY_PARTICLE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_RANGE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ALLY_RANGE] = false;

	matrix[COLLIDER_ENEMY_PARTICLE][COLLIDER_ALLY] = true;
	matrix[COLLIDER_ENEMY_PARTICLE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_PARTICLE][COLLIDER_ENEMY_PARTICLE] = false;
	matrix[COLLIDER_ENEMY_PARTICLE][COLLIDER_ALLY_PARTICLE] = false;
	matrix[COLLIDER_ENEMY_PARTICLE][COLLIDER_ENEMY_RANGE] = false;
	matrix[COLLIDER_ENEMY_PARTICLE][COLLIDER_ALLY_RANGE] = false;

	matrix[COLLIDER_ALLY_PARTICLE][COLLIDER_ALLY] = false;
	matrix[COLLIDER_ALLY_PARTICLE][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_ALLY_PARTICLE][COLLIDER_ENEMY_PARTICLE] = false;
	matrix[COLLIDER_ALLY_PARTICLE][COLLIDER_ALLY_PARTICLE] = false;
	matrix[COLLIDER_ALLY_PARTICLE][COLLIDER_ENEMY_RANGE] = false;
	matrix[COLLIDER_ALLY_PARTICLE][COLLIDER_ALLY_RANGE] = false;

	matrix[COLLIDER_ENEMY_RANGE][COLLIDER_ALLY] = true;
	matrix[COLLIDER_ENEMY_RANGE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_RANGE][COLLIDER_ENEMY_PARTICLE] = false;
	matrix[COLLIDER_ENEMY_RANGE][COLLIDER_ALLY_PARTICLE] = false;
	matrix[COLLIDER_ENEMY_RANGE][COLLIDER_ENEMY_RANGE] = false;
	matrix[COLLIDER_ENEMY_RANGE][COLLIDER_ALLY_RANGE] = false;

	matrix[COLLIDER_ALLY_RANGE][COLLIDER_ALLY] = false;
	matrix[COLLIDER_ALLY_RANGE][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_ALLY_RANGE][COLLIDER_ENEMY_PARTICLE] = false;
	matrix[COLLIDER_ALLY_RANGE][COLLIDER_ALLY_PARTICLE] = false;
	matrix[COLLIDER_ALLY_RANGE][COLLIDER_ENEMY_RANGE] = false;
	matrix[COLLIDER_ALLY_RANGE][COLLIDER_ALLY_RANGE] = false;
}

// Destructor
Collisions::~Collisions()
{}

void Collisions::Init() {
	enabled = false;
	active = true;
}

bool Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->toDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->callback&&c1->active)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback&&c2->active)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
bool Collisions::Update(float dt)
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void Collisions::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) { //||App->scene->colliders) {
		debug =! debug;
		/*if (App->scene->colliders) {
			App->scene->colliders = false;
		}*/
	}

	if (debug == false) {
		return;
	}
		
	Uint8 alpha = 140;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;
		if (colliders[i]->active) {
			switch (colliders[i]->type)
			{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case COLLIDER_ALLY_RANGE: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_ALLY: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_ENEMY: //red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_ENEMY_RANGE://yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			/*case END_COLLIDER://light blue
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case START_COLLIDER://purple
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
				break;
			case COLLIDER_ENEMY://black
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
				break;*/
			}
		}
	}
}

// Called before quitting
bool Collisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return SDL_HasIntersection(&rect,&r);
}

