#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModulePillsMap1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModulePillsMap1::ModulePillsMap1()
{
	// Power Pills
	char map1[31][28]{
		{ 1, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 2 },
		{ 8, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 3, 9, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 7, 7, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 7, 7, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 9, 9, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
		{ 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4 }
	};

	tile0 = { 74, 0, 8, 8 };	tile1 = { 0, 0, 8, 8 };		tile2 = { 9, 0, 8, 8 };		tile3 = { 18, 0, 8, 8 };	tile4 = { 27, 0, 8, 8 };	tile5 = { 0, 9, 8, 8 };
	tile6 = { 9, 9, 8, 8 };		tile7 = { 0, 18, 8, 8 };	tile8 = { 9, 18, 8, 8 };	tile9 = { 18, 18, 8, 8 };	tile10 = { 27, 18, 8, 8 };	tile11 = { 0, 27, 8, 8 };
	tile12 = { 9, 27, 8, 8 };	tile13 = { 18, 27, 8, 8 };	tile14 = { 27, 27, 8, 8 };	tile15 = { 37, 0, 8, 8 };	tile16 = { 46, 0, 8, 8 };	tile17 = { 55, 0, 8, 8 };
	tile18 = { 64, 0, 8, 8 };	tile19 = { 37, 9, 8, 8 };	tile20 = { 46, 9, 8, 8 };	tile21 = { 55, 9, 8, 8 };	tile22 = { 64, 9, 8, 8 };	tile23 = { 37, 18, 8, 8 };
	tile24 = { 46, 18, 8, 8 };	tile25 = { 55, 18, 8, 8 };	tile26 = { 64, 18, 8, 8 };	tilePILL = { 74, 9, 8, 8 };	tilepill = { 74, 18, 8, 8 };tilehouse = { 74, 27, 8, 8 };

}

ModulePillsMap1::~ModulePillsMap1()
{}

// Load assets
bool ModulePillsMap1::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("Tileset1.png");

	// Enable and disable modules

	return ret;
}

// Load assets
bool ModulePillsMap1::CleanUp()
{
	LOG("Unloading maps(1) stage.");
	return true;
}

// Update: draw background
update_status ModulePillsMap1::Update()
{
	for (int i = 0; i < 31; i++){
		for (int j = 0; j < 28; j++){
			switch (map1[i][j]){
				case 0:
					App->render->Blit(graphics, 0, 0, &tile0);
					break;
				case 1:
					App->render->Blit(graphics, 0, 0, &tile1);
					break;
				case 2:
					App->render->Blit(graphics, 0, 0, &tile2);
					break;
				case 3:
					App->render->Blit(graphics, 0, 0, &tile3);
					break;
				case 4:
					App->render->Blit(graphics, 0, 0, &tile4);
					break;
				case 5:
					App->render->Blit(graphics, 0, 0, &tile5);
					break;
				case 6:
					App->render->Blit(graphics, 0, 0, &tile6);
					break;
				case 7:
					App->render->Blit(graphics, 0, 0, &tile7);
					break;
				case 8:
					App->render->Blit(graphics, 0, 0, &tile8);
					break;
				case 9:
					App->render->Blit(graphics, 0, 0, &tile9);
					break;
				case 10:
					App->render->Blit(graphics, 0, 0, &tile10);
					break;
				case 11:
					App->render->Blit(graphics, 0, 0, &tile11);
					break;
				case 12:
					App->render->Blit(graphics, 0, 0, &tile12);
					break;
				case 13:
					App->render->Blit(graphics, 0, 0, &tile13);
					break;
				case 14:
					App->render->Blit(graphics, 0, 0, &tile14);
					break;
				case 15:
					App->render->Blit(graphics, 0, 0, &tile15);
					break;
				case 16:
					App->render->Blit(graphics, 0, 0, &tile16);
					break;
				case 17:
					App->render->Blit(graphics, 0, 0, &tile17);
					break;
				case 18:
					App->render->Blit(graphics, 0, 0, &tile18);
					break;
				case 19:
					App->render->Blit(graphics, 0, 0, &tile19);
					break;
				case 20:
					App->render->Blit(graphics, 0, 0, &tile20);
					break;
				case 21:
					App->render->Blit(graphics, 0, 0, &tile21);
					break;
				case 22:
					App->render->Blit(graphics, 0, 0, &tile22);
					break;
				case 23:
					App->render->Blit(graphics, 0, 0, &tile23);
					break;
				case 24:
					App->render->Blit(graphics, 0, 0, &tile24);
					break;
				case 25:
					App->render->Blit(graphics, 0, 0, &tile25);
					break;
				case 26:
					App->render->Blit(graphics, 0, 0, &tile26);
					break;
				case 27:
					App->render->Blit(graphics, 0, 0, &tilePILL);
					break;
				case 28:
					App->render->Blit(graphics, 0, 0, &tilepill);
					break;
				case 29:
					App->render->Blit(graphics, 0, 0, &tilehouse);
					break;
			}

		}
	}

	return UPDATE_CONTINUE;
}

