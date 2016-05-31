#ifndef __INTERMISION_1_H__
#define __INTERMISION_1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleBackgroundIntermision1 : public Module
{
public:
	ModuleBackgroundIntermision1();
	~ModuleBackgroundIntermision1();

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

	//Time control
	Uint32 now;
	Uint32 start_time = 0;
	bool one_time = true;



	int credits_used;
};

#endif