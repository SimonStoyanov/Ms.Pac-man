#include "Globals.h"
#include "Application.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

ModuleBackgroundMap1::ModuleBackgroundMap1()
{
	// Map 1
	map1 = {0, 0, 224, 248};

	//// flag animation
	//water.PushBack({8, 447, 283, 9});
	//water.PushBack({296, 447, 283, 12});
	//water.PushBack({588, 447, 283, 18});
	//water.speed = 0.02f;
}

ModuleBackgroundMap1::~ModuleBackgroundMap1()
{}

// Load assets
bool ModuleBackgroundMap1::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("maps.png");

	// Enable and disable modules
	App->player->Enable();
	App->audio->Enable();
	return ret;
}

// Load assets
bool ModuleBackgroundMap1::CleanUp()
{
	LOG("Unloading Map1 stage.");
	return true;
}

// Update: draw background
update_status ModuleBackgroundMap1::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 2, 15, &map1, 1.0f); // map 1
	
	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0F);
	}
	return UPDATE_CONTINUE;
}