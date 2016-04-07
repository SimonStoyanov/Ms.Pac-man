#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModuleBackgroundMap1::ModuleBackgroundMap1()
{
	// Map 1
	map1 = { 0, 0, 224, 248 };
}

ModuleBackgroundMap1::~ModuleBackgroundMap1()
{}

// Load assets
bool ModuleBackgroundMap1::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("void_maps.png");

	// Enable and disable modules
	App->player->Enable();
	App->audio->Enable();
	App->ghost_blue->Enable();
	return ret;
}

// Load assets
bool ModuleBackgroundMap1::CleanUp()
{
	LOG("Unloading maps(1) stage.");
	return true;
}

// Update: draw background
update_status ModuleBackgroundMap1::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 1, 15, &map1, 1.0f); // map 1

	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}
	return UPDATE_CONTINUE;
}