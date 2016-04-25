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

	SDL_Rect test;

	iPoint position;
	iPoint p_up;
	iPoint p_down;
	iPoint p_left;
	iPoint p_right;
	iPoint p_mid;

	// Ghost Movement
	bool go_up = false;
	bool go_down = false;
	bool go_left = false;
	bool go_right = false;

	bool ghost_up = false;
	bool ghost_down = false;
	bool ghost_left = false;
	bool ghost_right = false;

	// Ghost Random Input
	bool can_go_up = false;
	bool can_go_down = false;
	bool can_go_left = false;
	bool can_go_right = false;

	bool change_direction = false;

	bool cont = false;

	int tmp;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	float total_t = 9.5f;


};

#endif