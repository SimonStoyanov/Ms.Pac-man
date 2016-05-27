#ifndef __ENDSCREEN_H__
#define __ENDSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleEndScreen : public Module
{
public:
	ModuleEndScreen();
	~ModuleEndScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect roof;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation water;
	SDL_Rect map1;

	bool pressed_space;
};

#endif 