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
	fPoint red;

	Animation Blue_up;
	Animation Blue_left;
	fPoint blue;

	Animation Orange_up;
	Animation Orange_left;
	fPoint orange;

	Animation Pink_up;
	Animation Pink_left;
	fPoint pink;

	Animation Pacman_up;
	Animation Pacman_left;
	fPoint pacman;
	
	SDL_Rect background;

	SDL_Rect Blinky;
	SDL_Rect Pinky;
	SDL_Rect Sue;
	SDL_Rect Inky;
	SDL_Rect Starring;
	SDL_Rect With;
	SDL_Rect MsPacMan;
	SDL_Rect voidspace;

	//Time control
	Uint32 start_time = 0;
	Uint32 total_time_red = 0;
	float time_red = 0.0f; // red timer
	Uint32 total_time_blue = 0;
	float time_blue = 10.0f; // blue timer
	Uint32 total_time_orange = 0;
	float time_orange = 15.0f; // orange timer
	Uint32 total_time_pink = 0;
	float time_pink = 5.0f; // pink timer
	Uint32 total_time_pacman = 0;
	float time_pacman = 20.0f; // pacman timer

	bool one_time = true;
};

#endif