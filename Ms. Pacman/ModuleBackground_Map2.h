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
	SDL_Rect ground;
	SDL_Rect roof;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation water;
	SDL_Rect map2;
};

#endif // __MODULESCENEHONDA_H__