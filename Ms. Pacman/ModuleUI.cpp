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

	g200 = { 1, 28, 15, 7 }; g400 = { 19, 28, 15, 7 }; g800 = { 37, 28, 15, 7 }; g1600 = { 1, 37, 16, 7 };
}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("Letters & Numbers.png");
	gscore = App->textures->Load("Score.png");

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
		{ '_','_','_', 1, 'U','P','_','_','_','H','I','G','H','_','S','C','O','R','E', '_','_','_', 2, 'U','P', '_','_','_'}, //1
		{ 'x','x','x','x','x','x','x', '_','_','_','_','_','_','_','_','_','_','_','_','y','y','y','y','y','y','y','_','_' }, //2
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
	// One player or Two player
	if (App->player->two_players == false){
		mapMENU[0][22] = '_';
		mapMENU[0][23] = '_';
		mapMENU[0][24] = '_';
		mapMENU[1][24] = '_';
		mapMENU[1][25] = '_';
		mapUI[0][22] = '_';
		mapUI[0][23] = '_';
		mapUI[0][24] = '_';
		mapUI[1][24] = '_';
		mapUI[1][25] = '_';
	}
	else{
		mapMENU[0][22] = 2;
		mapMENU[0][23] = 'U';
		mapMENU[0][24] = 'P';
		mapMENU[1][24] = 0;
		mapMENU[1][25] = 0;
		mapUI[0][22] = 2;
		mapUI[0][23] = 'U';
		mapUI[0][24] = 'P';
		
	}
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
				}
			}
			i++;
		}
	}

	// Credit Sistem
 	int tmp_credit = credit;
	if (tmp_credit <= 99)
	{
		int cddigits = 0;
		int tmp;
		while (tmp_credit > 0)
		{
			tmp_credit /= 10;
			cddigits++;
		}
		if (cddigits == 1)
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

	// Score P1
	int tmp_score = score;
	if (tmp_score <= 9999999)
	{
		int scdigits = 0;
		int tmp;
		while (tmp_score > 0)
		{
			tmp_score /= 10;
			scdigits++;
		}
		if (scdigits == 1)
		{
			mapUI[1][6] = score;
		}
		if (scdigits == 2)
		{
			mapUI[1][5] = score;
		}
		if (scdigits == 3)
		{
			mapUI[1][4] = score;
		}
		if (scdigits == 4)
		{
			mapUI[1][3] = score;
		}
		if (scdigits == 5)
		{
			mapUI[1][2] = score;
		}
		if (scdigits == 6)
		{
			mapUI[1][1] = score;
		}
		if (scdigits == 7)
		{
			mapUI[1][0] = score;
		}
		else
		{
			sc1 = score % 10;
			sc2 = (score / 10) % 10;
		
			if (scdigits >= 3)
				sc3 = (score / 100) % 10;
			else
				sc3 = '_';
			
			if (scdigits >= 4)
				sc4 = (score / 1000) % 10;
			else
				sc4 = '_';
			
			if (scdigits >= 5)
				sc5 = (score / 10000) % 10;
			else
				sc5 = '_';
			
			if (scdigits >= 6)
				sc6 = (score / 100000) % 10;
			else
				sc6 = '_';
			
			if (scdigits == 7)
				sc7 = (score / 1000000) % 10;
			else
				sc7 = '_';
		
			mapUI[1][0] = sc7;
			mapUI[1][1] = sc6;
			mapUI[1][2] = sc5;
			mapUI[1][3] = sc4;
			mapUI[1][4] = sc3;			
			mapUI[1][5] = sc2;
			mapUI[1][6] = sc1;
		}
	}

	// Score P2
	int _tmp_score = _score;
	if (_tmp_score <= 9999999)
	{
		int _scdigits = 0;
		int _tmp;
		while (_tmp_score > 0)
		{
			_tmp_score /= 10;
			_scdigits++;
		}
		if (_scdigits == 1)
		{
			mapUI[1][26] = _score;
		}
		if (_scdigits == 2)
		{
			mapUI[1][24] = _score;
		}
		if (_scdigits == 3)
		{
			mapUI[1][23] = _score;
		}
		if (_scdigits == 4)
		{
			mapUI[1][22] = _score;
		}
		if (_scdigits == 5)
		{
			mapUI[1][21] = _score;
		}
		if (_scdigits == 6)
		{
			mapUI[1][20] = _score;
		}
		if (_scdigits == 7)
		{
			mapUI[1][19] = _score;
		}
		else
		{
			_sc1 = _score % 10;
			_sc2 = (_score / 10) % 10;

			if (_scdigits >= 3)
				_sc3 = (_score / 100) % 10;
			else
				_sc3 = '_';

			if (_scdigits >= 4)
				_sc4 = (_score / 1000) % 10;
			else
				_sc4 = '_';

			if (_scdigits >= 5)
				_sc5 = (_score / 10000) % 10;
			else
				_sc5 = '_';

			if (_scdigits >= 6)
				_sc6 = (_score / 100000) % 10;
			else
				_sc6 = '_';

			if (_scdigits == 7)
				_sc7 = (_score / 1000000) % 10;
			else
				_sc7 = '_';

			mapUI[1][19] = _sc7;
			mapUI[1][20] = _sc6;
			mapUI[1][21] = _sc5;
			mapUI[1][22] = _sc4;
			mapUI[1][23] = _sc3;
			mapUI[1][24] = _sc2;
			mapUI[1][25] = _sc1;
		}
	}

	// HighScore
	if (_score > score){
		mapUI[1][11] = _sc7;
		mapUI[1][12] = _sc6;
		mapUI[1][13] = _sc5;
		mapUI[1][14] = _sc4;
		mapUI[1][15] = _sc3;
		mapUI[1][16] = _sc2;
		mapUI[1][17] = _sc1;
	}
	else{
		mapUI[1][11] = sc7;
		mapUI[1][12] = sc6;
		mapUI[1][13] = sc5;
		mapUI[1][14] = sc4;
		mapUI[1][15] = sc3;
		mapUI[1][16] = sc2;
		mapUI[1][17] = sc1;
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
