#ifndef __MAP2_H__
#define __MAP2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackgroundMap2 : public Module
{
public:
	ModuleBackgroundMap2();
	~ModuleBackgroundMap2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation PowerPill;

	SDL_Rect Dot1;

	int eaten_dots = 0;

	// 220 pills and 4 PowerPills

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
	SDL_Rect tile10;
	SDL_Rect tile11;
	SDL_Rect tile12;
	SDL_Rect tile13;
	SDL_Rect tile14;
	SDL_Rect tile15;
	SDL_Rect tile16;
	SDL_Rect tile17;
	SDL_Rect tile18;
	SDL_Rect tile19;
	SDL_Rect tile20;
	SDL_Rect tile21;
	SDL_Rect tile22;
	SDL_Rect tile23;
	SDL_Rect tile24;
	SDL_Rect tile25;
	SDL_Rect tile26;
	SDL_Rect tile27;
	SDL_Rect tilePILL;
	SDL_Rect tilepill;
	SDL_Rect tilehouse;

	// Extra tiles
	SDL_Rect tile28;
	SDL_Rect tile29;
	SDL_Rect tile30;
	SDL_Rect tile31;

	//iPoint player_tile_position;
	char map2[31][28];
	int eaten_pills = 0;
};

#endif