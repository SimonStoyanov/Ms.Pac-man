#ifndef __ModuleGhostRed_H__
#define __ModuleGhostRed_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleGhostRed : public Module
{
public:
	ModuleGhostRed();
	~ModuleGhostRed();

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

	// Logic variables 
	bool cont = false;
	int tmp;

	// Ghost start moving time variables
	Uint32 now;
	float time_stoped = 20.5f;  //varaible to change start time
	Uint32 total_time = 0;
	Uint32 start_time = 0;

	// Ghost vulnerable variables
	Uint32 total_time_vuln = 0;
	float time_vulnerable = 6.0f;  //varaible to change vulnerable time
	float passed_time;
	bool is_vulnerable = false;

	Collider* enemy_collision = nullptr;

};

#endif