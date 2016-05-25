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
	float speed = 1.0f;
	float extra_speed = 0;

	SDL_Texture* graphics = nullptr;

	Collider* fruit_collision;
	
	int count;
	fPoint position;
	SDL_Rect cherry;
};

#endif // __MODULESCENESPACE_H__