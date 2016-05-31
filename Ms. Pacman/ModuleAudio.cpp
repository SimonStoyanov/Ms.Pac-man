#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBackground_Map1.h"
#include "ModuleEndScreen.h"



ModuleAudio::~ModuleAudio()
{}

// Load assets
bool ModuleAudio::Start()
{
	LOG("Loading audio");

	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	start_of_a_game = Mix_LoadMUS("Sounds/start_of_a_game.ogg");
	wakawaka = Mix_LoadWAV("Sounds/wakawaka.wav");
	powerpill = Mix_LoadWAV("Sounds/PowerPill.wav");
	eatenghost = Mix_LoadWAV("Sounds/EatenGhost.wav");
	ghostmovement = Mix_LoadWAV("Sounds/GhostMovement.wav"); // Channel 3
	death = Mix_LoadWAV("Sounds/Death.wav");
	fruitmovement = Mix_LoadWAV("Sounds/FruitMovement.wav"); // Channel 4 
	eatenfruit = Mix_LoadWAV("Sounds/EatenFruit.wav"); // Channel 4 
	extralife = Mix_LoadWAV("Sounds/ExtraLife.wav"); // Channel 5

	Mix_PlayMusic(start_of_a_game, 1);	
	Mix_PlayChannel(3, App->audio->ghostmovement, -1);
	Mix_Pause(3);
	return true;
}

ModuleAudio::ModuleAudio()
{
}

// UnLoad assets
bool ModuleAudio::CleanUp()
{
	LOG("Unloading space scene");

	Mix_CloseAudio();
	start_of_a_game = Mix_LoadMUS("Sounds/start_of_a_game.ogg");
	wakawaka = Mix_LoadWAV("Sounds/wakawaka.wav");
	powerpill = Mix_LoadWAV("Sounds/PowerPill.wav");
	eatenghost = Mix_LoadWAV("Sounds/EatenGhost.wav");
	ghostmovement = Mix_LoadWAV("Sounds/GhostMovement.wav"); // Channel 3
	death = Mix_LoadWAV("Sounds/Death.wav");
	fruitmovement = Mix_LoadWAV("Sounds/FruitMovement.wav"); // Channel 4 
	eatenfruit = Mix_LoadWAV("Sounds/EatenFruit.wav"); // Channel 4 
	extralife = Mix_LoadWAV("Sounds/ExtraLife.wav"); // Channel 5
	Mix_FreeChunk(extralife);
	Mix_FreeChunk(eatenfruit);
	Mix_FreeChunk(fruitmovement);
	Mix_FreeChunk(death);
	Mix_FreeChunk(ghostmovement);
	Mix_FreeChunk(eatenghost);
	Mix_FreeChunk(powerpill);
	Mix_FreeChunk(wakawaka);
	Mix_FreeMusic(start_of_a_game);

	return true;
}

// Update: draw background
update_status ModuleAudio::Update()
{

	return UPDATE_CONTINUE;
}