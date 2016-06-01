#ifndef __INTERMISION_3_H__
#define __INTERMISION_3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleBackgroundIntermision3 : public Module
{
public:
	ModuleBackgroundIntermision3();
	~ModuleBackgroundIntermision3();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* misc = nullptr;
	Animation* prev_anim;

	//Player 1
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	fPoint player;

	//Player 2
	Animation right2;
	Animation left2;
	Animation up2;
	Animation down2;
	fPoint player2;

	//Pink
	Animation rightp;
	Animation leftp;
	Animation upp;
	Animation downp;
	fPoint pink;

	//Blue
	Animation rightb;
	Animation leftb;
	Animation upb;
	Animation downb;
	fPoint blue;

	//Misc
	Animation claqueta;
	Animation hearth;
	fPoint claquet;
	Animation cigueña;
	fPoint ciguenya;
	Animation bebe;
	Animation bebe2;
	fPoint beb;

	//Time control
	Uint32 now;
	Uint32 start_time = 0;
	bool one_time = true;



	int credits_used;
};

#endif