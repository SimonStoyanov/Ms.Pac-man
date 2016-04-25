#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleMenu.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

#include "ModuleUI.h"


ModuleUI::ModuleUI()
{
	//tile0 = { , , , };		tile1 = { , , , };		tile2 = { , , , };		tile3 = { , , , };		tile4 = { , , , };
	//tile5 = { , , , };		tile6 = { , , , };		tile7 = { , , , };		tile8 = { , , , };		tile9 = { , , , };
	//tileH = { , , , };		tileI = { , , , };		tileG = { , , , };		tileS = { , , , };		tileC = { , , , };
	//tileO = { , , , };		tileR = { , , , };		tileE = { , , , };		tile_ = { , , , };		tileU = { , , , };
	//tileP = { , , , };		tileD = { , , , };		tileT = { , , , };
}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("Tileset 1.png");

//	// Enable and disable modules
//	App->player->Enable();
//	App->audio->Enable();
//	App->ghost_blue->Enable();
//
//	// Temporal map
//	char tmp_mapMENU[5][28]
//	{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //1
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //2
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //3
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //4
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }  //5
//	};
//	
//	char tmp_mapGAME[5][28]
//{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //1
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //2
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //3
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //4
//		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }  //5
//	};
//	// Passing map to the header
//	for (int i = 0; i < 5; i++)
//	{
//		for (int y = 0; y < 28; y++)
//		{
//			mapMENU[i][y] = tmp_mapMENU[i][y];
//		}
//	}
//	for (int i = 0; i < 5; i++)
//	{
//		for (int y = 0; y < 28; y++)
//		{
//			mapUI[i][y] = tmp_mapGAME[i][y];
//		}
//	}
	return ret;

}

// Load assets
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI stage.");
	return true;
}

// Update: draw background
update_status ModuleUI::Update()
{
	// Draw everything --------------------------------------	
	int i = 0;
	while (i < 28)
	{
		for (int j = 0; j < 31; j++)
		{
			switch (mapUI[j][i])
			{
				break;
			}

		}
		i++;
	}

	return UPDATE_CONTINUE;

}
