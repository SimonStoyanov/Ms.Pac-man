#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleBackground_Map3.h"
#include "ModuleBackground_Map4.h"
#include "ModuleEndScreen.h"
#include "ModuleBackground_Intermision1.h"
#include "ModuleBackground_Intermision2.h"
#include "ModuleBackground_Intermision3.h"

ModuleAudio::~ModuleAudio()
{}

// Load assets
bool ModuleAudio::Start()
{
	LOG("Loading audio");

	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	start_of_a_game = Mix_LoadMUS("Sounds/start_of_a_game.ogg");
	act1 = Mix_LoadMUS("Sounds/act1.ogg");
	act2 = Mix_LoadMUS("Sounds/act2.ogg");
	act3 = Mix_LoadMUS("Sounds/act3.ogg");
	wakawaka = Mix_LoadWAV("Sounds/wakawaka.wav");
	powerpill = Mix_LoadWAV("Sounds/PowerPill.wav");
	eatenghost = Mix_LoadWAV("Sounds/EatenGhost.wav");
	ghostmovement = Mix_LoadWAV("Sounds/GhostMovement.wav"); // Channel 3
	death = Mix_LoadWAV("Sounds/Death.wav");
	fruitmovement = Mix_LoadWAV("Sounds/FruitMovement.wav"); // Channel 4 
	eatenfruit = Mix_LoadWAV("Sounds/EatenFruit.wav"); // Channel 4 
	extralife = Mix_LoadWAV("Sounds/ExtraLife.wav"); // Channel 5

	if (App->map1->IsEnabled() || App->map2->IsEnabled() || App->map3->IsEnabled() || App->map4->IsEnabled())
	{
		Mix_PlayMusic(start_of_a_game, 1);
		Mix_PlayChannel(3, App->audio->ghostmovement, -1);
		Mix_Pause(3);
	}

	if (App->intermision1->IsEnabled()){
		Mix_PlayMusic(act1, 1);
	}
	if (App->intermision2->IsEnabled()){
		Mix_PlayMusic(act2, 1);
	}
	
	if (App->intermision3->IsEnabled()){
		Mix_PlayMusic(act3, 1);
	}
	
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
	act1 = Mix_LoadMUS("Sounds/act1.ogg");
	act2 = Mix_LoadMUS("Sounds/act2.ogg");
	act3 = Mix_LoadMUS("Sounds/act3.ogg");
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
	Mix_FreeMusic(act3);
	Mix_FreeMusic(act2);
	Mix_FreeMusic(act1);
	Mix_FreeMusic(start_of_a_game);

	return true;
}

// Update: draw background
update_status ModuleAudio::Update()
{

	return UPDATE_CONTINUE;
}