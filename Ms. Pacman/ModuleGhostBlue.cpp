#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleGhostBlue.h"
#include "ModuleBackground_Map1.h"
#include "ModuleAudio.h"
#include <time.h>
#include <stdlib.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleGhostBlue::ModuleGhostBlue()
{
	test = { 3, 120, 1, 1 };

	position.x = 105; //105
	position.y = 99;
	
	// collision
	enemy_collision = App->collision->AddCollider({ 50, 50, 8, 8 }, COLLIDER_ENEMY, this);
	
	// right animation
	right.PushBack({ 1, 112, 14, 14 });
	right.PushBack({ 17, 112, 14, 14 });
	right.speed = 0.10f;

	// left animation
	left.PushBack({ 113, 112, 14, 14 });
	left.PushBack({ 97, 112, 14, 14 });
	left.speed = 0.10f;

	// up animation
	up.PushBack({ 65, 112, 14, 14 });
	up.PushBack({ 81, 112, 14, 14 });
	up.speed = 0.10f;

	// down animation
	down.PushBack({ 33, 112, 14, 14 });
	down.PushBack({ 49, 112, 14, 14 });
	down.speed = 0.10f;

	// vulnerable animation
	vulnerable.PushBack({ 1, 127, 14, 14 });
	vulnerable.PushBack({ 17, 127, 14, 14 });
	vulnerable.speed = 0.10f;

}

ModuleGhostBlue::~ModuleGhostBlue()
{}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading blue ghost textures");
	bool ret = true;
	graphics = App->textures->Load("Pac-man & Ghosts.png");
	prev_anim = &up;

	srand(time(NULL));

	tmp = rand() % 2 + 1;

	if (tmp == 1)
	{
		go_left = true;
	}
	else if (tmp == 2)
	{
		go_right = true;
	}


	return ret;

}

