#include "j1App.h"
#include "j1input.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Module.h"
#include "p2Log.h"
#include "Entity.h"
#include "j1Scene.h"
#include "j1Map.h"

j1Collisions::j1Collisions()
{
	name = "collisions";

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	/*matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_WALL][COLLIDER_DEATH] = false;
	matrix[COLLIDER_WALL][COLLIDER_BACKGROUND] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_PLAYER1][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER1] = false;
	matrix[COLLIDER_PLAYER1][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_BACKGROUND] = true;
	matrix[COLLIDER_PLAYER1][END_COLLIDER] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_DEATH][COLLIDER_WALL] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_BACKGROUND] = false;
	matrix[COLLIDER_DEATH][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_BACKGROUND][COLLIDER_WALL] = false;
	matrix[COLLIDER_BACKGROUND][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_BACKGROUND][COLLIDER_DEATH] = true;

	matrix[END_COLLIDER][COLLIDER_PLAYER1] = true;
	matrix[END_COLLIDER][COLLIDER_ENEMY] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_DEATH] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BACKGROUND] = true;
	matrix[COLLIDER_ENEMY][END_COLLIDER] = false;*/

}

// Destructor
j1Collisions::~j1Collisions()
{}

void j1Collisions::Init() {
	enabled = false;
	active = true;
}

bool j1Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
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
bool j1Collisions::Update(float dt)
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void j1Collisions::DebugDraw()
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
		
/*
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
			case COLLIDER_WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_PLAYER1: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_DEATH: //red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_BACKGROUND://yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case END_COLLIDER://light blue
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case START_COLLIDER://purple
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
				break;
			case COLLIDER_ENEMY://black
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
				break;
			}
		}
	}*/
}

// Called before quitting
bool j1Collisions::CleanUp()
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

Collider* j1Collisions::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
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

