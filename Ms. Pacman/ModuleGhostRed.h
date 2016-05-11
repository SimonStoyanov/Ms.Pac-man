#ifndef __ModuleGhostRed_H__
#define __ModuleGhostRed_H__

#include "Globals.h"
#include "Application.h"
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
	Animation vulnerable_end;

	SDL_Rect test;

	fPoint position;
	iPoint p_up;
	iPoint p_down;
	iPoint p_left;
	iPoint p_right;
	iPoint p_mid;

	float speed = 1.0f;

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

	// Ghost start moving time variables
	Uint32 now;
	float time_stoped = 6.0f;  //varaible to change start time
	Uint32 total_time = 0;
	Uint32 start_time = 0;

	// Ghost vulnerable variables
	Uint32 total_time_vuln = 0;
	float time_vulnerable = 9.0f;  //varaible to change vulnerable time
	float passed_time;
	bool is_vulnerable = false;

	Collider* enemy_collision = nullptr;
	void WhatIsNextTile();



};

#endif