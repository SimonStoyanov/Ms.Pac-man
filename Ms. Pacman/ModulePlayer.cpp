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
#include "ModuleCherry.h"
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

	ftimerIsOn = false;	gtimerIsOn = false;

	return ret;
}

bool ModulePlayer::CleanUp()
{
	one_time = false;
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Paths mode -------------------------
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN)
	{
		can_see_paths = !can_see_paths;
	}

	// God mode --------------------------
	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		god_mode = !god_mode;
	}
	if (god_mode)
	{
		speed = 2.0f;
		if (two_players == true){
			App->player2->speed = 2.0f;
		}
	}
	else{ 
		speed = 1.0f; 
		if (two_players == true){
			App->player2->speed = 1.0f;
		}
	}
	
	// Random ghost timer --------------------------
	if (now - actual_t_g_r > 8 * 3.0f * 0.5f * 1000.0) //random ghost timer
	{
		ghost_random = false;
	}
	else
	{
		ghost_random = true;
	}

	// Pause --------------------
	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN){
		pause = !pause;
		if (!Mix_Paused(3)){
			Mix_Pause(3);
			Mix_Pause(4);
		}
		else{
			Mix_Resume(3);
			Mix_Resume(4);
		}
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
	else if (!pause && !App->ghost_red->player_dead){
		if (!god_mode)
			speed = 1.0f;
		else
			speed = 2.0f;
		if (two_players == true)
		{
			if (!god_mode)
				App->player2->speed = 1.0f;
			else
				App->player2->speed = 2.0f;
		}
		App->ghost_blue->speed = 1.0f;
		App->ghost_pink->speed = 1.0f;
		App->ghost_red->speed = 1.0f;
		App->ghost_orange->speed = 1.0f;
	}
	// --------------------

	Animation* current_animation = prev_anim;

	now = SDL_GetTicks() - start_time; //seting now

	player_collision->SetPos(position.x + 3, position.y+11); //seting collision

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
	if (!is_dead && speed != 0)
	{
		Mix_Resume(3);
		Mix_Resume(4);
		if (total_time <= now)
		{
			// Reseting random ghosts time and box time
			if (one_time == false) 
			{
				now = 0;
				actual_t_g_r = now;

				App->ghost_orange->passed_box = now;
				App->ghost_blue->passed_box = now;
				App->ghost_pink->passed_box = now;
				App->cherry->passed_cherry = now;
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
		else{ 
			left.speed = 0.0f; 
			App->ghost_red->speed = 0;
			if (!Mix_Paused(3)){
				Mix_Pause(3);
				Mix_Pause(4);
			}

			App->render->Blit(App->UI->graphics, position.x - 15, position.y - 35, &App->UI->Ready, 1.0f);
		}
	}
	else{ down.speed = 0.0f; up.speed = 0.0f; left.speed = 0.0f; right.speed = 0.0f; }

	// Change scene when dies ----------------------------
	if (lifes == 0 && App->map1->IsEnabled() && end_game)
	{
		lifes = 5;
		// Start everything again 
		//Red
		App->ghost_red->position.x = 105;
		App->ghost_red->position.y = 99;
		App->ghost_red->can_see = false;
		
		App->ghost_red->ghost_down = false; App->ghost_red->ghost_left = false; App->ghost_red->ghost_right = false; App->ghost_red->ghost_up = false;

		//Orange
		App->ghost_orange->position.x = 120;
		App->ghost_orange->position.y = 123;
		App->ghost_orange->in_box = true;
		App->ghost_orange->can_see = false;
		
		App->ghost_orange->ghost_down = false; App->ghost_orange->ghost_left = false; App->ghost_orange->ghost_right = false; App->ghost_orange->ghost_up = false;

		//Pink
		App->ghost_pink->position.x = 105;
		App->ghost_pink->position.y = 123;
		App->ghost_pink->in_box = true;
		App->ghost_pink->can_see = false;
		
		App->ghost_pink->ghost_down = false; App->ghost_pink->ghost_left = false; App->ghost_pink->ghost_right = false; App->ghost_pink->ghost_up = false;

		//Blue
		App->ghost_blue->position.x = 90; //105 //90
		App->ghost_blue->position.y = 123; //99 //123
		App->ghost_blue->in_box = true;
		App->ghost_blue->can_see = false;
	
		App->ghost_blue->ghost_down = false; App->ghost_blue->ghost_left = false; App->ghost_blue->ghost_right = false; App->ghost_blue->ghost_up = false;

		//Player
		App->player->position.x = 105; //105
		App->player->position.y = 195; //195
		App->player->can_see = false;
		go_left = true; go_right = false;


		//Player2
		if (two_players)
		{
			App->player2->position.x = 105; //105
			App->player2->position.y = 195; //195
			App->player2->can_see = false;
			App->player2->go_left = false; App->player2->go_right = true;
		}

		App->player->is_dead = false; //
	

		App->ghost_red->player_dead = false; //Only on red ghost.

		{
			App->render->Blit(App->UI->graphics, position.x - 32, position.y - 35, &App->UI->GameOver, 1.0f);
			SDL_Delay(5000);
		}

		App->fade->FadeToBlack(App->map1, App->end_screen, 1.0f);
	}


//Player die -----------------------------
	if (!end_game)
	{
		//End game when lifes = 0
		if (App->player->is_dead && ((now - passed_time) > (10 * 0.5f * 1000.0f) && lifes == 0))
		{
			end_game = true;
		}

		// Solves the bug of dying 2 times
		else if ((now - passed_time) > (13 * 0.5f * 1000.0f))
		{
			no_more = false;
		}
		else if (App->player->is_dead && (now - passed_time) > (10 * 0.5f * 1000.0f))
		{

			// Start everything again 
			//Red
			App->ghost_red->position.x = 105;
			App->ghost_red->position.y = 99;
			App->ghost_red->can_see = true;
			App->ghost_red->speed = 1.0f;
			App->ghost_red->ghost_down = false; App->ghost_red->ghost_left = false; App->ghost_red->ghost_right = false; App->ghost_red->ghost_up = false;

			//Orange
			App->ghost_orange->position.x = 120;
			App->ghost_orange->position.y = 123;
			App->ghost_orange->in_box = true;
			App->ghost_orange->can_see = true;
			App->ghost_orange->speed = 1.0f;
			App->ghost_orange->ghost_down = false; App->ghost_orange->ghost_left = false; App->ghost_orange->ghost_right = false; App->ghost_orange->ghost_up = false;

			//Pink
			App->ghost_pink->position.x = 105;
			App->ghost_pink->position.y = 123;
			App->ghost_pink->in_box = true;
			App->ghost_pink->can_see = true;
			App->ghost_pink->speed = 1.0f;
			App->ghost_pink->ghost_down = false; App->ghost_pink->ghost_left = false; App->ghost_pink->ghost_right = false; App->ghost_pink->ghost_up = false;

			//Blue
			App->ghost_blue->position.x = 90; //105 //90
			App->ghost_blue->position.y = 123; //99 //123
			App->ghost_blue->in_box = true;
			App->ghost_blue->can_see = true;
			App->ghost_blue->speed = 1.0f;
			App->ghost_blue->ghost_down = false; App->ghost_blue->ghost_left = false; App->ghost_blue->ghost_right = false; App->ghost_blue->ghost_up = false;

			//Player
			App->player->position.x = 105; //105
			App->player->position.y = 195; //195
			go_left = true; go_right = false;
			speed = 1.0f;
			
			//Player2
			if (two_players)
			{
				App->player2->position.x = 105; //105
				App->player2->position.y = 195; //195
				App->player2->go_left = false; App->player2->go_right = true;
				App->player2->speed = 1.0f;
			}

			//Cherry
			if (App->map1->IsEnabled())
			{
				App->cherry->passed_cherry = now;
				App->cherry->go_down = false; App->cherry->go_up = false; App->cherry->go_left = false; App->cherry->go_right = false;
			}

			actual_t_g_r = now + 5; //reseting random timer
			App->ghost_blue->passed_box = now;
			App->ghost_orange->passed_box = now;
			App->ghost_pink->passed_box = now;

			App->ghost_red->player_dead = false; //Only on red ghost.
			is_dead = false; //
			no_more = true; // Solves the bug of dying 2 times
		}
		// 8 sec
		else if (App->player->is_dead && (now - passed_time) > (8 * 0.5f * 1000.0f))
		{
			// Ghost red reset
			if (App->ghost_red->IsEnabled())
			{
				App->ghost_red->enemy_collision->to_delete = true;
				App->ghost_red->Disable();
				//App->textures->last_texture--; //Carefull with that. Could cause future errors.
				//App->ghost_red->graphics = nullptr;
				App->ghost_red->Enable();
			}

			// Ghost orange reset
			if (App->ghost_orange->IsEnabled())
			{
				App->ghost_orange->enemy_collision->to_delete = true;
				App->ghost_orange->Disable();
				//App->textures->last_texture--; //Carefull with that. Could cause future errors.
				//App->ghost_orange->graphics = nullptr;
				App->ghost_orange->Enable();
			}

			// Ghost pink reset
			if (App->ghost_pink->IsEnabled())
			{
				App->ghost_pink->enemy_collision->to_delete = true;
				App->ghost_pink->Disable();
				//App->textures->last_texture--; //Carefull with that. Could cause future errors.
				//App->ghost_pink->graphics = nullptr;
				App->ghost_pink->Enable();
			}

			// Ghost blue reset
			if (App->ghost_blue->IsEnabled())
			{
				App->ghost_blue->enemy_collision->to_delete = true;
				App->ghost_blue->Disable();
				//App->textures->last_texture--; //Carefull with that. Could cause future errors.
				//App->ghost_blue->graphics = nullptr;
				App->ghost_blue->Enable();
			}
		}

		// 6 sec
		else if (App->player->is_dead && (now - passed_time) > (5.9 * 0.5f * 1000.0f))
		{
			dead.speed = 0; //Stop dead animation
		}

		// 3.5 sec
		else if (App->player->is_dead && (now - passed_time) > (3.5 * 0.5f * 1000.0f))
		{
			// Start dead animation
			dead.speed = 0.3f;
			current_animation = &dead;
		}

		// 3 sec
		else if (App->player->is_dead && (now - passed_time) > (3 * 0.5f * 1000.0f))
		{
			Mix_PlayChannel(1, App->audio->death, 0);
			App->ghost_red->can_see = false;
			App->ghost_orange->can_see = false;
			App->ghost_pink->can_see = false;
			App->ghost_blue->can_see = false;
		}

	}

// Score timer and increase puntutaion ---------------------
	if (gtimer != 0 && now - gtimer < 2 * 1.0f * 0.5f * 1000.0 && gtimerIsOn)
	{
		if (eaten_ghost == 1){
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
	else{
		gtimerIsOn = false;
	}

	if (ftimer != 0 && now - ftimer < 2 * 1.0f * 0.5f * 1000.0 && ftimerIsOn){
		if (App->cherry->IsCherry){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f100, 1.0f);
		}
		else if (App->cherry->IsStrawberry){
			App->render->Blit(App->UI->gscore, x_aux, y_aux, &App->UI->f200, 1.0f);
		}
	}
	else{
		ftimerIsOn = false;
	}

// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;

	// Renders ----------------------------------------------
	if(can_see)
		App->render->Blit(graphics, position.x, position.y + DISTANCEM1 - r.h, &r); //player

	return UPDATE_CONTINUE;
}

// Collisions -----------------------------------------------
void ModulePlayer::OnCollision(Collider* c1, Collider* c2){
	LOG("\n\n\n------------------I've collided----------------------\n\n\n");

	// Cherry ---------------------
	if (c1 != nullptr && c2->type == COLLIDER_FRUIT)
	{
		App->cherry->passed_cherry = now;
		App->cherry->go_down = false; App->cherry->go_up = false; App->cherry->go_left = false; App->cherry->go_right = false;

		Mix_PlayChannel(4, App->audio->eatenfruit, 0);
		App->cherry->play_audio = false;
		x_aux = position.x;		y_aux = position.y + 11;
		if (App->cherry->IsCherry){
			App->UI->score += 100;
		}
		if (App->cherry->IsStrawberry){
			App->UI->score += 200;
		}
		ftimer = now;
		ftimerIsOn = true;
	}

	// Player --------------------
	if (((c1 != nullptr && c2->type == COLLIDER_BLUE && !App->ghost_blue->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_ORANGE && !App->ghost_orange->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_PINK && !App->ghost_pink->is_vulnerable) ||
		(c1 != nullptr && c2->type == COLLIDER_RED && !App->ghost_red->is_vulnerable)) && god_mode == false && is_dead == false){
		
		if (c2->type == COLLIDER_BLUE && App->ghost_blue->is_dead)
		{}
		else if (c2->type == COLLIDER_ORANGE && App->ghost_orange->is_dead)
		{}
		else if (c2->type == COLLIDER_PINK && App->ghost_pink->is_dead)
		{}
		else if (c2->type == COLLIDER_RED && App->ghost_red->is_dead)
		{}
		else
		{
			if (!is_dead && !no_more)
			{
				App->player->passed_time = App->player->now;
				App->player->is_dead = true;

				if (lifes > 0)
					lifes--;
			}

			Mix_Pause(3);
			App->ghost_red->speed = 0;
			App->ghost_orange->speed = 0;
			App->ghost_pink->speed = 0;
			App->ghost_blue->speed = 0;
			App->player->speed = 0;
		}
	}

	// Blue ghost ------------------------
	else if (c1 != nullptr && c2->type == COLLIDER_BLUE && App->ghost_blue->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		if (eaten_ghost == 5){
			eaten_ghost = 1;
		}
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			gtimer = now;
			App->UI->score += 200;
		}
		else if (eaten_ghost == 2){
			gtimer = now;
			App->UI->score += 400;
		}
		else if (eaten_ghost == 3){
			gtimer = now;
			App->UI->score += 800;
		}
		else if (eaten_ghost == 4){
			gtimer = now;
			App->UI->score += 1600;
		}

		//SDL_Delay(500);

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
	// Orange ghost ------------------------
	else if (c1 != nullptr && c2->type == COLLIDER_ORANGE && App->ghost_orange->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		if (eaten_ghost == 5){
			eaten_ghost = 1;
		}
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			gtimer = now;
			App->UI->score += 200;
		}
		else if (eaten_ghost == 2){
			gtimer = now;
			App->UI->score += 400;
		}
		else if (eaten_ghost == 3){
			gtimer = now;
			App->UI->score += 800;
		}
		else if (eaten_ghost == 4){
			gtimer = now;
			App->UI->score += 1600;
		}

		//SDL_Delay(500);

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

	// Pink ghost ------------------------
	else if (c1 != nullptr && c2->type == COLLIDER_PINK && App->ghost_pink->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		if (eaten_ghost == 5){
			eaten_ghost = 1;
		}
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			gtimer = now;
			App->UI->score += 200;
		}
		else if (eaten_ghost == 2){
			gtimer = now;
			App->UI->score += 400;
		}
		else if (eaten_ghost == 3){
			gtimer = now;
			App->UI->score += 800;
		}
		else if (eaten_ghost == 4){
			gtimer = now;
			App->UI->score += 1600;
		}

		//SDL_Delay(500);


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

	// Red ghost ------------------------
	else if (c1 != nullptr && c2->type == COLLIDER_RED && App->ghost_red->is_vulnerable)
	{
		Mix_PlayChannel(-1, App->audio->eatenghost, 0);
		eaten_ghost++;
		gtimerIsOn = true;
		x_aux = position.x;		y_aux = position.y + 11;
		if (eaten_ghost == 5){
			eaten_ghost = 1;
		}
		//SDL_Delay(500);
		if (eaten_ghost == 1){
			gtimer = now;
			App->UI->score += 200;
		}
		else if (eaten_ghost == 2){
			gtimer = now;
			App->UI->score += 400;
		}
		else if (eaten_ghost == 3){
			gtimer = now;
			App->UI->score += 800;
		}
		else if (eaten_ghost == 4){
			gtimer = now;
			App->UI->score += 1600;
		}

		//SDL_Delay(500);

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

