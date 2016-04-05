#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


ModuleAudio::ModuleAudio()
{}

ModuleAudio::~ModuleAudio()
{}

// Load assets
bool ModuleAudio::Start()
{
	LOG("Loading audio");

	//Mix_Init(MIX_INIT_OGG);
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	//intro_audio = Mix_LoadMUS("rtype/intro.ogg");



	return true;
}

// UnLoad assets
bool ModuleAudio::CleanUp()
{
	LOG("Unloading space scene");

	Mix_CloseAudio();


	Mix_FreeMusic(intro_audio);
	Mix_FreeMusic(ingame_audio);

	return true;
}

// Update: draw background
update_status ModuleAudio::Update()
{
	// Draw everything --------------------------------------

	return UPDATE_CONTINUE;
}