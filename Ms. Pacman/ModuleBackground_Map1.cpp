#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"

#include "ModuleMenu.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"


ModuleBackgroundMap1::ModuleBackgroundMap1()
{
	tile0 = { 74, 0, 8, 8 };	tile1 = { 0, 0, 8, 8 };		tile2 = { 9, 0, 8, 8 };		tile3 = { 18, 0, 8, 8 };	tile4 = { 27, 0, 8, 8 };	tile5 = { 0, 9, 8, 8 };
	tile6 = { 9, 9, 8, 8 };		tile7 = { 0, 18, 8, 8 };	tile8 = { 9, 18, 8, 8 };	tile9 = { 18, 18, 8, 8 };	tile10 = { 27, 18, 8, 8 };	tile11 = { 0, 27, 8, 8 };
	tile12 = { 9, 27, 8, 8 };	tile13 = { 18, 27, 8, 8 };	tile14 = { 27, 27, 8, 8 };	tile15 = { 37, 0, 8, 8 };	tile16 = { 46, 0, 8, 8 };	tile17 = { 55, 0, 8, 8 };
	tile18 = { 64, 0, 8, 8 };	tile19 = { 37, 9, 8, 8 };	tile20 = { 46, 9, 8, 8 };	tile21 = { 55, 9, 8, 8 };	tile22 = { 64, 9, 8, 8 };	tile23 = { 37, 18, 8, 8 };
	tile24 = { 46, 18, 8, 8 };	tile25 = { 55, 18, 8, 8 };	tile26 = { 64, 18, 8, 8 };	tilePILL = { 74, 9, 8, 8 };	tilepill = { 74, 18, 8, 8 }; tilehouse = { 74, 27, 8, 8 };
	tile27 = { 83, 0, 8, 8 };
}

ModuleBackgroundMap1::~ModuleBackgroundMap1()
{}

// Load assets
bool ModuleBackgroundMap1::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("Tileset 1.png");

	// Positions ---------------
	App->player->position.x = 105; //105
	App->player->position.y = 195; //195

	App->ghost_blue->position.x = 105; //105
	App->ghost_blue->position.y = 99; //99

	App->ghost_orange->position.x = 105;
	App->ghost_orange->position.y = 99;

	App->ghost_pink->position.x = 105;
	App->ghost_pink->position.y = 99;

	App->ghost_red->position.x = 105;
	App->ghost_red->position.y = 99;

	// Enable and disable modules ---------
	App->player->Enable();
	App->audio->Enable();
	//App->ghost_blue->Enable();
	//App->ghost_orange->Enable();
	//App->ghost_pink->Enable();
	App->ghost_red->Enable();
	App->collision->Enable();

	// Temporal map ----------
	char tmp_map[31][28]
	{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
		{ 1, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 2 }, //1
		{ 8, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 10 }, //2
		{ 8, 27, 11, 17, 17, 12, 28, 15, 16, 28, 11, 17, 17, 17, 17, 17, 17, 12, 28, 15, 16, 28, 11, 17, 17, 12, 27, 10 }, //3
		{ 8, 28, 13, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 18, 18, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 14, 28, 10 }, //4
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //5
		{ 3, 9, 12, 28, 11, 12, 28, 11, 17, 17, 17, 12, 28, 11, 12, 28, 11, 17, 17, 17, 12, 28, 11, 12, 28, 11, 9, 4 }, //6
		{ 0, 0, 8, 28, 15, 16, 28, 15, 30, 30, 30, 16, 28, 15, 16, 28, 15, 30, 30, 30, 16, 28, 15, 16, 28, 10, 0, 0 }, //7
		{ 7, 7, 14, 28, 15, 16, 28, 13, 18, 18, 18, 14, 28, 15, 16, 28, 13, 18, 18, 18, 14, 28, 15, 16, 28, 13, 7, 7 }, //8
		{ 0, 0, 0, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 0, 0, 0 }, //9
		{ 9, 9, 12, 28, 15, 23, 17, 17, 12, 0, 11, 17, 17, 24, 23, 17, 17, 12, 0, 11, 17, 17, 24, 16, 28, 11, 9, 9 }, //10
		{ 0, 0, 8, 28, 13, 18, 18, 18, 14, 0, 13, 18, 18, 18, 18, 18, 18, 14, 0, 13, 18, 18, 18, 14, 28, 10, 0, 0 }, //11
		{ 0, 0, 8, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 10, 0, 0 }, //12
		{ 0, 0, 8, 28, 11, 17, 17, 17, 12, 0, 19, 9, 9, 29, 29, 9, 9, 20, 0, 11, 17, 17, 17, 12, 28, 10, 0, 0 }, //13
		{ 0, 0, 8, 28, 15, 25, 18, 18, 14, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 13, 18, 18, 26, 16, 28, 10, 0, 0 }, //14
		{ 0, 0, 8, 28, 15, 16, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 15, 16, 28, 10, 0, 0 }, //15
		{ 0, 0, 8, 28, 15, 16, 0, 11, 12, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 11, 12, 0, 15, 16, 28, 10, 0, 0 }, //16
		{ 7, 7, 14, 28, 13, 14, 0, 15, 16, 0, 21, 7, 7, 7, 7, 7, 7, 22, 0, 15, 16, 0, 13, 14, 28, 13, 7, 7 }, //17
		{ 0, 0, 0, 28, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 28, 0, 0, 0 }, //18
		{ 9, 9, 12, 28, 11, 17, 17, 24, 23, 17, 17, 12, 0, 11, 12, 0, 11, 17, 17, 24, 23, 17, 17, 12, 28, 11, 9, 9 }, //19
		{ 0, 0, 8, 28, 13, 18, 18, 18, 18, 18, 18, 14, 0, 15, 16, 0, 13, 18, 18, 18, 18, 18, 18, 14, 28, 10, 0, 0 }, //20
		{ 0, 0, 8, 28, 28, 28, 28, 28, 28, 28, 0, 0, 0, 15, 16, 0, 0, 0, 28, 28, 28, 28, 28, 28, 28, 10, 0, 0 }, //21
		{ 0, 0, 8, 28, 11, 17, 17, 17, 12, 28, 11, 17, 17, 24, 23, 17, 17, 12, 28, 11, 17, 17, 17, 12, 28, 10, 0, 0 }, //22
		{ 1, 7, 14, 28, 13, 18, 18, 18, 14, 28, 13, 18, 18, 18, 18, 18, 18, 14, 28, 13, 18, 18, 18, 14, 28, 13, 7, 2 }, //23
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 0, 0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //24
		{ 8, 28, 11, 17, 17, 12, 28, 11, 17, 17, 17, 12, 28, 11, 12, 28, 11, 17, 17, 17, 12, 28, 11, 17, 17, 12, 28, 10 }, //25
		{ 8, 28, 15, 30, 30, 16, 28, 15, 25, 18, 18, 14, 28, 15, 16, 28, 13, 18, 18, 26, 16, 28, 15, 30, 30, 16, 28, 10 }, //26
		{ 8, 28, 15, 30, 30, 16, 28, 15, 16, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 15, 16, 28, 15, 30, 30, 16, 28, 10 }, //27
		{ 8, 27, 15, 30, 30, 16, 28, 15, 16, 28, 11, 17, 17, 24, 23, 17, 17, 12, 28, 15, 16, 28, 15, 30, 30, 16, 27, 10 }, //28
		{ 8, 28, 13, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 18, 18, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 14, 28, 10 }, //29
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //30
		{ 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, } //31

	};

	// Passing map to the header --------
	for (int i = 0; i < 31; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			g_map[i][y] = tmp_map[i][y];
		}
	}
	return ret;

}

