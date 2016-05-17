#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleBackground_Map1.h"
#include "ModuleCollision.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "ModuleUI.h"
#include "ModuleEndScreen.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	test = { 3, 120, 1, 1 };

	// right animation
	right.PushBack({ 33, 1, 15, 14 });
	right.PushBack({ 17, 1, 13, 14 });
	right.PushBack({ 1, 1, 11, 14 });
	right.speed = 0.3f;

	// left animation
	left.PushBack({ 15, 34, 15, 15 });
	left.PushBack({ 33, 34, 15, 15 });
	left.PushBack({ 0, 34, 17, 15 });
	left.speed = 0.3f;

	// up animation
	up.PushBack({ 33, 51, 14, 15 });
	up.PushBack({ 17, 51, 14, 13 });
	up.PushBack({ 1, 51, 14, 11 });
	up.speed = 0.3f;

	// down animation
	down.PushBack({ 33, 17, 14, 15 });
	down.PushBack({ 17, 17, 14, 15 });
	down.PushBack({ 1, 17, 14, 15 });
	down.speed = 0.3f;

	// dead animation
	dead.PushBack({ 17, 1, 13, 14 });
	dead.PushBack({ 17, 17, 14, 15 });
	dead.PushBack({ 33, 34, 15, 15 });
	dead.PushBack({ 17, 51, 14, 13 });
	dead.speed = 0.3f;

	total_time = (Uint32)(total_t * 0.5f * 1000.0f);
	
}

ModulePlayer::~ModulePlayer()
{
	player_collision = nullptr;
}


// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Pac-man & Ghosts.png");
	prev_anim = &left;
	
	player_collision = App->collision->AddCollider({ position.x - 50, position.y - 50, 10, 10 }, COLLIDER_PLAYER, this);

	start_time = SDL_GetTicks();

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		god_mode = !god_mode;
	}
	if (god_mode)
	{
		speed = 2.0f;
	}
	else{ speed = 1.0f; }

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		pause = !pause;
	}
	if (pause){
		speed = 0;
		
		if (two_players == true){
			App->player2->speed = 0;
		}
		App->ghost_blue->speed = 0;
		App->ghost_pink->speed = 0;
		App->ghost_red->speed = 0;
		App->ghost_orange->speed = 0;
	}
	else{ 
		speed = 1.0f;
		if (two_players == true){
			App->player2->speed = 1.0f;
		}
		App->ghost_blue->speed = 1.0f;
		App->ghost_pink->speed = 1.0f;
		App->ghost_red->speed = 1.0f;
		App->ghost_orange->speed = 1.0f;
	}

	Animation* current_animation = prev_anim;

	now = SDL_GetTicks() - start_time;

	player_collision->SetPos(position.x + 3, position.y+11);

	// Player tile collision detectors with tiles ------
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

	if (now - actual_t_g_r > 8 * 3.0f * 0.5f * 1000.0) //random ghost timer
	{
		ghost_random = false;
	}
	else
	{
		ghost_random = true;
	}

	// Movement ---------------------------------------
	if (!is_dead || speed == 0)
	{
		if (total_time <= now)
		{
			if (one_time == false) //reseting random ghosts time
			{
				actual_t_g_r = now;
				one_time = true;
			}

			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == false && App->input->keyboard[SDL_SCANCODE_A] == false && App->input->keyboard[SDL_SCANCODE_W] == false) // right
			{
				// What is the next tile
				if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) >= (p_mid.y * 8) + 2 && (position.y - 7) <= (p_mid.y * 8) + 6 || go_left == true)
					{
						position.y = (p_mid.y * 8) + 4 + 7; // Re-position to the center of the tile
						go_right = true; go_left = false; go_up = false; go_down = false;
					}
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) // left
			{
				// What is the next tile
				if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if ((position.x + 7) == (p_mid.x * 8) + 4 && (position.y - 7) >= (p_mid.y * 8) + 2 && (position.y - 7) <= (p_mid.y * 8) + 6 || go_right == true)
					{
						position.y = (p_mid.y * 8) + 4 + 7;  // Re-position to the center of the tile
						go_left = true; go_right = false; go_up = false; go_down = false;
					}
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == false && App->input->keyboard[SDL_SCANCODE_S] == false && App->input->keyboard[SDL_SCANCODE_D] == false) // up
			{
				// What is the next tile
				if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if (((position.x + 7) >= (p_mid.x * 8) + 2 && (position.x + 7) <= (p_mid.x * 8) + 6 && (position.y - 7) == (p_mid.y * 8) + 4 || go_down == true) && position.x < 208 && position.x > 2)
					{
						position.x = (p_mid.x * 8) + 4 - 7;  // Re-position to the center of the tile
						go_up = true; go_right = false; go_left = false; go_up = true; go_down = false;
					}
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == false) // down
			{
				// What is the next tile
				if (App->map1->g_map[p_down.y + 1][p_down.x] == 0 || App->map1->g_map[p_down.y + 1][p_down.x] == 28 || App->map1->g_map[p_down.y + 1][p_down.x] == 27)
				{
					// Is the player near the center-pixel of the tile?
					if (((position.x + 7) >= (p_mid.x * 8) + 2 && (position.x + 7) <= (p_mid.x * 8) + 6 && (position.y - 7) == (p_mid.y * 8) + 4 || go_up == true) && position.x < 208 && position.x > 2)
					{
						position.x = (p_mid.x * 8) + 4 - 7;  // Re-position to the center of the tile
						go_down = true; go_right = false; go_left = false; go_up = false;
					}
				}
			}

			if (go_right)
			{
				// What is the next tile
				if (App->map1->g_map[p_right.y][p_right.x + 1] == 0 || App->map1->g_map[p_right.y][p_right.x + 1] == 28 || App->map1->g_map[p_right.y][p_right.x + 1] == 27 || position.x >= 213)
				{
					right.speed = 0.3f;
					current_animation = &right;
					position.x += speed;
					wakawaka = true;

					// Tunel teleport
					if (position.x >= 220)
					{
						position.x = -10;
					}

					go_left = false; go_up = false; go_down = false;
				}
				else
					right.speed = 0.0f;
			}
			if (go_left)
			{
				// What is the next tile
				if (App->map1->g_map[p_left.y][p_left.x - 1] == 0 || App->map1->g_map[p_left.y][p_left.x - 1] == 28 || App->map1->g_map[p_left.y][p_left.x - 1] == 27 || position.x <= 0)
				{
					left.speed = 0.3f;
					current_animation = &left;
					position.x -= speed;
					wakawaka = true;
					go_right = false; go_up = false; go_down = false;

					// Tunel teleport
					if (position.x <= -10)
					{
						position.x = 220;
					}
				}
				else
					left.speed = 0.0f;
			}
			if (go_up)
			{
				// What is the next tile
				if (App->map1->g_map[p_up.y - 1][p_up.x] == 0 || App->map1->g_map[p_up.y - 1][p_up.x] == 28 || App->map1->g_map[p_up.y - 1][p_up.x] == 27)
				{
					up.speed = 0.3f;
					current_animation = &up;
					position.y -= speed;
					wakawaka = true;
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
					down.speed = 0.3f;
					current_animation = &down;
					position.y += speed;
					wakawaka = true;
					go_right = false; go_left = false; go_up = false;
				}
				else
					down.speed = 0.0f;
			}
		}
		else{ left.speed = 0.0f; }
	}
	else{ down.speed = 0.0f; up.speed = 0.0f; left.speed = 0.0f; right.speed = 0.0f; }

	// Change scene when dies
	if (lifes == 0 && App->map1->IsEnabled())
	{
		//App->fade->FadeToBlack(App->map1, App->menu, 0.0f);
	}


	 //Player die -----------------------------
	if (App->player->is_dead && (now - passed_time) > (10 * 0.5f * 1000.0f))
	{
		// Start everithing again 
		//Red
		App->ghost_red->position.x = 105;
		App->ghost_red->position.y = 99;
		App->ghost_red->can_see = true;
		App->ghost_red->speed = 1.0f;
		App->ghost_red->ghost_down = false; App->ghost_red->ghost_left = false; App->ghost_red->ghost_right = false; App->ghost_red->ghost_up = false;

		//Orange
		App->ghost_orange->position.x = 105;
		App->ghost_orange->position.y = 99;
		App->ghost_orange->can_see = true;
		App->ghost_orange->speed = 1.0f;
		App->ghost_orange->ghost_down = false; App->ghost_orange->ghost_left = false; App->ghost_orange->ghost_right = false; App->ghost_orange->ghost_up = false;

		//Pink
		App->ghost_pink->position.x = 105;
		App->ghost_pink->position.y = 99;
		App->ghost_pink->can_see = true;
		App->ghost_pink->speed = 1.0f;
		App->ghost_pink->ghost_down = false; App->ghost_pink->ghost_left = false; App->ghost_pink->ghost_right = false; App->ghost_pink->ghost_up = false;

		//Blue
		App->ghost_blue->position.x = 105;
		App->ghost_blue->position.y = 99;
		App->ghost_blue->can_see = true;
		App->ghost_blue->speed = 1.0f;
		App->ghost_blue->ghost_down = false; App->ghost_blue->ghost_left = false; App->ghost_blue->ghost_right = false; App->ghost_blue->ghost_up = false;

		//Player
		App->player->position.x = 105; //105
		App->player->position.y = 195; //195
		App->player->is_dead = false; //
		go_left = true; go_right = false;
		speed = 1.0f;

		App->ghost_red->player_dead = false; //Only on red ghost.

	}
	else if (App->player->is_dead && (now - passed_time) > (8 * 0.5f * 1000.0f))
	{
		// Ghost red reset
		if (App->ghost_red->IsEnabled())
		{
			App->ghost_red->enemy_collision->to_delete = true;
			App->ghost_red->Disable();
			App->textures->last_texture--; //Carefull with that. Could cause future errors.
			App->ghost_red->Enable();
		}

		// Ghost orange reset
		if (App->ghost_orange->IsEnabled())
		{
			App->ghost_orange->enemy_collision->to_delete = true;
			App->ghost_orange->Disable();
			App->textures->last_texture--; //Carefull with that. Could cause future errors.
			App->ghost_orange->Enable();
		}

		// Ghost pink reset
		if (App->ghost_pink->IsEnabled())
		{
			App->ghost_pink->enemy_collision->to_delete = true;
			App->ghost_pink->Disable();
			App->textures->last_texture--; //Carefull with that. Could cause future errors.
			App->ghost_pink->Enable();
		}

		// Ghost blue reset
		if (App->ghost_blue->IsEnabled())
		{
			App->ghost_blue->enemy_collision->to_delete = true;
			App->ghost_blue->Disable();
			App->textures->last_texture--; //Carefull with that. Could cause future errors.
			App->ghost_blue->Enable();
		}
	}
	else if (App->player->is_dead && (now - passed_time) > (5.9 * 0.5f * 1000.0f))
	{
		dead.speed = 0; //Stop dead animation
	}
	else if (App->player->is_dead && (now - passed_time) > (3.5 * 0.5f * 1000.0f))
	{
		dead.speed = 0.3f;
		current_animation = &dead;
	}
	else if (App->player->is_dead && (now - passed_time) > (3 * 0.5f * 1000.0f))
	{
			App->ghost_red->can_see = false;
			App->ghost_orange->can_see = false;
			App->ghost_pink->can_see = false;
			App->ghost_blue->can_see = false;
	}


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;

	//App->render->Blit(graphics, (position.x +7), (position.y - 7 + DISTANCEM1), &test, 1.0f);
	//App->render->Blit(graphics, (p_mid.x * 8) + 4, (p_mid.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_up.x * 8) + 4, (p_up.y * 8  + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_down.x * 8) + 4, (p_down.y * 8  + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_left.x * 8) + 4, (p_left.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //
	//App->render->Blit(graphics, (p_right.x * 8) + 4, (p_right.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //

	//App->render->Blit(graphics, position.x, position.y + DISTANCEM1, &test, 1.0f); //
	//App->render->Blit(graphics, 3, (p_right.y * 8 + DISTANCEM1) + 4, &test, 1.0f); //

	if(can_see)
		App->render->Blit(graphics, position.x, position.y + DISTANCEM1 - r.h, &r); //player

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2){
	LOG("\n\n\n------------------I've collided----------------------\n\n\n");
	if (((c1 != nullptr && c2->type == COLLIDER_BLUE && !App->ghost_blue->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_ORANGE && !App->ghost_orange->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_PINK && !App->ghost_pink->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_RED && !App->ghost_red->is_vulnerable)) && god_mode == false){
		// Player die -------------------
		if (!App->ghost_red->player_dead)
		{
			App->player->passed_time = App->player->now;
			App->ghost_red->player_dead = true; //only on red
			App->player->is_dead = true;

			if (lifes > 0)
				lifes--;
		}

		App->ghost_red->speed = 0;
		App->ghost_orange->speed = 0;
		App->ghost_pink->speed = 0;
		App->ghost_blue->speed = 0;
		App->player->speed = 0;

		// -------------------------------

	}
	else if (c1 != nullptr && c2->type == COLLIDER_BLUE && App->ghost_blue->is_vulnerable)
	{
		if (eaten_ghost == 0){
			App->UI->score += 200;
		}
		else if (eaten_ghost == 1){
			App->UI->score += 400;
		}
		else if (eaten_ghost == 2){
			App->UI->score += 800;
		}
		else if (eaten_ghost == 3){
			App->UI->score += 1600;
		}
		App->ghost_blue->enemy_collision->to_delete = true;
		App->ghost_blue->Disable();
		App->ghost_blue->Enable();

		App->ghost_blue->is_vulnerable = false;

		App->ghost_blue->position.x = 105;
		App->ghost_blue->position.y = 99;
		
		eaten_ghost++;
	}
	else if (c1 != nullptr && c2->type == COLLIDER_ORANGE && App->ghost_orange->is_vulnerable)
	{
		if (eaten_ghost == 0){
			App->UI->score += 200;
		}
		else if (eaten_ghost == 1){
			App->UI->score += 400;
		}
		else if (eaten_ghost == 2){
			App->UI->score += 800;
		}
		else if (eaten_ghost == 3){
			App->UI->score += 1600;
		}
		App->ghost_orange->enemy_collision->to_delete = true;
		App->ghost_orange->Disable();
		App->ghost_orange->Enable();

		App->ghost_orange->is_vulnerable = false;

		App->ghost_orange->position.x = 105;
		App->ghost_orange->position.y = 99;
		
		eaten_ghost++;
	}
	else if (c1 != nullptr && c2->type == COLLIDER_PINK && App->ghost_pink->is_vulnerable)
	{
		if (eaten_ghost == 0){
			App->UI->score += 200;
		}
		else if (eaten_ghost == 1){
			App->UI->score += 400;
		}
		else if (eaten_ghost == 2){
			App->UI->score += 800;
		}
		else if (eaten_ghost == 3){
			App->UI->score += 1600;
		}
		App->ghost_pink->enemy_collision->to_delete = true;
		App->ghost_pink->Disable();
		App->ghost_pink->Enable();

		App->ghost_pink->is_vulnerable = false;

		App->ghost_pink->position.x = 105;
		App->ghost_pink->position.y = 99;
		
		eaten_ghost++;
	}
	else if (c1 != nullptr && c2->type == COLLIDER_RED && App->ghost_red->is_vulnerable)
	{
		if (eaten_ghost == 0){
			App->UI->score += 200;
		}
		else if (eaten_ghost == 1){
			App->UI->score += 400;
		}
		else if (eaten_ghost == 2){
			App->UI->score += 800;
		}
		else if (eaten_ghost == 3){
			App->UI->score += 1600;
		}
		App->ghost_red->enemy_collision->to_delete = true;
		App->ghost_red->Disable();
		App->ghost_red->Enable();

		App->ghost_red->is_vulnerable = false;
		
		App->ghost_red->position.x = 105;
		App->ghost_red->position.y = 99;
		App->ghost_red->ghost_up = false;
		App->ghost_red->ghost_down = false;
		if (App->ghost_red->ghost_left = true)
			App->ghost_red->ghost_right = false;
		else
			App->ghost_red->ghost_left = true;
		
		eaten_ghost++;
	}

}

