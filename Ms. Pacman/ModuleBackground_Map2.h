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
	SDL_Rect map2;
};

#endif