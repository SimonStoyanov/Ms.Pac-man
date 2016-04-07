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
	Animation Orange_up;
	Animation Orange_left;
	Animation Pink_up;
	Animation Pink_left;
	
	SDL_Rect background;

	Uint32 start_time = 0;
	Uint32 total_time_red = 0;
	Uint32 total_time_blue = 0;
	Uint32 total_time_orange = 0;
	Uint32 total_time_pink = 0;
	float time = 2.0f;
};

#endif