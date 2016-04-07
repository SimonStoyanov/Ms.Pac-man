#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleMenu : public Module
{
public:
	ModuleMenu();
	~ModuleMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	//Screen efects
	Animation Rectangle;
	
	//Ghosts
	Animation Red_up;
	Animation Red_left;
	iPoint red;

	Animation Blue_up;
	Animation Blue_left;
	iPoint blue;

	Animation Orange_up;
	Animation Orange_left;
	iPoint orange;

	Animation Pink_up;
	Animation Pink_left;
	iPoint pink;
	
	SDL_Rect background;

	//Time control
	Uint32 start_time = 0;
	Uint32 total_time_red = 0;
	float time_red = 1.0f; // red timer
	Uint32 total_time_blue = 0;
	float time_blue = 13.0f; // blue timer
	Uint32 total_time_orange = 0;
	float time_orange = 30.0f; // orange timer
	Uint32 total_time_pink = 0;
	float time_pink = 7.0f; // pink timer
};

#endif