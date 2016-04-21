#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModulePillsMap1.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

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

	// Enable and disable modules
	App->player->Enable();
	App->audio->Enable();
	App->ghost_blue->Enable();
	App->mapPills1->Enable();

	// Temporal map
	char tmp_map[31][28]
	{	//1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
		{ 1, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 2 }, //1
		{ 8, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 10 }, //2
		{ 8, 0, 11, 17, 17, 12, 0, 15, 16, 0, 11, 17, 17, 17, 17, 17, 17, 12, 0, 15, 16, 0, 11, 17, 17, 12, 0, 10 }, //3
		{ 8, 0, 13, 18, 18, 14, 0, 13, 14, 0, 13, 18, 18, 18, 18, 18, 18, 14, 0, 13, 14, 0, 13, 18, 18, 14, 0, 10 }, //4
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //5
		{ 3, 9, 12, 0, 11, 12, 0, 11, 17, 17, 17, 12, 0, 11, 12, 0, 11, 17, 17, 17, 12, 0, 0, 0, 0, 0, 0, 10 }, //6
		{ 0, 0, 8, 0, 15, 16, 0, 15, 30, 30, 30, 16, 0, 15, 16, 0, 15, 30, 30, 30, 16, 0, 0, 0, 0, 0, 0, 10 }, //7
		{ 7, 7, 14, 0, 15, 16, 0, 13, 18, 18, 18, 14, 0, 15, 16, 0, 13, 18, 18, 18, 14, 0, 0, 0, 0, 0, 0, 10 }, //8
		{ 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //9
		{ 9, 9, 12, 0, 15, 23, 17, 17, 12, 0, 11, 17, 17, 24, 23, 17, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //10
		{ 0, 0, 8, 0, 13, 18, 18, 18, 14, 0, 13, 18, 18, 18, 18, 18, 18, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //11
		{ 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //12
		{ 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //13
		{ 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //14
		{ 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //15
		{ 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //16
		{ 7, 7, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //17
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //18
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //19
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //20
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //21
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //22
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //23
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //24
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //25
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //26
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //27
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //28
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //29
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }, //30
		{ 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4 } //31

	};

	// Passing map to the header
	for (int i = 0; i <= 31; i++)
	{
		for (int y = 0; y <= 28; y++)
		{
			map1[i][y] = tmp_map[i][y];
		}
	}
	return ret;

}

// Load assets
bool ModuleBackgroundMap1::CleanUp()
{
	LOG("Unloading maps(1) stage.");
	return true;
}

// Update: draw background
update_status ModuleBackgroundMap1::Update()
{
	
	// Draw everything --------------------------------------	
	int i = 0;
	while (i < 32)
	{
		for (int j = 0; j < 28; j++)
		{
			switch (map1[j][i])
			{
			case 0:
				//LOG("%d", map1[i][j]);
				App->render->Blit(graphics, i * 8, j * 8, &tile0);
				break;
			case 1:
				App->render->Blit(graphics, i * 8, j * 8, &tile1);
				break;
			case 2:
				App->render->Blit(graphics, i * 8, j * 8, &tile2);
				break;
			case 3:
				App->render->Blit(graphics, i * 8, j * 8, &tile3);
				break;
			case 4:
				App->render->Blit(graphics, i * 8, j * 8, &tile4);
				break;
			case 5:
				App->render->Blit(graphics, i * 8, j * 8, &tile5);
				break;
			case 6:
				App->render->Blit(graphics, i * 8, j * 8, &tile6);
				break;
			case 7:
				App->render->Blit(graphics, i * 8, j * 8, &tile7);
				break;
			case 8:
				App->render->Blit(graphics, i * 8, j * 8, &tile8);
				break;
			case 9:
				App->render->Blit(graphics, i * 8, j * 8, &tile9);
				break;
			case 10:
				App->render->Blit(graphics, i * 8, j * 8, &tile10);
				break;
			case 11:
				App->render->Blit(graphics, i * 8, j * 8, &tile11);
				break;
			case 12:
				App->render->Blit(graphics, i * 8, j * 8, &tile12);
				break;
			case 13:
				App->render->Blit(graphics, i * 8, j * 8, &tile13);
				break;
			case 14:
				App->render->Blit(graphics, i * 8, j * 8, &tile14);
				break;
			case 15:
				App->render->Blit(graphics, i * 8, j * 8, &tile15);
				break;
			case 16:
				App->render->Blit(graphics, i * 8, j * 8, &tile16);
				break;
			case 17:
				App->render->Blit(graphics, i * 8, j * 8, &tile17);
				break;
			case 18:
				App->render->Blit(graphics, i * 8, j * 8, &tile18);
				break;
			case 19:
				App->render->Blit(graphics, i * 8, j * 8, &tile19);
				break;
			case 20:
				App->render->Blit(graphics, i * 8, j * 8, &tile20);
				break;
			case 21:
				App->render->Blit(graphics, i * 8, j * 8, &tile21);
				break;
			case 22:
				App->render->Blit(graphics, i * 8, j * 8, &tile22);
				break;
			case 23:
				App->render->Blit(graphics, i * 8, j * 8, &tile23);
				break;
			case 24:
				App->render->Blit(graphics, i * 8, j * 8, &tile24);
				break;
			case 25:
				App->render->Blit(graphics, i * 8, j * 8, &tile25);
				break;
			case 26:
				App->render->Blit(graphics, i * 8, j * 8, &tile26);
				break;
			case 27:
				App->render->Blit(graphics, i * 8, j * 8, &tilePILL);
				break;
			case 28:
				App->render->Blit(graphics, i * 8, j * 8, &tilepill);
				break;
			case 29:
				App->render->Blit(graphics, i * 8, j * 8, &tilehouse);
				break;
			case 30:
				App->render->Blit(graphics, i * 8, j * 8, &tile27);
				break;

			}

			int a = App->player->position.x; a += 10;
			int b = App->player->position.y; b -= 10;
			map1[b/8][a/8] = 0;
		}
		i++;
	}
	
	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}
	return UPDATE_CONTINUE;
}
