#ifndef __UI__
#define __UI__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* gscore = nullptr;

	// Tiles
	SDL_Rect tile0;
	SDL_Rect tile1;
	SDL_Rect tile2;
	SDL_Rect tile3;
	SDL_Rect tile4;
	SDL_Rect tile5;
	SDL_Rect tile6;
	SDL_Rect tile7;
	SDL_Rect tile8;
	SDL_Rect tile9;
	
	SDL_Rect tileH;
	SDL_Rect tileI;
	SDL_Rect tileG;
	SDL_Rect tileS;
	SDL_Rect tileC;
	SDL_Rect tileO;
	SDL_Rect tileR;
	SDL_Rect tileE;
	SDL_Rect tile_;

	SDL_Rect tileU;
	SDL_Rect tileP;
	SDL_Rect tileD;
	SDL_Rect tileT;

	SDL_Rect pacman1;
	SDL_Rect pacman2;
	SDL_Rect pacman3;
	SDL_Rect pacman4;

	

	// Map array
	char mapMENU[5][28];
	char mapUI[5][28];

	//Puntuation
	int points[7];

	int digit1;
	int digit2;
	int digit3;
	int digit4;
	int digit5;
	int digit6;
	int digit7;

	//Credit
	int credit = 0;
	int cd1 = 0;
	int cd2 = 0;

	// Score P1
	int score = 0;
	int sc1 = 0;
	int sc2 = 0;
	int sc3 = 0;
	int sc4 = 0;
	int sc5 = 0;
	int sc6 = 0;
	int sc7 = 0;

	// Score P2
	int _score = 0;
	int _sc1 = 0;
	int _sc2 = 0;
	int _sc3 = 0;
	int _sc4 = 0;
	int _sc5 = 0;
	int _sc6 = 0;
	int _sc7 = 0;

	// ghost score
	SDL_Rect g200;
	SDL_Rect g400;
	SDL_Rect g800;
	SDL_Rect g1600;

	// fruit score
	SDL_Rect f100;
	SDL_Rect f200;
	SDL_Rect f500;
	SDL_Rect f700;
	SDL_Rect f1000;
	SDL_Rect f2000;
	SDL_Rect f5000;

	// Ready!
	SDL_Rect Ready;

	// Game Over
	SDL_Rect GameOver;
};

#endif 