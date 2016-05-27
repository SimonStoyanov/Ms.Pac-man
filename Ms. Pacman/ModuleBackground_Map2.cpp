#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"

#include "ModuleCherry.h"
#include "ModulePlayer2.h"



ModuleBackgroundMap2::ModuleBackgroundMap2()
{
	tile0 = { 74, 0, 8, 8 };	tile1 = { 0, 0, 8, 8 };		tile2 = { 9, 0, 8, 8 };		tile3 = { 18, 0, 8, 8 };	tile4 = { 27, 0, 8, 8 };	 tile5 = { 0, 9, 8, 8 };
	tile6 = { 9, 9, 8, 8 };		tile7 = { 0, 18, 8, 8 };	tile8 = { 9, 18, 8, 8 };	tile9 = { 18, 18, 8, 8 };	tile10 = { 27, 18, 8, 8 };	 tile11 = { 0, 27, 8, 8 };
	tile12 = { 9, 27, 8, 8 };	tile13 = { 18, 27, 8, 8 };	tile14 = { 27, 27, 8, 8 };	tile15 = { 37, 0, 8, 8 };	tile16 = { 46, 0, 8, 8 };	 tile17 = { 55, 0, 8, 8 };
	tile18 = { 64, 0, 8, 8 };	tile19 = { 37, 9, 8, 8 };	tile20 = { 46, 9, 8, 8 };	tile21 = { 55, 9, 8, 8 };	tile22 = { 64, 9, 8, 8 };	 tile23 = { 37, 18, 8, 8 };
	tile24 = { 46, 18, 8, 8 };	tile25 = { 55, 18, 8, 8 };	tile26 = { 64, 18, 8, 8 };	tilePILL = { 74, 9, 8, 8 };	tilepill = { 74, 18, 8, 8 }; tilehouse = { 74, 27, 8, 8 };
	tile27 = { 83, 0, 8, 8 };	tile28 = { 83, 9, 8, 8 };   tile29 = { 83, 18, 8, 8 };	tile30 = { 83, 27, 8, 8 };  tile31 = { 92, 0, 8, 8 };
}

ModuleBackgroundMap2::~ModuleBackgroundMap2()
{}

