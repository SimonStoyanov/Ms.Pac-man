#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"



ModuleBackgroundMap2::ModuleBackgroundMap2()
{
	tile0 = { 74, 0, 8, 8 };	tile1 = { 0, 0, 8, 8 };		tile2 = { 9, 0, 8, 8 };		tile3 = { 18, 0, 8, 8 };	tile4 = { 27, 0, 8, 8 };	tile5 = { 0, 9, 8, 8 };
	tile6 = { 9, 9, 8, 8 };		tile7 = { 0, 18, 8, 8 };	tile8 = { 9, 18, 8, 8 };	tile9 = { 18, 18, 8, 8 };	tile10 = { 27, 18, 8, 8 };	tile11 = { 0, 27, 8, 8 };
	tile12 = { 9, 27, 8, 8 };	tile13 = { 18, 27, 8, 8 };	tile14 = { 27, 27, 8, 8 };	tile15 = { 37, 0, 8, 8 };	tile16 = { 46, 0, 8, 8 };	tile17 = { 55, 0, 8, 8 };
	tile18 = { 64, 0, 8, 8 };	tile19 = { 37, 9, 8, 8 };	tile20 = { 46, 9, 8, 8 };	tile21 = { 55, 9, 8, 8 };	tile22 = { 64, 9, 8, 8 };	tile23 = { 37, 18, 8, 8 };
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

	// Enable and disable modules
	App->player->Enable();

	// Temporal map
	char tmp_map[31][28]
	{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
		{ 7,  7,  7,  7,  7,  7,  7,  5,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  5,  6,  7,  7,  7,  7,  7,  7,  7 },  //1
		{ 0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0 },  //2
		{ 17, 17, 17, 17, 17, 12, 0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  11, 17, 17, 17, 17, 17 }, //3
		{ 31, 18, 18, 18, 18, 14, 0,  13, 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13, 14, 0,  13, 18, 18, 18, 18, 32 }, //4
		{ 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //5
		{ 8,  0,  11, 17, 17, 17, 17, 17, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //6
		{ 8,  0,  15, 25, 18, 18, 18, 18, 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //7
		{ 8,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //8
		{ 8,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //9
		{ 8,  0,  13, 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //10
		{ 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //11
		{ 33, 17, 17, 17, 17, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  34 },  //12
		{ 31, 18, 18, 18, 18, 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  32 },  //13
		{ 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //14
		{ 8,  0,  11, 17, 17, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //15
		{ 8,  0,  13, 18, 26, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //16
		{ 8,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //17
		{ 3,  9,  12, 0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 9,  4 },  //18
		{ 0,  0,  8,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10, 0,  0 },  //19
		{ 0,  0,  8,  0,  13, 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10, 0,  0 },  //20
		{ 0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10, 0,  0 },  //21
		{ 0,  0,  8,  0,  11, 17, 17, 17, 17, 17, 12, 0,  0,  0,  0,  0,  0,  11, 17, 17, 17, 17, 17, 12, 0,  10, 0,  0 },  //22
		{ 7,  7,  14, 0,  13, 18, 18, 26, 25, 18, 14, 0,  0,  0,  0,  0,  0,  13, 18, 26, 25, 18, 18, 14, 0,  13, 7,  7 },  //23
		{ 0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0 },  //24
		{ 17, 17, 12, 0,  11, 12, 0,  15, 16, 0,  11, 17, 17, 17, 17, 17, 17, 12, 0,  15, 16, 0,  11, 12, 0,  11, 17, 17 },  //25
		{ 31, 18, 14, 0,  15, 16, 0,  13, 14, 0,  13, 18, 18, 26, 25, 18, 18, 14, 0,  13, 14, 0,  15, 16, 0,  13, 18, 32 },  //26
		{ 8,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  0,  0,  0,  0,  0,  0,  15, 16, 0,  0,  0,  10 },  //27
		{ 8,  0,  11, 17, 24, 16, 0,  11, 17, 17, 17, 12, 0,  15, 16, 0,  11, 17, 17, 17, 12, 0,  15, 23, 17, 12, 0,  10 },  //28
		{ 8,  0,  13, 18, 18, 14, 0,  13, 18, 18, 18, 14, 0,  13, 14, 0,  13, 18, 18, 18, 14, 0,  13, 18, 18, 14, 0,  10 },  //29
		{ 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10 },  //30
		{ 3,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  4 },  //31
	 };
	
	// Passing map to the header
	for (int i = 0; i < 31; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			map2[i][y] = tmp_map[i][y];
		}
	}
	return ret;
}

// Load assets
bool ModuleBackgroundMap2::CleanUp()
{
	LOG("Unloading maps(2) stage");
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
			switch (map2[j][i])
			{
			case 0:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile0);
				break;
			case 1:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile1);
				break;
			case 2:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile2);
				break;
			case 3:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile3);
				break;
			case 4:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile4);
				break;
			case 5:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile5);
				break;
			case 6:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile6);
				break;
			case 7:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile7);
				break;
			case 8:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile8);
				break;
			case 9:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile9);
				break;
			case 10:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile10);
				break;
			case 11:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile11);
				break;
			case 12:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile12);
				break;
			case 13:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile13);
				break;
			case 14:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile14);
				break;
			case 15:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile15);
				break;
			case 16:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile16);
				break;
			case 17:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile17);
				break;
			case 18:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile18);
				break;
			case 19:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile19);
				break;
			case 20:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile20);
				break;
			case 21:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile21);
				break;
			case 22:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile22);
				break;
			case 23:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile23);
				break;
			case 24:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile24);
				break;
			case 25:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile25);
				break;
			case 26:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile26);
				break;
			case 27:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tilePILL);
				break;
			case 28:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tilepill);
				break;
			case 29:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tilehouse);
				break;
			case 30:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile27);
				break;
			case 31:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile28);
				break;
			case 32:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile29);
				break;
			case 33:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile30);
				break;
			case 34:
				App->render->Blit(graphics, i * 8, j * 8 + DISTANCE, &tile31);
				break;
			}
		}
		i++;
	}

	switch (map2[App->player->p_mid.y][App->player->p_mid.x])
	{
	case 27:
		map2[App->player->p_mid.y][App->player->p_mid.x] = 0;
		eaten_dots++;
		break;
	case 28:
		map2[App->player->p_mid.y][App->player->p_mid.x] = 0;
		eaten_dots++;
		break;
	default:
		break;
	}
	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->map2, App->end_screen, 2.0F);
	}

	return UPDATE_CONTINUE;
}