// Update: draw background
update_status ModuleGhostBlue::Update()
{
	Animation* current_animation = prev_anim;

	Uint32 now = SDL_GetTicks() - start_time;

	////Random direction --------------------------------

	srand(time(NULL));

	// What is the next tile
	// right
	if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_right = true;
		}
	}
	else{ can_go_right = false; }

	// left
	if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_left = true;
		}
	}
	else{ can_go_left = false; }

	// up
	if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_up = true;
		}
	}
	else{ can_go_up = false; }

	// down
	if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_down = true;
		}
	}
	else{ can_go_down = false; }

	// Is the player on an intersection and on the right pixel ?
	if (can_go_left == true || can_go_right == true)
	{
		if (can_go_up == false && can_go_down == false)
		{
			change_direction = false;
		}
		else
		{
			change_direction = true;
		}
	}
	if (can_go_up == true || can_go_down == true)
	{
		if (can_go_left == false && can_go_right == false)
		{
			change_direction = false;
		}
		else
		{
			change_direction = true;
		}
	}
	else{ change_direction = false; }

	//choose direction
	if (change_direction)
	{
		cont = false;
		while (cont == false)
		{
			tmp = rand() % 4 + 1;
			if (can_go_right && tmp == 1)
			{
				position.y = (p_mid.y * 8) + 4 + 7;
				ghost_right = true; cont = true;
			}
			else{ ghost_right = false; }

			if (can_go_left && tmp == 2)
			{
				position.y = (p_mid.y * 8) + 4 + 7;
				ghost_left = true; cont = true;
			}
			else{ ghost_left = false; }

			if (can_go_up && tmp == 3)
			{
				position.x = (p_mid.x * 8) + 4 - 7;
				ghost_up = true; cont = true;
			}
			else{ ghost_up = false; }

			if (can_go_down && tmp == 4)
			{
				position.x = (p_mid.x * 8) + 4 - 7;
				ghost_down = true; cont = true;
			}
			else{ ghost_down = false; }
		}
	}



	// Player tile collision detectors ------------------------------
	p_up.x = (position.x + 7) / 8;
	p_up.y = (position.y - 4) / 8;

	p_down.x = (position.x + 7) / 8;
	p_down.y = (position.y - 11) / 8;

	p_left.x = (position.x + 10) / 8;
	p_left.y = (position.y - 7) / 8;

	p_right.x = (position.x + 3) / 8;
	p_right.y = (position.y - 7) / 8;

	p_mid.x = (position.x + 6) / 8;
	p_mid.y = (position.y - 7) / 8;

	// Movement ---------------------------------------
	int speed = 1;
	if (1)
	{
		if (total_time <= now)
		{
			if (ghost_right) // right
			{
				// What is the next tile
				if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4 || (position.y - 7) == (p_mid.y * 8) + 3 || (position.y - 7) == (p_mid.y * 8) + 5 || (position.y - 7) == (p_mid.y * 8) + 2 || (position.y - 7) == (p_mid.y * 8) + 6 || go_left == true)
					{
						position.y = (p_mid.y * 8) + 4 + 7; // Re-position to the center of the tile
						go_right = true; go_left = false; go_up = false; go_down = false;
					}
				}
			}
			if (ghost_left) // left
			{
				// What is the next tile
				if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4 || (position.y - 7) == (p_mid.y * 8) + 3 || (position.y - 7) == (p_mid.y * 8) + 5 || (position.y - 7) == (p_mid.y * 8) + 2 || (position.y - 7) == (p_mid.y * 8) + 6 || go_right == true)
					{
						position.y = (p_mid.y * 8) + 4 + 7;  // Re-position to the center of the tile
						go_left = true; go_right = false; go_up = false; go_down = false;
					}
				}
			}
			if (ghost_up) // up
			{
				// What is the next tile
				if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if ((position.x + 7) == (p_mid.x * 8) + 4 || (position.x + 7) == (p_mid.x * 8) + 3 || (position.x + 7) == (p_mid.x * 8) + 5 || (position.x + 7) == (p_mid.x * 8) + 2 || (position.x + 7) == (p_mid.x * 8) + 6 && (position.y - 7) == (p_mid.y * 8) + 4 || go_down == true)
					{
						position.x = (p_mid.x * 8) + 4 - 7;  // Re-position to the center of the tile
						go_up = true; go_right = false; go_left = false; go_up = true; go_down = false;
					}
				}
			}
			if (ghost_down) // down
			{
				// What is the next tile
				if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if ((position.x + 7) == (p_mid.x * 8) + 4 || (position.x + 7) == (p_mid.x * 8) + 3 || (position.x + 7) == (p_mid.x * 8) + 5 || (position.x + 7) == (p_mid.x * 8) + 2 || (position.x + 7) == (p_mid.x * 8) + 6 && (position.y - 7) == (p_mid.y * 8) + 4 || go_up == true)
					{
						position.x = (p_mid.x * 8) + 4 - 7;  // Re-position to the center of the tile
						go_down = true; go_right = false; go_left = false; go_up = false;
					}
				}
			}

			if (go_right)
			{
				// What is the next tile
				if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
				{
					right.speed = 0.25f;
					current_animation = &right;
					position.x += speed;

					go_left = false; go_up = false; go_down = false;
				}
				else
					right.speed = 0.0f;
			}
			if (go_left)
			{
				// What is the next tile
				if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
				{
					left.speed = 0.25f;
					current_animation = &left;
					position.x -= speed;
					go_right = false; go_up = false; go_down = false;
				}
				else
					left.speed = 0.0f;
			}
			if (go_up)
			{
				// What is the next tile
				if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
				{
					up.speed = 0.25f;
					current_animation = &up;
					position.y -= speed;
					go_right = false; go_left = false; go_down = false;
				}
				else
					up.speed = 0.0f;
			}
			if (go_down)
			{
				// What is the next tile
				if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
				{
					down.speed = 0.25f;
					current_animation = &down;
					position.y += speed;
					go_right = false; go_left = false; go_up = false;
				}
				else
					down.speed = 0.0f;
			}
		}
		else{ left.speed = 0.0f; }
	}
	else{}



	// Draw everything --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &vulnerable;
	}
	else
	{
		current_animation = &up;
	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;
	App->render->Blit(graphics, position.x, position.y + DISTANCEM1 - r.h, &r);

	App->render->Blit(graphics, (position.x +7), (position.y - 7) + DISTANCEM1, &test, 1.0f); //
	App->render->Blit(graphics, (p_mid.x * 8) + 4, (p_mid.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //
	App->render->Blit(graphics, (p_up.x * 8) + 4, (p_up.y * 8  + DISTANCEM1) + 4, &test, 1.0f); //
	App->render->Blit(graphics, (p_down.x * 8) + 4, (p_down.y * 8  + DISTANCEM1) + 4, &test, 1.0f); //
	App->render->Blit(graphics, (p_left.x * 8) + 4, (p_left.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //
	App->render->Blit(graphics, (p_right.x * 8) + 4, (p_right.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //

	if (enemy_collision->to_delete == true){
		position.x = 105;
		position.y = 99;
	}

	return UPDATE_CONTINUE;
}