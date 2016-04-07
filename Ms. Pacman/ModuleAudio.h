#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* start_of_a_game;
	Mix_Chunk* wakawaka;


};

#endif // __MODULESCENESPACE_H__