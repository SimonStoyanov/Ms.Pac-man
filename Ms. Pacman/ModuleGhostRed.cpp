#include <iostream>
#include <random>
using namespace std;

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"+
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleBackground_Map3.h"
#include "ModuleBackground_Map4.h"
#include "ModuleAudio.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

ModuleGhostRed::ModuleGhostRed()
{
	test = { 3, 75, 3, 3 };

	// right animation
	right.PushBack({ 1, 66, 14, 15 });
	right.PushBack({ 17, 66, 14, 15 });
	right.speed = 0.10f;

	// left animation
	left.PushBack({ 113, 66, 14, 15 });
	left.PushBack({ 97, 66, 14, 15 });
	left.speed = 0.10f;

	// up animation
	up.PushBack({ 65, 66, 14, 15 });
	up.PushBack({ 81, 66, 14, 15 });
	up.speed = 0.10f;

	// down animation
	down.PushBack({ 33, 66, 14, 15 });
	down.PushBack({ 49, 66, 14, 15 });
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

	// Dead animations
	dead_up.PushBack({ 65, 129, 12, 5 });
	dead_left.PushBack({ 95, 130, 12, 5 });
	dead_right.PushBack({ 65, 135, 12, 5 });
	dead_downs.PushBack({ 81, 129, 12, 5 });

	total_time_vuln = (Uint32)(time_vulnerable * 0.5f * 1000.0f);
	total_time = (Uint32)(time_stoped * 0.5f * 1000.0f);

}

ModuleGhostRed::~ModuleGhostRed()
{
	enemy_collision = nullptr;
}

bool ModuleGhostRed::CleanUp()
{
	LOG("Red ghost CleanUp");
	App->textures->Unload(graphics);

	ghost_down = false; 
	ghost_left = false; 
	ghost_right = true; 
	ghost_up = false;
	go_right = false; go_left = false; go_up = false; go_down = false;
	is_dead = false;
	passed_time = 0;

	left.speed = 0.0f;
	right.speed = 0.0f;
	up.speed = 0.10f;
	down.speed = 0.0f;

	return true;
}

// Load assets
bool ModuleGhostRed::Start()
{
	LOG("Loading red ghost textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Pac-man & Ghosts.png");
	prev_anim = &up;

	srand(time(NULL) * 754);

	//Starting random direction
	tmp = rand() % 2 + 1;

	if (tmp == 1)
	{
		ghost_left = true;
	}
	else if (tmp == 2)
	{
		ghost_right = true;
	}

	enemy_collision = App->collision->AddCollider({ 50, 50, 8, 8 }, COLLIDER_RED, this);

	return ret;

}

