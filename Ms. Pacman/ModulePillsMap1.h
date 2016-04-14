#ifndef __PILLMAP1_H__
#define __PILLMAP1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModulePillsMap1 : public Module
{
public:
	ModulePillsMap1();
	~ModulePillsMap1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation PowerPill;

	// 220 pills and 4 PowerPills
	SDL_Rect Dot[220];
	Collider* _Dot[220];
	void _Dot_to_nullptr() {
		for (int i = 0; i < 220; i++){
			_Dot[i] = nullptr;
		}
	}
	SDL_Rect PDot[4];
	Collider* _PDot[4];
	void _PDot_to_nullptr(){
		for (int i = 0; i < 4; i++){
			_PDot[i] = nullptr;
		}
	}


};

#endif 