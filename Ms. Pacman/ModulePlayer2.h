#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

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
	bool go_left = false;
	bool go_right = true;

	SDL_Rect test;

	bool can_see = true;

	Collider* player_collision;
	void OnCollision(Collider* c1, Collider* c2);

	int eaten_ghost = 0;

};

#endif