// Load assets
bool ModuleBackgroundMap1::CleanUp()
{
	LOG("Unloading maps(1) stage.");

	App->player->Disable();
	App->ghost_blue->Disable();
	App->ghost_orange->Disable();
	App->ghost_pink->Disable();
	App->ghost_red->Disable();
	App->audio->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleBackgroundMap1::Update()
{
	// Draw everything --------------------------------------	
	int i = 0;
	while (i < 28)
	{
		for (int j = 0; j < 31; j++)
		{
			switch (g_map[j][i])
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
			}

		}
		i++;
	}

	// Eat pills
	switch (g_map[App->player->p_mid.y][App->player->p_mid.x])
	{
	case 27:
		// Change tile
		g_map[App->player->p_mid.y][App->player->p_mid.x] = 0;

		// Vulnerable
		App->ghost_blue->passed_time = App->ghost_blue->now;
		App->ghost_orange->passed_time = App->ghost_orange->now;
		App->ghost_pink->passed_time = App->ghost_pink->now;
		App->ghost_red->passed_time = App->ghost_red->now;

		App->ghost_blue->is_vulnerable = true;
		App->ghost_orange->is_vulnerable = true;
		App->ghost_pink->is_vulnerable = true;
		App->ghost_red->is_vulnerable = true;

		// Points
		App->UI->score += 5;

		////
		//if (App->UI->points[5] >= 5 && App->UI->points[4] == 11){
		//	if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//	if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//	if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//	if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//	if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	App->UI->points[4] = 1;
		//}
		//else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] == 11){
		//	if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//	if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//	if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//	if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//	if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	App->UI->points[4] = 0;
		//	App->UI->points[3] = 1;
		//}
		//else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] >= 5 && App->UI->points[2] == 11){
		//	if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//	if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//	if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//	if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//	if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	App->UI->points[4] = 0;
		//	App->UI->points[3] = 0;
		//	App->UI->points[2] = 1;
		//}
		//else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] >= 5 && App->UI->points[2] >= 5 && App->UI->points[1] == 11){
		//	if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//	if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//	if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//	if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//	if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	App->UI->points[4] = 0;
		//	App->UI->points[3] = 0;
		//	App->UI->points[2] = 0;
		//	App->UI->points[1] = 1;
		//}
		//else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] >= 5 && App->UI->points[2] >= 5 && App->UI->points[1] >= 5 && App->UI->points[0] == 11){
		//	if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//	if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//	if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//	if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//	if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	App->UI->points[4] = 0;
		//	App->UI->points[3] = 0;
		//	App->UI->points[2] = 0;
		//	App->UI->points[1] = 0;
		//	App->UI->points[0] = 1;
		//}
		//else if (App->UI->points[5] <= 4){
		//	App->UI->points[5] += 5;
		//}
		//else{
		//	if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] >= 5 && App->UI->points[2] >= 5 && App->UI->points[1] >= 5){
		//		App->UI->points[0] += 1;
		//		App->UI->points[1] = 0;
		//		App->UI->points[2] = 0;
		//		App->UI->points[3] = 0;
		//		App->UI->points[4] = 0;
		//		if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//		if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//		if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//		if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//		if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	}
		//	else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] >= 5 && App->UI->points[2] >= 5){
		//		App->UI->points[1] += 1;
		//		App->UI->points[2] = 0;
		//		App->UI->points[3] = 0;
		//		App->UI->points[4] = 0;
		//		if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//		if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//		if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//		if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//		if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	}
		//	else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5 && App->UI->points[3] >= 5){
		//		App->UI->points[2] += 1;
		//		App->UI->points[3] = 0;
		//		App->UI->points[4] = 0;
		//		if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//		if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//		if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//		if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//		if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	}
		//	else if (App->UI->points[5] >= 5 && App->UI->points[4] >= 5){
		//		App->UI->points[3] += 1;
		//		App->UI->points[4] = 0;
		//		if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//		if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//		if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//		if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//		if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	}
		//	else if (App->UI->points[5] >= 5){
		//		App->UI->points[4] += 1;
		//		if (App->UI->points[5] == 5) App->UI->points[5] = 0;
		//		if (App->UI->points[5] == 6) App->UI->points[5] = 1;
		//		if (App->UI->points[5] == 7) App->UI->points[5] = 2;
		//		if (App->UI->points[5] == 8) App->UI->points[5] = 3;
		//		if (App->UI->points[5] == 9) App->UI->points[5] = 4;
		//	}
		//}

		break;
	case 28:
		// Change tile
		g_map[App->player->p_mid.y][App->player->p_mid.x] = 0;

		// Points
		App->UI->score++;

		//// Provisional Code Simon Pls my eyes
		//if (App->UI->points[5] == 9 && App->UI->points[4] == 11){
		//	App->UI->points[4] = 1;
		//	App->UI->points[5] = 0;
		//}
		//else if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 11){
		//	App->UI->points[3] = 1;
		//	App->UI->points[4] = 0;
		//	App->UI->points[5] = 0;
		//}
		//else if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 9 && App->UI->points[2] == 11){
		//	App->UI->points[2] = 1;
		//	App->UI->points[3] = 0;
		//	App->UI->points[4] = 0;
		//	App->UI->points[5] = 0;
		//}
		//else if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 9 && App->UI->points[2] == 9 && App->UI->points[1] == 11){
		//	App->UI->points[1] = 1;
		//	App->UI->points[2] = 0;
		//	App->UI->points[3] = 0;
		//	App->UI->points[4] = 0;
		//	App->UI->points[5] = 0;
		//}
		//else if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 9 && App->UI->points[2] == 9 && App->UI->points[1] == 9 && App->UI->points[0] == 11){
		//	App->UI->points[0] = 1;
		//	App->UI->points[1] = 0;
		//	App->UI->points[2] = 0;
		//	App->UI->points[3] = 0;
		//	App->UI->points[4] = 0;
		//	App->UI->points[5] = 0;
		//}
		//else if (App->UI->points[5] != 9){
		//	App->UI->points[5] += 1;
		//}
		//else{
		//	if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 9 && App->UI->points[2] == 9 && App->UI->points[1] == 9){
		//		App->UI->points[0] += 1;
		//		App->UI->points[1] = 0;
		//		App->UI->points[2] = 0;
		//		App->UI->points[3] = 0;
		//		App->UI->points[4] = 0;
		//		App->UI->points[5] = 0;
		//	}
		//	else if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 9 && App->UI->points[2] == 9){
		//		App->UI->points[1] += 1;
		//		App->UI->points[2] = 0;
		//		App->UI->points[3] = 0;
		//		App->UI->points[4] = 0;
		//		App->UI->points[5] = 0;
		//	}
		//	else if (App->UI->points[5] == 9 && App->UI->points[4] == 9 && App->UI->points[3] == 9){
		//		App->UI->points[2] += 1;
		//		App->UI->points[3] = 0;
		//		App->UI->points[4] = 0;
		//		App->UI->points[5] = 0;
		//	}
		//	else if (App->UI->points[5] == 9 && App->UI->points[4] == 9){
		//		App->UI->points[3] += 1;
		//		App->UI->points[4] = 0;
		//		App->UI->points[5] = 0;
		//	}
		//	else if (App->UI->points[5] == 9){
		//		App->UI->points[4] += 1;
		//		App->UI->points[5] = 0;
		//	}
		//}
		break;
	default:
		break;
	}


	// Load scene when all the pills are taken
	if (eaten_pills <= 223)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}

	// Load scene when press space
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}
	return UPDATE_CONTINUE;

}
