#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	Animation* prev_anim;
	Animation right;
	Animation left;
	Animation up;
	Animation down;

	iPoint position;
	iPoint player_tile;

	bool go_up = false;
	bool go_down = false;
	bool go_left = true;
	bool go_right = false;
	


	bool wakawaka;
};

#endif