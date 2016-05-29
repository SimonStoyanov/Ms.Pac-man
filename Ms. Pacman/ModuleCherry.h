#ifndef __MODULECHERRY_H__
#define __MODULECHERRY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
// 23 seconds to appear
class ModuleCherry : public Module
{
public:
	ModuleCherry();
	~ModuleCherry();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	float speed = 0.8f;
	float extra_speed = 0;

	SDL_Texture* graphics = nullptr;

	Collider* fruit_collision;
	
	int count;

	fPoint position;
	iPoint p_up;
	iPoint p_down;
	iPoint p_left;
	iPoint p_right;
	iPoint p_mid;

	SDL_Rect test;

	SDL_Rect cherry;
	SDL_Rect strawberry;
	SDL_Rect orange;

	//Animation vars
	fPoint render_pos;
	int pixels_up;

	// Cherry core Movement
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
	float time_stoped = 6.0f;  //varaible to change start time
	Uint32 total_time = 0;
	Uint32 start_time = 0;

	float passed_cherry;

	float p_position_x;
	float p_position_y;

	bool random = false;

	bool play_audio = false;
};

#endif // __MODULESCENESPACE_H__