// Load assets
bool ModuleBackgroundMap2::Start()
{
	LOG("Loading maps(2).");
	bool ret = true;
	graphics = App->textures->Load("Tileset 2.png");

	// Positions ---------------
	App->player->passed_time = App->player->now;
	App->player->speed = 1.0f;
	App->player->position.x = 105; //105
	App->player->position.y = 195; //195
	App->player->can_see = true;
	App->player->go_left = true; 	App->player->go_right = false; 	App->player->go_up = false; 	App->player->go_down = false;

	App->player2->speed = 1.0f;
	App->player2->position.x = 105; //105
	App->player2->position.y = 195; //195
	App->player2->can_see = true;
	App->player2->go_left = false; 	App->player2->go_right = true; 	App->player2->go_up = false; 	App->player2->go_down = false;

	App->ghost_blue->position.x = 90; //105 //90
	App->ghost_blue->position.y = 123; //99 //123
	App->ghost_blue->in_box = true;
	App->ghost_blue->can_see = true;

	App->ghost_orange->position.x = 120;
	App->ghost_orange->position.y = 123;
	App->ghost_orange->in_box = true;
	App->ghost_orange->can_see = true;

	App->ghost_pink->position.x = 105;
	App->ghost_pink->position.y = 123;
	App->ghost_pink->in_box = true;
	App->ghost_pink->can_see = true;

	App->ghost_red->position.x = 105;
	App->ghost_red->position.y = 99;
	App->ghost_red->can_see = true;

	App->ghost_blue->is_vulnerable = false;
	App->ghost_orange->is_vulnerable = false;
	App->ghost_pink->is_vulnerable = false;
	App->ghost_red->is_vulnerable = false;

	// Enable and disable modules ---------
	App->audio->Enable();
	App->cherry->Enable();
	App->ghost_blue->Enable();
	App->ghost_orange->Enable();
	App->ghost_pink->Enable();
	App->ghost_red->Enable();
	App->player->Enable();
	if (App->player->two_players == true){
		App->player2->Enable();
	}
	App->collision->Enable();
	App->UI->Enable();

	// Temporal map
	char tmp_map[31][28]
	{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
		{ 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7 },  //1
		{ 0, 0, 0, 0, 0, 0, 0, 15, 16, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 15, 16, 0, 0, 0, 0, 0, 0, 0 },  //2
		{ 17, 17, 17, 17, 17, 12, 0, 15, 16, 28, 11, 17, 17, 17, 17, 17, 17, 12, 28, 15, 16, 0, 11, 17, 17, 17, 17, 17 }, //3
		{ 31, 18, 18, 18, 18, 14, 0, 13, 14, 28, 13, 18, 18, 26, 25, 18, 18, 14, 28, 13, 14, 0, 13, 18, 18, 18, 18, 32 }, //4
		{ 8, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 27, 10 }, //5
		{ 8, 28, 11, 17, 17, 17, 17, 17, 12, 28, 11, 12, 28, 15, 16, 28, 11, 12, 28, 11, 17, 17, 17, 17, 17, 12, 28, 10 }, //6
		{ 8, 28, 15, 25, 18, 18, 18, 18, 14, 28, 15, 16, 28, 15, 16, 28, 15, 16, 28, 13, 18, 18, 18, 18, 26, 16, 28, 10 }, //7
		{ 8, 28, 15, 16, 28, 28, 28, 28, 28, 28, 15, 16, 28, 13, 14, 28, 15, 16, 28, 28, 28, 28, 28, 28, 15, 16, 28, 10 }, //8
		{ 8, 28, 15, 16, 28, 11, 17, 17, 12, 0, 15, 16, 28, 28, 28, 28, 15, 16, 0, 11, 17, 17, 12, 28, 15, 16, 28, 10 }, //9
		{ 8, 28, 13, 14, 28, 13, 18, 26, 16, 0, 15, 23, 17, 17, 17, 17, 24, 16, 0, 15, 25, 18, 14, 0, 13, 14, 28, 10 }, //10
		{ 8, 28, 28, 28, 28, 28, 28, 15, 16, 0, 13, 18, 18, 18, 18, 18, 18, 14, 0, 15, 16, 28, 28, 28, 28, 28, 28, 10 }, //11
		{ 33, 17, 17, 17, 17, 12, 28, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 28, 11, 17, 17, 17, 17, 34 }, //12
		{ 31, 18, 18, 18, 18, 14, 28, 15, 16, 0, 19, 9, 9, 29, 29, 9, 9, 20, 0, 15, 16, 28, 13, 18, 18, 18, 18, 32 }, //13
		{ 8, 28, 28, 28, 28, 28, 28, 15, 16, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 15, 16, 28, 28, 28, 28, 28, 28, 10 }, //14
		{ 8, 28, 11, 17, 17, 12, 28, 13, 14, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 13, 14, 28, 11, 17, 17, 12, 28, 10 }, //15
		{ 8, 28, 13, 18, 26, 16, 28, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 28, 15, 25, 18, 14, 28, 10 }, //16
		{ 8, 28, 28, 28, 15, 16, 28, 11, 12, 0, 21, 7, 7, 7, 7, 7, 7, 22, 0, 11, 12, 28, 15, 16, 28, 28, 28, 10 }, //17
		{ 3, 9, 12, 28, 15, 16, 28, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 28, 15, 16, 28, 11, 9, 4 },  //18
		{ 0, 0, 8, 28, 15, 16, 28, 15, 23, 17, 12, 0, 11, 17, 17, 12, 0, 11, 17, 24, 16, 28, 15, 16, 28, 10, 0, 0 },  //19
		{ 0, 0, 8, 28, 13, 14, 28, 13, 18, 18, 14, 0, 15, 30, 30, 16, 0, 13, 18, 18, 14, 28, 13, 14, 28, 10, 0, 0 },  //20
		{ 0, 0, 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 15, 30, 30, 16, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10, 0, 0 },  //21
		{ 0, 0, 8, 28, 11, 17, 17, 17, 17, 17, 12, 28, 15, 30, 30, 16, 28, 11, 17, 17, 17, 17, 17, 12, 28, 10, 0, 0 },  //22
		{ 7, 7, 14, 28, 13, 18, 18, 26, 25, 18, 14, 28, 13, 18, 18, 14, 28, 13, 18, 26, 25, 18, 18, 14, 28, 13, 7, 7 },  //23
		{ 0, 0, 0, 28, 28, 28, 28, 15, 16, 28, 28, 28, 0, 0, 0, 0, 28, 28, 28, 15, 16, 28, 28, 28, 28, 0, 0, 0 },  //24
		{ 17, 17, 12, 28, 11, 12, 28, 15, 16, 28, 11, 17, 17, 17, 17, 17, 17, 12, 28, 15, 16, 28, 11, 12, 28, 11, 17, 17 }, //25
		{ 31, 18, 14, 28, 15, 16, 28, 13, 14, 28, 13, 18, 18, 26, 25, 18, 18, 14, 28, 13, 14, 28, 15, 16, 28, 13, 18, 32 }, //26
		{ 8, 27, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 27, 10 }, //27
		{ 8, 28, 11, 17, 24, 16, 28, 11, 17, 17, 17, 12, 28, 15, 16, 28, 11, 17, 17, 17, 12, 28, 15, 23, 17, 12, 28, 10 }, //28
		{ 8, 28, 13, 18, 18, 14, 28, 13, 18, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 18, 14, 28, 13, 18, 18, 14, 28, 10 }, //29
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //30
		{ 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4 },  //31
	};

	// Passing map to the header
	for (int i = 0; i < 31; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			App->map1->g_map[i][y] = tmp_map[i][y];
		}
	}
	return ret;
}

