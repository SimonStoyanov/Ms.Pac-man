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


};

#endif 