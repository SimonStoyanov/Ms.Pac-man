#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack();
	~ModuleFadeToBlack();

	bool Start();
	update_status Update();
	void FadeToBlack(Module* module_off, Module* module_on, float time = 2.0f);
	Module* off;
	Module* on;

private:

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	bool fading_in = true;
};

#endif //__MODULEFADETOBLACK_H__