// Update: draw background
update_status ModuleGhostRed::Update()
{
	if (!is_dead)
	{
		if (App->player->two_players)
		{
			if (abs(sqrt(((App->player->position.x - position.x) * (App->player->position.x - position.x)) + (App->player->position.y - position.y) * (App->player->position.y - position.y))) < abs(sqrt(((App->player2->position.x - position.x) * (App->player2->position.x - position.x)) + (App->player2->position.y - position.y) * (App->player2->position.y - position.y))))
			{
				p_position_x = App->player->position.x;
				p_position_y = App->player->position.y;
			}
			else
			{
				p_position_x = App->player2->position.x;
				p_position_y = App->player2->position.y;
			}
		}
		else
		{
			p_position_x = App->player->position.x;
			p_position_y = App->player->position.y;
		}
	}
	// Dead targeting -------------------
	else if (position.y == 99 && (position.x > 85 && position.x < 150) && App->map2->IsEnabled())
	{
		p_position_x = 105;
		p_position_y = 99;
		pre_find = false;
	}
	// Dead targeting -------------------
	else if ((position.y == 99 && (position.x > 78 || position.x < 120)) && !App->map2->IsEnabled())
	{
		p_position_x = 105;
		p_position_y = 99;
		pre_find = false;
	}

	if (is_dead && !dead_positioning && pre_find)
	{
		if (App->map1->IsEnabled() || App->map4->IsEnabled())
		{
			if (position.x > 105)
			{
				p_position_x = 119;
				p_position_y = 99;
				pre_find = false;
			}
			else if (position.x < 105)
			{
				p_position_x = 79;
				p_position_y = 99;
				pre_find = false;
			}
		}
		else if (App->map2->IsEnabled())
		{
			if (position.x > 105)
			{
				p_position_x = 75;
				p_position_y = 90;
				pre_find = false;
			}
			else if (position.x < 105)
			{
				p_position_x = 145;
				p_position_y = 95;
				pre_find = false;
			}
		}
		else if (App->map3->IsEnabled())
		{
			if (position.x > 105)
			{
				p_position_x = 65;
				p_position_y = 120;
				pre_find = false;
			}
			else if (position.x < 105)
			{
				p_position_x = 140;
				p_position_y = 120;
				pre_find = false;
			}
		}
	}

	if (position.x > 104 && position.x < 106 && position.y > 98 && position.y < 100 && is_dead && !dead_positioning && is_dead)
	{
		position.x = 105;
		position.y = 99;
		dead_positioning = true;
		pre_find = true;
	}


	// ----------------------------------
	if (is_dead)
	{
		speed = 1.0f;
		is_vulnerable = false;
	}

	Animation* current_animation = prev_anim;

	now = SDL_GetTicks() - App->player->start_time;

	// Collision ------------
	enemy_collision->SetPos(position.x + 4, position.y + 14);

	if (App->player->can_see_paths)
		App->render->Blit(graphics, (p_position_x + 6), (p_position_y - 8) + DISTANCEM1, &test, 1.0f);

	// What is the next tile --------------
	// right
	if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
	{
		if (((int)position.x + 7) == (p_mid.x * 8) + 4 && ((int)position.y - 7) >= (p_mid.y * 8) + 3 && ((int)position.y - 7) <= (p_mid.y * 8) + 5)
		{
			can_go_right = true;
		}
		else can_go_right = false; 
	}
	else can_go_right = false; 

	// left
	if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
	{
		if (((int)position.x + 7) == (p_mid.x * 8) + 4 && ((int)position.y - 7) >= (p_mid.y * 8) + 3 && ((int)position.y - 7) <= (p_mid.y * 8) + 5)
		{
			can_go_left = true;
		}
		else{ can_go_left = false; }
	}
	else can_go_left = false; 

	// up
	if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
	{
		if (((int)position.x + 7) >= (p_mid.x * 8) + 3 && ((int)position.x + 7) <= (p_mid.x * 8) + 5 && ((int)position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_up = true;
		}
		else can_go_up = false; 
	}
	else can_go_up = false; 

	// down
	if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
	{
		if (((int)position.x + 7) >= (p_mid.x * 8) + 3 && ((int)position.x + 7) <= (p_mid.x * 8) + 5 && ((int)position.y - 7) == (p_mid.y * 8) + 4)
		{
			can_go_down = true;
		}
		else can_go_down = false; 
	}
	else can_go_down = false; 

	// Is the player on an intersection change direction ------------------
	if (can_go_left == true || can_go_right == true)
	{
		if (can_go_up == false && can_go_down == false)
		{
			change_direction = false;
		}
		else
			change_direction = true;
		
	}
	if (can_go_up == true || can_go_down == true)
	{
		if (can_go_left == false && can_go_right == false)
		{
			change_direction = false;
		}
		else
			change_direction = true;
	}
	else change_direction = false; 

	// Ghosts follows the player

	if (App->player->ghost_random == false || is_dead)
	{
		if (is_vulnerable == false)
		{
			// Want to go to the player / Where is the target -----------------------------
			if (p_position_x + 7 > position.x) //is right
			{
				if (position.y > p_position_y - 7) // is up
				{
					if (position.y - p_position_y - 7 > p_position_x + 7 - position.x)
					{
						want_go_up = true; want_go_down = false; want_go_left = false; want_go_right = false;
					}
					else{ want_go_right = true;  want_go_up = false; want_go_down = false; want_go_left = false; }
				}
				else // is down 
				{
					if (p_position_y - 7 - position.y > p_position_x + 7 - position.x)
					{
						want_go_down = true; want_go_left = false; want_go_right = false; want_go_up = false;
					}
					else{ want_go_right = true;  want_go_up = false; want_go_down = false; want_go_left = false; }
				}
			}
			else // is left
			{
				if (position.y > p_position_y - 7) // is up
				{
					if (position.y - p_position_y - 7 > position.x - p_position_x + 7)
					{
						want_go_up = true;  want_go_down = false; want_go_left = false; want_go_right = false;
					}
					else{ want_go_left = true; want_go_right = false;  want_go_up = false; want_go_down = false; }
				}
				else // is down 
				{
					if (p_position_y - 7 - position.y > position.x - p_position_x + 7)
					{
						want_go_down = true; want_go_left = false; want_go_right = false; want_go_up = false;
					}
					else{ want_go_left = true; want_go_right = false;  want_go_up = false; want_go_down = false; }
				}
			}
		}
		else
		{
			// Want to escape from the player / Where is the target -----------------------------
			if (p_position_x + 7 > position.x) //is right
			{
				if (position.y > p_position_y - 7) // is up
				{
					if (position.y - p_position_y - 7 > p_position_x + 7 - position.x)
					{
						want_go_up = false; want_go_down = true; want_go_left = false; want_go_right = false;
					}
					else{ want_go_right = false;  want_go_up = false; want_go_down = false; want_go_left = true; }
				}
				else // is down 
				{
					if (p_position_y - 7 - position.y > p_position_x + 7 - position.x)
					{
						want_go_down = false; want_go_left = false; want_go_right = false; want_go_up = true;
					}
					else{ want_go_right = false;  want_go_up = false; want_go_down = false; want_go_left = true; }
				}
			}
			else // is left
			{
				if (position.y > p_position_y - 7) // is up
				{
					if (position.y - p_position_y - 7 > position.x - p_position_x + 7)
					{
						want_go_up = false;  want_go_down = true; want_go_left = false; want_go_right = false;
					}
					else{ want_go_left = false; want_go_right = true;  want_go_up = false; want_go_down = false; }
				}
				else // is down 
				{
					if (p_position_y - 7 - position.y > position.x - p_position_x + 7)
					{
						want_go_down = false; want_go_left = false; want_go_right = false; want_go_up = true;
					}
					else{ want_go_left = false; want_go_right = true;  want_go_up = false; want_go_down = false; }
				}
			}
		}

		// Choose direction ----------------------------
		if (change_direction)
		{
			if (want_go_right) // try go right
			{
				if (can_go_right && !ghost_left)
				{
					ghost_right = true; ghost_left = false; ghost_up = false; ghost_down = false;
				}
				else if (can_go_up && can_go_down)
				{
					if (position.y > p_position_y - 7)
					{
						ghost_up = true; ghost_down = false; ghost_left = false; ghost_right = false;
					}
					else{ ghost_down = true; ghost_left = false; ghost_right = false; ghost_up = false; }
				}
				else if (can_go_up && !ghost_down)
				{
					ghost_up = true; ghost_down = false; ghost_left = false; ghost_right = false;
				}
				else if (can_go_down && !ghost_up)
				{
					ghost_down = true; ghost_left = false; ghost_right = false; ghost_up = false;
				}
				else{ ghost_left = true; ghost_right = false; ghost_up = false; ghost_down = false; }
			}

			//-------
			else if (want_go_left) // try go left
			{
				if (can_go_left && !ghost_right)
				{
					ghost_left = true; ghost_right = false; ghost_up = false; ghost_down = false;
				}
				else if (can_go_up && can_go_down)
				{
					if (position.y > p_position_y - 7)
					{
						ghost_up = true; ghost_down = false; ghost_left = false; ghost_right = false;
					}
					else{ ghost_down = true; ghost_left = false; ghost_right = false; ghost_up = false; }
				}
				else if (can_go_up && !ghost_down)
				{
					ghost_up = true; ghost_down = false; ghost_left = false; ghost_right = false;
				}
				else if (can_go_down && !ghost_up)
				{
					ghost_down = true; ghost_left = false; ghost_right = false; ghost_up = false;
				}
				else{ ghost_right = true; ghost_left = false; ghost_up = false; ghost_down = false; }
			}

			//-------
			else if (want_go_up) // try go up
			{
				if (can_go_up && !ghost_down)
				{
					ghost_up = true; ghost_down = false; ghost_left = false; ghost_right = false;
				}
				else if (can_go_left && can_go_right)
				{
					if (position.x > p_position_x + 7)
					{
						ghost_left = true; ghost_right = false; ghost_up = false; ghost_down = false;
					}
					else{ ghost_right = true; ghost_left = false; ghost_up = false; ghost_down = false; }
				}
				else if (can_go_left && !ghost_right)
				{
					ghost_left = true; ghost_right = false; ghost_up = false; ghost_down = false;
				}
				else if (can_go_right && !ghost_left)
				{
					ghost_right = true; ghost_left = false; ghost_up = false; ghost_down = false;
				}
				else{ ghost_down = true; ghost_up = false; ghost_right = false; ghost_left = false; }
			}

			//-------
			else if (want_go_down) // try go down
			{
				if (can_go_down && !ghost_up)
				{
					ghost_down = true; ghost_up = false; ghost_right = false; ghost_left = false;
				}
				else if (can_go_left && can_go_right)
				{
					if (position.x > p_position_x + 7)
					{
						ghost_left = true; ghost_right = false; ghost_up = false; ghost_down = false;
					}
					else{ ghost_right = true; ghost_left = false; ghost_up = false; ghost_down = false; }
				}
				else if (can_go_left && !ghost_right)
				{
					ghost_left = true; ghost_right = false; ghost_up = false; ghost_down = false;
				}
				else if (can_go_right && !ghost_left)
				{
					ghost_right = true; ghost_left = false; ghost_up = false; ghost_down = false;
				}
				else{ ghost_up = true; ghost_down = false; ghost_left = false; ghost_right = false; }
			}
		}
	}

	// Ghost random ----------
	else
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(1, 4);

		// Choose direction Radom -------------------
		if (change_direction)
		{
			cont = false;
			while (cont == false)
			{
				tmp = dis(gen);

				if (can_go_right && tmp == 4)
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

				if (can_go_down && (tmp == 1))
				{
					position.x = (p_mid.x * 8) + 4 - 7;
					ghost_down = true; cont = true;
				}
				else{ ghost_down = false; }
			}
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
	if (!App->player->is_dead)
	{
		if (dead_positioning && !App->player->pause && is_dead)
		{
			is_vulnerable = false;
			if (dead_down)
			{
				if (position.y < 120)
				{
					current_animation = &dead_downs;
					position.y += 0.5f;
				}
				else{ dead_down = false; }
			}
			else
			{
				if (position.y > 99)
				{
					position.y -= 0.3f;
					current_animation = &up;
				}
				else
				{
					is_dead = false;
					dead_positioning = false;
					dead_down = true;

					ghost_down = false;
					ghost_left = false;
					ghost_right = true;
					ghost_up = false;
					go_right = false; go_left = false; go_up = false; go_down = false;
				}
			}
		}
		else if (now >= total_time)
		{
			// What direction are we changing
			if (speed != 0)
			{
				if (ghost_right) // right
				{
					// What is the next tile
					if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
					{
						position.y = (p_mid.y * 8) + 4 + 7; // Re-position to the center of the tile
						go_right = true; go_left = false; go_up = false; go_down = false;
					}
				}
				if (ghost_left) // left
				{
					// What is the next tile
					if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
					{
						position.y = (int)(p_mid.y * 8) + 4 + 7;  // Re-position to the center of the tile
						go_left = true; go_right = false; go_up = false; go_down = false;
					}
				}
				if (ghost_up) // up
				{
					// What is the next tile
					if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
					{
						position.x = (int)(p_mid.x * 8) + 4 - 7;  // Re-position to the center of the tile
						go_up = true; go_right = false; go_left = false; go_up = true; go_down = false;
					}
				}
				if (ghost_down) // down
				{
					// What is the next tile
					if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
					{
						position.x = (int)(p_mid.x * 8) + 4 - 7;  // Re-position to the center of the tile
						go_down = true; go_right = false; go_left = false; go_up = false;
					}
				}

				// Slow speed when vulnerable
				if (is_vulnerable && !App->player->pause)
				{
					speed = 0.6f;
				}


				// Move
				if (go_right)
				{
					// What is the next tile
					if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27 || position.x >= 210)
					{
						right.speed = 0.25f;

						if (!is_vulnerable){ current_animation = &right; }

						if (position.x >= 220){ position.x = -10; }
						if (is_dead){ current_animation = &dead_right; }

						position.x += speed + extra_speed;

						go_left = false; go_up = false; go_down = false;
					}
				}
				if (go_left)
				{
					// What is the next tile
					if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27 || position.x <= 0)
					{
						left.speed = 0.25f;

						if (!is_vulnerable){ current_animation = &left; }
						if (is_dead){ current_animation = &dead_left; }

						if (position.x <= -10){ position.x = 220; }

						position.x -= speed + extra_speed;

						go_right = false; go_up = false; go_down = false;
					}
				}
				if (go_up)
				{
					// What is the next tilec
					if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
					{
						up.speed = 0.25f;

						if (!is_vulnerable)
						{
							current_animation = &up;
						}
						if (is_dead){ current_animation = &dead_up; }

						position.y -= speed + extra_speed;

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
						if (is_dead){ current_animation = &dead_downs; }

						position.y += speed + extra_speed;

						go_right = false; go_left = false; go_up = false;
					}
				}
			}
			else{ down.speed = 0; up.speed = 0; left.speed = 0; right.speed = 0; }
		}
		else{}
	}
	else{ down.speed = 0; up.speed = 0; left.speed = 0; right.speed = 0; }


	//Ghost vulnerable animation control -----------------
	if (is_vulnerable &&  now > total_time_vuln + passed_time + 1200.0f)
	{
		is_vulnerable = false;
		App->player->eaten_ghost = 0;
		App->player2->eaten_ghost = 0;
	}
	else if (is_vulnerable && (total_time_vuln + passed_time + 100.0f) - now < 4.0f * 0.5f * 1000.0)
	{
		current_animation = &vulnerable_end;
	}
	else if (is_vulnerable && (total_time_vuln + passed_time + 100.0f) - now < 1.0f * 0.5f * 1000.0)
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
	if (can_see){ App->render->Blit(graphics, position.x, position.y + DISTANCEM1 - r.h, &r);}

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
