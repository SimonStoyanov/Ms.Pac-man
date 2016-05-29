#ifndef __ModuleGhostOrange_H__
#define __ModuleGhostOrange_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleGhostOrange : public Module
{
public:
	ModuleGhostOrange();
	~ModuleGhostOrange();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	float speed = 1.0f;
	float extra_speed = 0;

	SDL_Texture* graphics = nullptr;
	Animation* prev_anim;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation vulnerable;
	Animation vulnerable_end;
	Animation dead_up;
	Animation dead_left;
	Animation dead_right;
	Animation dead_downs;

	SDL_Rect test;
	SDL_Rect test2;

	fPoint position;
	iPoint p_up;
	iPoint p_down;
	iPoint p_left;
	iPoint p_right;
	iPoint p_mid;

	// Ghost core Movement
	bool go_up = false;
	bool go_down = false;
	bool go_left = false;
	bool go_right = false;

	bool ghost_up = false;
	bool ghost_down = false;
	bool ghost_left = false;
	bool ghost_right = false;

	// Choosing direction
	bool can_go_up = false;
	bool can_go_down = false;
	bool can_go_left = false;
	bool can_go_right = false;

	bool want_go_up = false;
	bool want_go_down = false;
	bool want_go_left = false;
	bool want_go_right = false;

	bool change_direction = false;

	// Logic variables 
	bool cont = false;
	int tmp;
	bool can_see = true;

	// Ghost start moving time variables
	Uint32 now;
	float time_stoped = 9.5f;  //varaible to change start time
	Uint32 total_time = 0;
	Uint32 start_time = 0;

	// Ghost vulnerable variables
	Uint32 total_time_vuln = 0;
	float time_vulnerable = 9.0f;  //varaible to change vulnerable time
	float passed_time;
	bool is_vulnerable = false;

	Collider* enemy_collision = nullptr;

	// Box variables
	float passed_box;
	bool in_box = true;
	bool box_up = true;
	bool box_down = false;
	bool box_positioning = false;

	// Dead varables
	bool is_dead;
	bool dead_positioning = false;
	bool dead_down = true;
	bool pre_find = true;

	int p_position_x;
	int p_position_y;
};

#endif