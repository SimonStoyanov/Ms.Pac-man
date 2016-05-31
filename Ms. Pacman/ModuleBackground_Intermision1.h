#ifndef __INTERMISION_1_H__
#define __INTERMISION_1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleBackgroundIntermision1 : public Module
{
public:
	ModuleBackgroundIntermision1();
	~ModuleBackgroundIntermision1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	//Ghosts


	//Time control


	int credits_used;
};

#endif