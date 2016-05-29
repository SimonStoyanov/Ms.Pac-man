#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleRender;
class ModuleMenu;
class ModuleBackgroundMap1;
class ModuleBackgroundMap2;
class ModuleBackgroundMap3;
class ModuleEndScreen;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class Module;
class ModuleGhostBlue;
class ModuleGhostOrange;
class ModuleGhostPink;
class ModuleGhostRed;
class ModuleCherry;
class ModuleUI;
class ModuleCollision;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleMenu* menu;
	ModuleBackgroundMap1* map1;
	ModuleBackgroundMap2* map2;
	ModuleBackgroundMap3* map3;
	ModuleEndScreen* end_screen;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleGhostBlue* ghost_blue;
	ModuleGhostOrange* ghost_orange;
	ModuleGhostPink* ghost_pink;
	ModuleGhostRed* ghost_red;
	ModuleCherry* cherry;
	ModuleUI* UI;
	ModuleCollision* collision;
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