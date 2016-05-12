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
	float speed = 1.2f;

	SDL_Texture* graphics = nullptr;
	Animation* prev_anim;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation dead;

	fPoint position;
	iPoint p_up;
	iPoint p_down;
	iPoint p_left;
	iPoint p_right;
	iPoint p_mid;

	bool go_up = false;
	bool go_down = false;
	bool go_left = true;
	bool go_right = false;

	SDL_Rect test;
	
	int lifes = 5;

	Uint32 now;
	//Start
	Uint32 start_time = 0;
	Uint32 total_time = 0;
	float total_t = 9.5f;
	
	bool is_dead = false;
	float passed_time;

	Collider* player_collision;
	void OnCollision(Collider* c1, Collider* c2);

	bool wakawaka;
};

#endif