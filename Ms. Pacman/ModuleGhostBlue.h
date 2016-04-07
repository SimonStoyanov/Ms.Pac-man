#ifndef __ModuleGhostBlue_H__
#define __ModuleGhostBlue_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleGhostBlue : public Module
{
public:
	ModuleGhostBlue();
	~ModuleGhostBlue();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	Animation* prev_anim;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation vulnerable;
	iPoint position;


};

#endif