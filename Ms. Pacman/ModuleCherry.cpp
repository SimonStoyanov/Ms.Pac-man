#include <iostream>
#include <random>
using namespace std;

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleCherry.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleBackground_Map3.h"
#include "ModuleAudio.h"
#include <time.h>
#include <stdlib.h>

ModuleCherry::ModuleCherry()
{
	// Cherry Animation
	cherry = { 1, 2, 12, 12 };
	strawberry = { 17, 3, 11, 11 };
	orange = { 33, 2, 12, 12 };
	apple = { 62, 2, 12, 12 };

	test = { 69, 6, 1, 1 };
}

ModuleCherry::~ModuleCherry()
{
	fruit_collision = nullptr;
}

bool ModuleCherry::CleanUp()
{
	LOG("Blue ghost CleanUp");

	App->textures->Unload(graphics);

	
	return true;
}

// Load assets
bool ModuleCherry::Start()
{
	LOG("Loading fruitt textures");
	bool ret = true;
	graphics = App->textures->Load("Fruits.png");

	fruit_collision = App->collision->AddCollider({ position.x, position.y, 10, 10 }, COLLIDER_FRUIT, this);

	count = 0;
	return ret;
}

// Update: draw background
update_status ModuleCherry::Update()
{
	// Cherry appears when 23 seconds passed je
	if (App->player->now - passed_cherry > 25 * (0.5f * 1000.0f) && !App->player->is_dead) 
	{
		p_position_x = 0;
		p_position_y = 147;
		speed = 0.8f;
		if (!App->player->pause){
			play_audio = true;
		}
	}
	else
	{
		position.x = 270;
		position.y = 75;
		speed = 0;
		go_left = true;
		play_audio = false;
	}
	if (position.x > 210 && App->player->now - passed_cherry > 25 * (0.5f * 1000.0f))
	{
		position.x -= 0.8f;
	}
	if (App->player->now - passed_cherry > 30 * (0.5f * 1000.0f))
	{
		random = true;
	}
	if (App->player->now - passed_cherry > 45 * (0.5f * 1000.0f))
	{
		random = false;
	}

	count++;

	fruit_collision->SetPos(position.x + 1, position.y + 14);


	if (position.x <= -10)
	{
		App->cherry->fruit_collision->to_delete = true;
		App->cherry->Disable();
		passed_cherry = App->player->now;
		App->cherry->Enable();
	}



	if (position.x < 220)
	{
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

		if (random == false)
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
			uniform_int_distribution<> dis(1, 6);

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

					if (can_go_left && (tmp == 2 || tmp == 6))
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

					if (can_go_down && (tmp == 1 || tmp == 5))
					{
						position.x = (p_mid.x * 8) + 4 - 7;
						ghost_down = true; cont = true;
					}
					else{ ghost_down = false; }
				}
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
		if (1)
		{
			if (now >= total_time)
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

					// Move
					if (go_right)
					{
						// What is the next tile
						if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27 || position.x >= 210)
						{
							if (position.x >= 220){ position.x = -10; }

							position.x += speed + extra_speed;

							go_left = false; go_up = false; go_down = false;
						}
					}
					if (go_left)
					{
						// What is the next tile
						if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27 || position.x <= 0)
						{
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
							position.y -= speed + extra_speed;

							go_right = false; go_left = false; go_down = false;
						}
					}
					if (go_down)
					{
						// What is the next tile
						if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
						{

							position.y += speed + extra_speed;

							go_right = false; go_left = false; go_up = false;
						}
					}
				}
				else{  }
			}
			else{}
		}
		else{ }

		// Animation--------------------------------------------------------------

		render_pos.x = position.x;
		render_pos.y = position.y + pixels_up;

		count++;
		if (count == 10){
			if (play_audio)
			Mix_PlayChannel(4, App->audio->fruitmovement, 0);
			pixels_up = 1;
		}
		else if (count == 20)
		{
			pixels_up = -1;
			count = 0;
		}
	//------------------------------------------------------------------------

		if (can_see){
			if (App->map1->IsEnabled()){
				IsCherry = true;
				IsStrawberry = false;
				isOrange = false;
				isApple = false;
				App->render->Blit(graphics, render_pos.x, render_pos.y + DISTANCEM1 - 13, &cherry);
			}
			else if (App->map2->IsEnabled()){
				IsCherry = false;
				IsStrawberry = true;
				isOrange = false;
				isApple = false;
				App->render->Blit(graphics, render_pos.x, render_pos.y + DISTANCEM1 - 13, &strawberry);
			}
			else if (App->map3->IsEnabled()){
				IsStrawberry = false;
				IsCherry = false;
				isOrange = true;
				isApple = false;
				App->render->Blit(graphics, render_pos.x, render_pos.y + DISTANCEM1 - 13, &orange);
			}
			else if (App->map3->IsEnabled()){
				IsStrawberry = false;
				IsCherry = false;
				isOrange = false;
				isApple = true;
				App->render->Blit(graphics, render_pos.x, render_pos.y + DISTANCEM1 - 13, &orange);
			}
		}
	return UPDATE_CONTINUE;
}
