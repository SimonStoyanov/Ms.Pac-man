#include <iostream>
#include <random>
using namespace std;

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

ModuleGhostBlue::ModuleGhostBlue()
{
	test = { 3, 120, 1, 1 };

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

	//end of vulnerable
	vulnerable_end.PushBack({ 1, 127, 14, 14 });
	vulnerable_end.PushBack({ 17, 127, 14, 14 });
	vulnerable_end.PushBack({ 33, 127, 14, 14 });
	vulnerable_end.PushBack({ 49, 127, 14, 14 });
	vulnerable_end.speed = 0.10f;

	total_time_vuln = (Uint32)(time_vulnerable * 0.5f * 1000.0f);
	total_time = (Uint32)(time_stoped * 0.5f * 1000.0f);

}

ModuleGhostBlue::~ModuleGhostBlue()
{
	enemy_collision = nullptr;
}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading blue ghost textures");
	bool ret = true;
	graphics = App->textures->Load("Pac-man & Ghosts.png");
	prev_anim = &up;

	srand(time(NULL) * 10003);

	tmp = rand() % 2 + 1;

	if (tmp == 1)
	{
		go_left = true;
	}
	else if (tmp == 2)
	{
		go_right = true;
	}

	enemy_collision = App->collision->AddCollider({ 50, 50, 8, 8 }, COLLIDER_BLUE, this);

	return ret;

}

// Update: draw background
update_status ModuleGhostBlue::Update()
{
	Animation* current_animation = prev_anim;

	now = SDL_GetTicks() - App->player->start_time;

	// Collision ------------
	enemy_collision->SetPos(position.x+4, position.y+14);

	//Random direction ----------------------------------------

	srand(time(NULL));

	// What is the next tile --------------
	// right
	if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_right = true;
		}
		else{ can_go_right = false; }
	}
	else{ can_go_right = false; }

	// left
	if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_left = true;
		}
		else{ can_go_left = false; }
	}
	else{ can_go_left = false; }

	// up
	if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_up = true;
		}
		else{ can_go_up = false; }
	}
	else{ can_go_up = false; }

	// down
	if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
	{
		if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_down = true;
		}
		else{ can_go_down = false; }
	}
	else{ can_go_down = false; }

	// Is the player on an intersection?
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


	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 5);

	// Choose direction Radom -------------------
	if (change_direction)
	{
		cont = false;
		while (cont == false)
		{
			tmp = dis(gen);
	

			if (can_go_right && (tmp == 4 || tmp == 5))
			{
				ghost_right = true; cont = true; change_direction = false;
			}
			else{ ghost_right = false; }

			if (can_go_left && tmp == 2)
			{
				ghost_left = true; cont = true; change_direction = false;
			}
			else{ ghost_left = false; }

			if (can_go_up && tmp == 3)
			{
				ghost_up = true; cont = true; change_direction = false;
			}
			else{ ghost_up = false; }

			if (can_go_down && tmp == 1)
			{
				ghost_down = true; cont = true; change_direction = false;
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
	if (now >= total_time)
	{
		if (1)
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
				if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27 || position.x >= 210)
				{
					right.speed = 0.25f;

					if (!is_vulnerable)
					{
						current_animation = &right;
					}

					if (position.x >= 220)
					{
						position.x = -10;
					}

					position.x += speed;

					go_left = false; go_up = false; go_down = false;
				}
			}
			if (go_left)
			{
				// What is the next tile
				if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27 || position.x <= 0)
				{
					left.speed = 0.25f;

					if (!is_vulnerable)
					{
						current_animation = &left;
					}

					if (position.x <= -10)
					{
						position.x = 220;
					}

					position.x -= speed;
					go_right = false; go_up = false; go_down = false;
				}
			}
			if (go_up)
			{
				// What is the next tile
				if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
				{
					up.speed = 0.25f;

					if (!is_vulnerable)
					{
						current_animation = &up;
					}

					position.y -= speed;
					go_right = false; go_left = false; go_down = false;
				}
			}
			if (go_down)
			{
				// What is the next tile
				if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
				{
					down.speed = 0.25f;

					if (!is_vulnerable)
					{
						current_animation = &down;
					}

					position.y += speed;
					go_right = false; go_left = false; go_up = false;
				}
			}
		}
	}
	else{}


	//Ghost vulnerable animation control -----------------
	if (is_vulnerable &&  now > total_time_vuln + passed_time)
	{
		is_vulnerable = false;
	}
	else if (is_vulnerable && (total_time_vuln + passed_time) - now < 3.0f * 0.5f * 1000.0)
	{
		current_animation = &vulnerable_end;
	}
	else if (is_vulnerable && (total_time_vuln + passed_time) - now < 1.0f * 0.5f * 1000.0)
	{
		vulnerable_end.speed = 0.20f;
	}
	else if (is_vulnerable &&  now < total_time_vuln + passed_time)
	{
		current_animation = &vulnerable;
	}




	// Draw everything --------------------------------------

	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;
	App->render->Blit(graphics, position.x, position.y + DISTANCEM1 - r.h, &r);

	//App->render->Blit(graphics, (position.x +7), (position.y - 7) + DISTANCEM1, &test, 1.0f); //
	//App->render->Blit(graphics, (p_mid.x * 8) + 4, (p_mid.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_up.x * 8) + 4, (p_up.y * 8  + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_down.x * 8) + 4, (p_down.y * 8  + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_left.x * 8) + 4, (p_left.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_right.x * 8) + 4, (p_right.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //

	if (enemy_collision->to_delete == true){
		position.x = 105;
		position.y = 99;
	}

	return UPDATE_CONTINUE;
}