// Load assets
bool ModuleBackgroundMap2::CleanUp()
{
	LOG("Unloading maps(2) stage.");

	App->player->Disable();
	if (App->player->two_players == true){
		App->player2->Disable();
	}
	App->ghost_blue->Disable();
	App->ghost_orange->Disable();
	App->ghost_pink->Disable();
	App->ghost_red->Disable();
	App->audio->Disable();
	App->collision->Disable();
	App->cherry->Disable();
	App->UI->Disable();

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleBackgroundMap2::Update()
{

	// Draw everything --------------------------------------	
	int i = 0;
	while (i < 28)
	{
		for (int j = 0; j < 31; j++)
		{
			switch (App->map1->g_map[j][i])
			{
			case 0:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile0);
				break;
			case 1:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile1);
				break;
			case 2:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile2);
				break;
			case 3:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile3);
				break;
			case 4:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile4);
				break;
			case 5:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile5);
				break;
			case 6:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile6);
				break;
			case 7:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile7);
				break;
			case 8:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile8);
				break;
			case 9:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile9);
				break;
			case 10:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile10);
				break;
			case 11:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile11);
				break;
			case 12:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile12);
				break;
			case 13:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile13);
				break;
			case 14:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile14);
				break;
			case 15:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile15);
				break;
			case 16:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile16);
				break;
			case 17:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile17);
				break;
			case 18:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile18);
				break;
			case 19:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile19);
				break;
			case 20:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile20);
				break;
			case 21:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile21);
				break;
			case 22:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile22);
				break;
			case 23:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile23);
				break;
			case 24:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile24);
				break;
			case 25:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile25);
				break;
			case 26:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile26);
				break;
			case 27:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tilePILL);
				break;
			case 28:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tilepill);
				break;
			case 29:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tilehouse);
				break;
			case 30:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile27);
				break;
			case 31:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile28);
				break;
			case 32:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile29);
				break;
			case 33:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile30);
				break;
			case 34:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCEM1, &tile31);
				break;
			}
		}
		i++;
	}

	// Eat pills
	switch (App->map1->g_map[App->player->p_mid.y][App->player->p_mid.x])
	{
	case 27:
		// Change tile
		App->map1->g_map[App->player->p_mid.y][App->player->p_mid.x] = 0;
		if (App->ghost_blue->is_vulnerable == false && App->ghost_orange->is_vulnerable == false && App->ghost_pink->is_vulnerable == false && App->ghost_red->is_vulnerable == false){
			Mix_PlayChannel(1, App->audio->powerpill, 0);

			// Vulnerable
			App->ghost_blue->passed_time = App->ghost_blue->now;
			App->ghost_orange->passed_time = App->ghost_orange->now;
			App->ghost_pink->passed_time = App->ghost_pink->now;
			App->ghost_red->passed_time = App->ghost_red->now;

			App->ghost_blue->is_vulnerable = true;
			App->ghost_orange->is_vulnerable = true;
			App->ghost_pink->is_vulnerable = true;
			App->ghost_red->is_vulnerable = true;
		}

		// Points
		App->UI->score += 50;
		eaten_pills++;

		break;
	case 28:
		// Change tile
		App->map1->g_map[App->player->p_mid.y][App->player->p_mid.x] = 0;
		Mix_PlayChannel(-1, App->audio->wakawaka, 0);

		// Points
		App->UI->score += 10;
		eaten_pills++;

		break;
	default:
		break;
	}

	switch (App->map1->g_map[App->player2->p_mid.y][App->player2->p_mid.x])
	{
	case 27:
		// Change tile
		App->map1->g_map[App->player2->p_mid.y][App->player2->p_mid.x] = 0;
		if (App->ghost_blue->is_vulnerable == false && App->ghost_orange->is_vulnerable == false && App->ghost_pink->is_vulnerable == false && App->ghost_red->is_vulnerable == false){
			Mix_PlayChannel(1, App->audio->powerpill, 0);

			// Vulnerable
			App->ghost_blue->passed_time = App->ghost_blue->now;
			App->ghost_orange->passed_time = App->ghost_orange->now;
			App->ghost_pink->passed_time = App->ghost_pink->now;
			App->ghost_red->passed_time = App->ghost_red->now;

			App->ghost_blue->is_vulnerable = true;
			App->ghost_orange->is_vulnerable = true;
			App->ghost_pink->is_vulnerable = true;
			App->ghost_red->is_vulnerable = true;
		}
		// Points
		App->UI->_score += 50;
		eaten_pills++;

		break;
	case 28:
		// Change tile
		App->map1->g_map[App->player2->p_mid.y][App->player2->p_mid.x] = 0;
		Mix_PlayChannel(-1, App->audio->wakawaka, 0);

		// Points
		App->UI->_score += 10;
		eaten_pills++;

		break;
	default:
		break;
	}

	if (eaten_pills <= 242)
	{
		App->fade->FadeToBlack(App->map2, App->end_screen, 2.0f);
	}

	// Load scene when press space

	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->map2, App->end_screen, 2.0F);
	}

	return UPDATE_CONTINUE;
}