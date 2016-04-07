#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 10

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleRender;
class ModuleBackgroundMap1;
class ModuleBackgroundMap2;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleGhostBlue;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleBackgroundMap1* map1;
	ModuleBackgroundMap2* map2;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleGhostBlue* ghost_blue;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__