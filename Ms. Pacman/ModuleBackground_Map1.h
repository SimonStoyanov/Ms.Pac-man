#ifndef __MAP1_H__
#define __MAP1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackgroundMap1 : public Module
{
public:
	ModuleBackgroundMap1();
	~ModuleBackgroundMap1();

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
};

#endif 