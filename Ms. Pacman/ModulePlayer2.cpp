#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
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
#include "ModuleCherry.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	test = { 3, 120, 1, 1 };

	// right animation
	right.PushBack({ 50, 2, 13, 13 });
	right.PushBack({ 65, 2, 13, 13 });
	right.PushBack({ 81, 2, 13, 13 });
	right.speed = 0.3f;

	// left animation
	left.PushBack({ 50, 34, 13, 13 });
	left.PushBack({ 66, 34, 13, 13 });
	left.PushBack({ 81, 2, 13, 13 });
	left.speed = 0.3f;

	// up animation
	up.PushBack({ 50, 53, 13, 9 });
	up.PushBack({ 65, 51, 13, 12 });
	up.PushBack({ 81, 2, 13, 13 });
	up.speed = 0.3f;

	// down animation
	down.PushBack({ 50, 18, 13, 13 });
	down.PushBack({ 66, 18, 13, 13 });
	down.PushBack({ 81, 2, 13, 13 });
	down.speed = 0.3f;

	// dead animation
	dead.PushBack({ 50, 2, 13, 13 });
	dead.PushBack({ 50, 18, 13, 13 });
	dead.PushBack({ 50, 34, 13, 13 });
	dead.PushBack({ 50, 49, 13, 13 });
	dead.speed = 0.3f;
}

ModulePlayer2::~ModulePlayer2()
{
	player_collision = nullptr;
	App->textures->Unload(graphics);
}


// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Pac-man & Ghosts.png");

	prev_anim = &left;

	player_collision = App->collision->AddCollider({ position.x - 50, position.y - 50, 10, 10 }, COLLIDER_PLAYER, this);

	App->player->start_time = SDL_GetTicks();

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	current_animation = prev_anim;

	App->player->now = SDL_GetTicks() - App->player->start_time;

	player_collision->SetPos(position.x + 3, position.y + 11);

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


	// Movement ---------------------------------------
	if (!App->player->is_dead)
	{
		if (App->player->total_time <= App->player->now)
		{
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_DOWN] == false && App->input->keyboard[SDL_SCANCODE_LEFT] == false && App->input->keyboard[SDL_SCANCODE_UP] == false) // right
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
			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) // left
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
			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_LEFT] == false && App->input->keyboard[SDL_SCANCODE_S] == false && App->input->keyboard[SDL_SCANCODE_D] == false) // up
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
			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_LEFT] == false) // down
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

					go_right = false; go_left = false; go_up = false;
				}
				else
					down.speed = 0.0f;
			}
		}
		else{ left.speed = 0.0f; }
	}
	else{ down.speed = 0.0f; up.speed = 0.0f; left.speed = 0.0f; right.speed = 0.0f; }



	// Player 2 animation dead control ----------------------
	// 6 sec
	if (App->player->is_dead && (App->player->now - App->player->passed_time) > (5.9 * 0.5f * 1000.0f))
	{
		dead.speed = 0; //Stop dead animation
	}

	// 3.5 sec
	else if (App->player->is_dead && (App->player->now - App->player->passed_time) > (3.5 * 0.5f * 1000.0f))
	{
		// Start dead animation
		dead.speed = 0.3f;
		current_animation = &dead;
	}

	// Score timer and increase puntutaion ---------------------
	if (App->player->ftimer != 0 && App->player->now - App->player->ftimer < 2 * 1.0f * 0.5f * 1000.0 && ftimerIsOn){
		if (App->cherry->IsCherry){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f100, 1.0f);
		}
		else if (App->cherry->IsStrawberry){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f200, 1.0f);
		}
		else if (App->cherry->isOrange){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f500, 1.0f);
		}
		else if (App->cherry->isPretzel){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f700, 1.0f);
		}
		else if (App->cherry->isApple){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f1000, 1.0f);
		}
		else if (App->cherry->isPear){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f2000, 1.0f);
		}
		else if (App->cherry->isBanana){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f5000, 1.0f);
		}
	}
	else
	{
		App->player->ftimerIsOn = false;
	}
	
	if (App->player->gtimer != 0 && App->player->now - App->player->gtimer < 2 * 1.0f * 0.5f * 1000.0)
	{
		if (eaten_ghost == 1)
		{
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->g200, 1.0f);
		}
		else if (eaten_ghost == 2){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->g400, 1.0f);
		}
		else if (eaten_ghost == 3){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->g800, 1.0f);
		}
		else if (eaten_ghost == 4){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->g1600, 1.0f);
		}
	}
	if (gtimerIsOn && !App->ghost_blue->is_vulnerable && !App->ghost_orange->is_vulnerable && !App->ghost_pink->is_vulnerable && !App->ghost_red->is_vulnerable){
		gtimerIsOn = false;
	}


// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;

	if(can_see)
		App->render->Blit(graphics, position.x, position.y + DISTANCEM1 - r.h, &r); //player

	return UPDATE_CONTINUE;
}

// Collisions -----------------------------------------------
void ModulePlayer2::OnCollision(Collider* c1, Collider* c2){
	LOG("\n\n\n------------------I've collided----------------------\n\n\n");
	
	if (c1 != nullptr && c2->type == COLLIDER_FRUIT)
	{
		App->cherry->passed_cherry = App->player->now;
		App->cherry->go_down = false; App->cherry->go_up = false; App->cherry->go_left = false; App->cherry->go_right = false;
	
		Mix_PlayChannel(4, App->audio->eatenfruit, 0);
		x_aux = position.x;		y_aux = position.y + 11;

		if (App->cherry->IsCherry){
			App->UI->_score += 100;
		}
		if (App->cherry->IsStrawberry){
			App->UI->_score += 200;
		}
		if (App->cherry->isOrange){
			App->UI->_score += 500;
		}
		if (App->cherry->isPretzel)
		{
			App->UI->_score += 700;
		}
		if (App->cherry->isApple)
		{
			App->UI->_score += 1000;
		}
		if (App->cherry->isPear)
		{
			App->UI->_score += 2000;
		}
		if (App->cherry->isBanana)
		{
			App->UI->_score += 5000;
		}

		App->player->ftimer = App->player->now;
		ftimerIsOn = true;
	}


	if (((c1 != nullptr && c2->type == COLLIDER_BLUE && !App->ghost_blue->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_ORANGE && !App->ghost_orange->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_PINK && !App->ghost_pink->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_RED && !App->ghost_red->is_vulnerable)) && App->player->god_mode == false)
	{
		if (c2->type == COLLIDER_BLUE && App->ghost_blue->is_dead)
		{
		}
		else if (c2->type == COLLIDER_ORANGE && App->ghost_orange->is_dead)
		{
		}
		else if (c2->type == COLLIDER_PINK && App->ghost_pink->is_dead)
		{
		}
		else if (c2->type == COLLIDER_RED && App->ghost_red->is_dead)
		{
		}
		else
		{
			if (!App->ghost_red->player_dead && !App->player->no_more)
			{
				App->player->passed_time = App->player->now;
				App->ghost_red->player_dead = true; //only on red
				App->player->is_dead = true;

				if (App->player->lifes > 0)
					App->player->lifes--;
			}
			Mix_Pause(3);
			App->ghost_red->speed = 0;
			App->ghost_orange->speed = 0;
			App->ghost_pink->speed = 0;
			App->ghost_blue->speed = 0;
			App->player->speed = 0;
			App->player2->speed = 0;
		}
	}
	else if (c1 != nullptr && c2->type == COLLIDER_BLUE && App->ghost_blue->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		if (!gtimerIsOn){
			eaten_ghost = 0;
			x_aux = 999; y_aux = 999;
		}
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			App->player->gtimer = App->player->now;
			App->UI->_score += 200;
		}
		else if (eaten_ghost == 2){
			App->player->gtimer = App->player->now;
			App->UI->_score += 400;
		}
		else if (eaten_ghost == 3){
			App->player->gtimer = App->player->now;
			App->UI->_score += 800;
		}
		else if (eaten_ghost == 4){
			App->player->gtimer = App->player->now;
			App->UI->_score += 1600;
		}
		App->ghost_blue->is_dead = true;
		App->ghost_blue->is_vulnerable = false;

		if (App->ghost_blue->is_dead)
		{
			if (App->ghost_blue->position.x < 105)
			{
				App->ghost_blue->p_position_x = 80;
				App->ghost_blue->p_position_y = 99;
			}
			else
			{
				App->ghost_blue->p_position_x = 130;
				App->ghost_blue->p_position_y = 99;
			}
		}
	}
	else if (c1 != nullptr && c2->type == COLLIDER_ORANGE && App->ghost_orange->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		if (!gtimerIsOn){
			eaten_ghost = 0;
			x_aux = 999; y_aux = 999;
		}
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			App->player->gtimer = App->player->now;
			App->UI->_score += 200;
		}
		else if (eaten_ghost == 2){
			App->player->gtimer = App->player->now;
			App->UI->_score += 400;
		}
		else if (eaten_ghost == 3){
			App->player->gtimer = App->player->now;
			App->UI->_score += 800;
		}
		else if (eaten_ghost == 4){
			App->player->gtimer = App->player->now;
			App->UI->_score += 1600;
		}
		App->ghost_orange->is_dead = true;
		App->ghost_orange->is_vulnerable = false;

		if (App->ghost_orange->is_dead)
		{
			if (App->ghost_orange->position.x < 105)
			{
				App->ghost_orange->p_position_x = 80;
				App->ghost_orange->p_position_y = 99;
			}
			else
			{
				App->ghost_orange->p_position_x = 130;
				App->ghost_orange->p_position_y = 99;
			}
		}
	}
	else if (c1 != nullptr && c2->type == COLLIDER_PINK && App->ghost_pink->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		if (!gtimerIsOn){
			eaten_ghost = 0;
			x_aux = 999; y_aux = 999;
		}
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			App->player->gtimer = App->player->now;
			App->UI->_score += 200;
		}
		else if (eaten_ghost == 2){
			App->player->gtimer = App->player->now;
			App->UI->_score += 400;
		}
		else if (eaten_ghost == 3){
			App->player->gtimer = App->player->now;
			App->UI->_score += 800;
		}
		else if (eaten_ghost == 4){
			App->player->gtimer = App->player->now;
			App->UI->_score += 1600;
		}
		App->ghost_pink->is_dead = true;
		App->ghost_pink->is_vulnerable = false;

		if (App->ghost_pink->is_dead)
		{
			if (App->ghost_pink->position.x < 105)
			{
				App->ghost_pink->p_position_x = 80;
				App->ghost_pink->p_position_y = 99;
			}
			else
			{
				App->ghost_pink->p_position_x = 130;
				App->ghost_pink->p_position_y = 99;
			}
		}
	}
	else if (c1 != nullptr && c2->type == COLLIDER_RED && App->ghost_red->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		if (!gtimerIsOn){
			eaten_ghost = 0;
			x_aux = 999; y_aux = 999;
		}
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			App->player->gtimer = App->player->now;
			App->UI->_score += 200;
		}
		else if (eaten_ghost == 2){
			App->player->gtimer = App->player->now;
			App->UI->_score += 400;
		}
		else if (eaten_ghost == 3){
			App->player->gtimer = App->player->now;
			App->UI->_score += 800;
		}
		else if (eaten_ghost == 4){
			App->player->gtimer = App->player->now;
			App->UI->_score += 1600;
		}
		App->ghost_red->is_dead = true;
		App->ghost_red->is_vulnerable = false;

		if (App->ghost_red->is_dead)
		{
			if (App->ghost_red->position.x < 105)
			{
				App->ghost_red->p_position_x = 80;
				App->ghost_red->p_position_y = 99;
			}
			else
			{
				App->ghost_red->p_position_x = 130;
				App->ghost_red->p_position_y = 99;
			}
		}
	}
}

