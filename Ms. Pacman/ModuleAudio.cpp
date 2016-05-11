#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBackground_Map1.h"
#include "ModuleEndScreen.h"


ModuleAudio::ModuleAudio()
{}

ModuleAudio::~ModuleAudio()
{}

// Load assets
bool ModuleAudio::Start()
{
	LOG("Loading audio");

	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	start_of_a_game = Mix_LoadMUS("start_of_a_game.ogg");
	wakawaka = Mix_LoadWAV("wakawaka.wav");

	if (App->map1->IsEnabled())
	{
		Mix_PlayMusic(start_of_a_game, 1);	
	}

	return true;
}

// UnLoad assets
bool ModuleAudio::CleanUp()
{
	LOG("Unloading space scene");

	/*Mix_CloseAudio();
	Mix_FreeMusic(start_of_a_game);*/
	//Mix_FreeChunk(wakawaka);

	return true;
}

// Update: draw background
update_status ModuleAudio::Update()
{
	/*if (App->player->wakawaka == true)
	{
		Mix_PlayChannel(-1, wakawaka, 0);
	}
	App->player->wakawaka = false;*/
	return UPDATE_CONTINUE;
}