#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	// Player
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BLUE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ORANGE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PINK] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_RED] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FRUIT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TELEPORT] = true;

	// Blue Ghost
	matrix[COLLIDER_BLUE][COLLIDER_ORANGE] = false;
	matrix[COLLIDER_BLUE][COLLIDER_PINK] = false;
	matrix[COLLIDER_BLUE][COLLIDER_RED] = true;
	matrix[COLLIDER_BLUE][COLLIDER_FRUIT] = false;
	matrix[COLLIDER_BLUE][COLLIDER_TELEPORT] = true;
	matrix[COLLIDER_BLUE][COLLIDER_PLAYER] = true;

	// Orange Ghost
	matrix[COLLIDER_ORANGE][COLLIDER_BLUE] = false;
	matrix[COLLIDER_ORANGE][COLLIDER_PINK] = false;
	matrix[COLLIDER_ORANGE][COLLIDER_RED] = true;
	matrix[COLLIDER_ORANGE][COLLIDER_FRUIT] = false;
	matrix[COLLIDER_ORANGE][COLLIDER_TELEPORT] = true;
	matrix[COLLIDER_ORANGE][COLLIDER_PLAYER] = true;

	// Pink Ghost
	matrix[COLLIDER_PINK][COLLIDER_BLUE] = false;
	matrix[COLLIDER_PINK][COLLIDER_ORANGE] = false;
	matrix[COLLIDER_PINK][COLLIDER_RED] = true;
	matrix[COLLIDER_PINK][COLLIDER_FRUIT] = false;
	matrix[COLLIDER_PINK][COLLIDER_TELEPORT] = true;
	matrix[COLLIDER_PINK][COLLIDER_PLAYER] = true;

	// Red Ghost
	matrix[COLLIDER_RED][COLLIDER_BLUE] = false;
	matrix[COLLIDER_RED][COLLIDER_ORANGE] = false;
	matrix[COLLIDER_RED][COLLIDER_PINK] = true;
	matrix[COLLIDER_RED][COLLIDER_FRUIT] = false;
	matrix[COLLIDER_RED][COLLIDER_TELEPORT] = true;
	matrix[COLLIDER_RED][COLLIDER_PLAYER] = true;

	// Fruits
	matrix[COLLIDER_FRUIT][COLLIDER_FRUIT] = false;
	matrix[COLLIDER_FRUIT][COLLIDER_BLUE] = false;
	matrix[COLLIDER_FRUIT][COLLIDER_ORANGE] = false;
	matrix[COLLIDER_FRUIT][COLLIDER_PINK] = false;
	matrix[COLLIDER_FRUIT][COLLIDER_RED] = false;
	matrix[COLLIDER_FRUIT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FRUIT][COLLIDER_TELEPORT] = true;

	// Teleport
	matrix[COLLIDER_TELEPORT][COLLIDER_TELEPORT] = false;
	matrix[COLLIDER_TELEPORT][COLLIDER_BLUE] = true;
	matrix[COLLIDER_TELEPORT][COLLIDER_ORANGE] = true;
	matrix[COLLIDER_TELEPORT][COLLIDER_PINK] = true;
	matrix[COLLIDER_TELEPORT][COLLIDER_RED] = true;
	matrix[COLLIDER_TELEPORT][COLLIDER_FRUIT] = true;
	matrix[COLLIDER_TELEPORT][COLLIDER_PLAYER] = true;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
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

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
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

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);  
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_BLUE: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ORANGE: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PINK: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_RED: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_FRUIT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_TELEPORT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
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

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
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

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}