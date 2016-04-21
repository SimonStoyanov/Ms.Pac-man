#ifndef __PILLMAP1_H__
#define __PILLMAP1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModulePillsMap1 : public Module
{
public:
	ModulePillsMap1();
	~ModulePillsMap1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	
	

};

#endif 