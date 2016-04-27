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
	tile0 = { 73, 9, 8, 8 };		tile1 = { 1, 9, 8, 8 };			tile2 = { 9, 9, 8, 8 };			tile3 = { 17, 9, 8, 8 };		tile4 = { 25, 9, 8, 8 };
	tile5 = { 33, 9, 8, 8 };		tile6 = { 41, 9, 8, 8 };		tile7 = { 49, 9, 8, 8 };		tile8 = { 57, 9, 8, 8 };		tile9 = { 65, 9, 8, 8 };
	tileH = { 1, 1, 8, 8 };			tileI = { 9, 1, 8, 8 };			tileG = { 17, 1, 8, 8 };		tileS = { 25, 1, 8, 8 };		tileC = { 33, 1, 8, 8 };
	tileO = { 41, 1, 8, 8 };		tileR = { 49, 1, 8, 8 };		tileE = { 57, 1, 8, 8 };		tile_ = { 81, 9, 8, 8 };		tileU = { 81, 1, 8, 8 };
	tileP = { 89, 1, 8, 8 };		tileD = { 65, 1, 8, 8 };		tileT = { 73, 1, 8, 8 };
	
	pacman1 = { 3, 18, 8, 8 }; pacman2 = { 3, 26, 8, 8 }; pacman3 = { 12, 18, 8, 8 }; pacman4 = { 12, 26, 8, 8 };

	points[0] = 11; 
	points[1] = 11; 
	points[2] = 11; 
	points[3] = 11; 
	points[4] = 11;
	points[5] = 0;
	points[6] = 0;
}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("Letters & Numbers.png");

	// Temporal map
	char tmp_mapMENU[5][28]
	{	// 1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
		{ '_','_','_', 1, 'U','P','_','_','_','H','I','G','H','_','S','C','O','R','E', '_','_','_',2, 'U','P', '_','_','_'}, //1
		{ '_','_','_','_','_', 0,  0, '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_', 0,  0, '_','_' }, //2
		{ '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_' }, //3
		//-------------------------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------//
		{ '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_' }, //4
		{ '_', '_','C','R','E','D','I','T','_','_', 0, 0,'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_' }  //5
	};
	
	char tmp_mapGAME[5][28]
	{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
		{ '_','_','_', 1, 'U','P','_','_','_','H','I','G','H','_','S','C','O','R','E', '_','_','_','_','_','_', '_','_','_'}, //1
		{ 'x','x','x','x','x','x','x', '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_', '_','_','_','_' }, //2
		{ '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_' }, //3
		//-------------------------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------//
		{ '_','_', 100, 102, 100, 102, 100, 102, 100, 102,'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_' }, //4
		{ '_', '_', 101, 103, 101, 103, 101, 103, 101, 103,'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_' }  //5
	};
	// Passing map to the header
	for (int i = 0; i < 5; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			mapMENU[i][y] = tmp_mapMENU[i][y];
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			mapUI[i][y] = tmp_mapGAME[i][y];
		}
	}
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
	if (App->menu->IsEnabled()){
		while (i < 28)
		{
			for (int j = 0, var = 0; j < 5; j++, var++)
			{
				if (j == 3){
					var = 34;
				}
				switch (mapMENU[j][i])
				{
				case 0:
					App->render->Blit(graphics, i * 8, var * 8, &tile0);
					break;
				case 1:
					App->render->Blit(graphics, i * 8, var * 8, &tile1);
					break;
				case 2:
					App->render->Blit(graphics, i * 8, var * 8, &tile2);
					break;
				case 3:
					App->render->Blit(graphics, i * 8, var * 8, &tile3);
					break;
				case 4:
					App->render->Blit(graphics, i * 8, var * 8, &tile4);
					break;
				case 5:
					App->render->Blit(graphics, i * 8, var * 8, &tile5);
					break;
				case 6:
					App->render->Blit(graphics, i * 8, var * 8, &tile6);
					break;
				case 7:
					App->render->Blit(graphics, i * 8, var * 8, &tile7);
					break;
				case 8:
					App->render->Blit(graphics, i * 8, var * 8, &tile8);
					break;
				case 9:
					App->render->Blit(graphics, i * 8, var * 8, &tile9);
					break;
				case '_':
					App->render->Blit(graphics, i * 8, var * 8, &tile_);
					break;
				case 'H':
					App->render->Blit(graphics, i * 8, var * 8, &tileH);
					break;
				case 'I':
					App->render->Blit(graphics, i * 8, var * 8, &tileI);
					break;
				case 'G':
					App->render->Blit(graphics, i * 8, var * 8, &tileG);
					break;
				case 'S':
					App->render->Blit(graphics, i * 8, var * 8, &tileS);
					break;
				case 'C':
					App->render->Blit(graphics, i * 8, var * 8, &tileC);
					break;
				case 'O':
					App->render->Blit(graphics, i * 8, var * 8, &tileO);
					break;
				case 'R':
					App->render->Blit(graphics, i * 8, var * 8, &tileR);
					break;
				case 'E':
					App->render->Blit(graphics, i * 8, var * 8, &tileE);
					break;
				case 'U':
					App->render->Blit(graphics, i * 8, var * 8, &tileU);
					break;
				case 'P':
					App->render->Blit(graphics, i * 8, var * 8, &tileP);
					break;
				case 'D':
					App->render->Blit(graphics, i * 8, var * 8, &tileD);
					break;
				case 'T':
					App->render->Blit(graphics, i * 8, var * 8, &tileT);
					break;
				}
			}
			i++;
		}
	}
	else{
		while (i < 28)
		{
			for (int j = 0, var = 0; j < 5; j++, var++)
			{
				if (j == 3){
					var = 34;
				}
				switch (mapUI[j][i])
				{
				case 0:
					App->render->Blit(graphics, i * 8, var * 8, &tile0);
					break;
				case 1:
					App->render->Blit(graphics, i * 8, var * 8, &tile1);
					break;
				case 2:
					App->render->Blit(graphics, i * 8, var * 8, &tile2);
					break;
				case 3:
					App->render->Blit(graphics, i * 8, var * 8, &tile3);
					break;
				case 4:
					App->render->Blit(graphics, i * 8, var * 8, &tile4);
					break;
				case 5:
					App->render->Blit(graphics, i * 8, var * 8, &tile5);
					break;
				case 6:
					App->render->Blit(graphics, i * 8, var * 8, &tile6);
					break;
				case 7:
					App->render->Blit(graphics, i * 8, var * 8, &tile7);
					break;
				case 8:
					App->render->Blit(graphics, i * 8, var * 8, &tile8);
					break;
				case 9:
					App->render->Blit(graphics, i * 8, var * 8, &tile9);
					break;
				case '_':
					App->render->Blit(graphics, i * 8, var * 8, &tile_);
					break;
				case 'H':
					App->render->Blit(graphics, i * 8, var * 8, &tileH);
					break;
				case 'I':
					App->render->Blit(graphics, i * 8, var * 8, &tileI);
					break;
				case 'G':
					App->render->Blit(graphics, i * 8, var * 8, &tileG);
					break;
				case 'S':
					App->render->Blit(graphics, i * 8, var * 8, &tileS);
					break;
				case 'C':
					App->render->Blit(graphics, i * 8, var * 8, &tileC);
					break;
				case 'O':
					App->render->Blit(graphics, i * 8, var * 8, &tileO);
					break;
				case 'R':
					App->render->Blit(graphics, i * 8, var * 8, &tileR);
					break;
				case 'E':
					App->render->Blit(graphics, i * 8, var * 8, &tileE);
					break;
				case 'U':
					App->render->Blit(graphics, i * 8, var * 8, &tileU);
					break;
				case 'P':
					App->render->Blit(graphics, i * 8, var * 8, &tileP);
					break;
				case 'D':
					App->render->Blit(graphics, i * 8, var * 8, &tileD);
					break;
				case 'T':
					App->render->Blit(graphics, i * 8, var * 8, &tileT);
				case 100:
					App->render->Blit(graphics, i * 8, var * 8, &pacman1);
					break;
				case 101:
					App->render->Blit(graphics, i * 8, var * 8, &pacman2);
					break;
				case 102:
					App->render->Blit(graphics, i * 8, var * 8, &pacman3);
					break;
				case 103:
					App->render->Blit(graphics, i * 8, var * 8, &pacman4);
					break;
				case 'x':
					for (int i = 0; i < 7; ++i){
						switch (points[i]){
						case 0:
							App->render->Blit(graphics, i * 8, var * 8, &tile0);
							break;
						case 1:
							App->render->Blit(graphics, i * 8, var * 8, &tile1);
							break;
						case 2:
							App->render->Blit(graphics, i * 8, var * 8, &tile2);
							break;
						case 3:
							App->render->Blit(graphics, i * 8, var * 8, &tile3);
							break;
						case 4:
							App->render->Blit(graphics, i * 8, var * 8, &tile4);
							break;
						case 5:
							App->render->Blit(graphics, i * 8, var * 8, &tile5);
							break;
						case 6:
							App->render->Blit(graphics, i * 8, var * 8, &tile6);
							break;
						case 7:
							App->render->Blit(graphics, i * 8, var * 8, &tile7);
							break;
						case 8:
							App->render->Blit(graphics, i * 8, var * 8, &tile8);
							break;
						case 9:
							App->render->Blit(graphics, i * 8, var * 8, &tile9);
							break;
						case 11:
							App->render->Blit(graphics, i * 8, var * 8, &tile_);
							break;
						}
					}
					break;
				}
			}
			i++;
		}
	}


	// Credit
 	int tmp_credit = credit;
	if (tmp_credit <= 99)
	{
		int digits = 0;
		int tmp;
		while (tmp_credit > 0)
		{
			tmp_credit /= 10;
			digits++;
		}

		if (credit == 0)
		{
		}
		else if (digits == 1)
		{
			mapMENU[4][11] = credit;
		}
		else
		{
			cd1 = credit % 10;
			cd2 = (credit / 10) % 10;
			mapMENU[4][10] = cd2;
			mapMENU[4][11] = cd1;

		}
	}

	 //Lifes
	if (!App->menu->IsEnabled())
	{
		if (App->player->lifes == 5)
		{
			mapUI[3][2] = 100;
			mapUI[3][3] = 102;
			mapUI[4][2] = 101;
			mapUI[4][3] = 103;

			mapUI[3][4] = 100;
			mapUI[3][5] = 102;
			mapUI[4][4] = 101;
			mapUI[4][5] = 103;

			mapUI[3][6] = 100;
			mapUI[3][7] = 102;
			mapUI[4][6] = 101;
			mapUI[4][7] = 103;

			mapUI[3][8] = 100;
			mapUI[3][9] = 102;
			mapUI[4][8] = 101;
			mapUI[4][9] = 103;

		}
		else if (App->player->lifes == 4)
		{
			mapUI[3][2] = 100;
			mapUI[3][3] = 102;
			mapUI[4][2] = 101;
			mapUI[4][3] = 103;

			mapUI[3][4] = 100;
			mapUI[3][5] = 102;
			mapUI[4][4] = 101;
			mapUI[4][5] = 103;

			mapUI[3][6] = 100;
			mapUI[3][7] = 102;
			mapUI[4][6] = 101;
			mapUI[4][7] = 103;

			mapUI[3][8] = '_';
			mapUI[3][9] = '_';
			mapUI[4][8] = '_';
			mapUI[4][9] = '_';

		}
		else if (App->player->lifes == 3)
		{
			mapUI[3][2] = 100;
			mapUI[3][3] = 102;
			mapUI[4][2] = 101;
			mapUI[4][3] = 103;

			mapUI[3][4] = 100;
			mapUI[3][5] = 102;
			mapUI[4][4] = 101;
			mapUI[4][5] = 103;

			mapUI[3][6] = '_';
			mapUI[3][7] = '_';
			mapUI[4][6] = '_';
			mapUI[4][7] = '_';

			mapUI[3][8] = '_';
			mapUI[3][9] = '_';
			mapUI[4][8] = '_';
			mapUI[4][9] = '_';

		}
		else if (App->player->lifes == 2)
		{
			mapUI[3][2] = 100;
			mapUI[3][3] = 102;
			mapUI[4][2] = 101;
			mapUI[4][3] = 103;

			mapUI[3][4] = '_';
			mapUI[3][5] = '_';
			mapUI[4][4] = '_';
			mapUI[4][5] = '_';

			mapUI[3][6] = '_';
			mapUI[3][7] = '_';
			mapUI[4][6] = '_';
			mapUI[4][7] = '_';

			mapUI[3][8] = '_';
			mapUI[3][9] = '_';
			mapUI[4][8] = '_';
			mapUI[4][9] = '_';

		}
		else if (App->player->lifes == 1)
		{
			mapUI[3][2] = '_';
			mapUI[3][3] = '_';
			mapUI[4][2] = '_';
			mapUI[4][3] = '_';

			mapUI[3][4] = '_';
			mapUI[3][5] = '_';
			mapUI[4][4] = '_';
			mapUI[4][5] = '_';

			mapUI[3][6] = '_';
			mapUI[3][7] = '_';
			mapUI[4][6] = '_';
			mapUI[4][7] = '_';

			mapUI[3][8] = '_';
			mapUI[3][9] = '_';
			mapUI[4][8] = '_';
			mapUI[4][9] = '_';

		}
	}

	return UPDATE_CONTINUE;

}
