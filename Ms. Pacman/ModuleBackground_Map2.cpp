#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"



ModuleBackgroundMap2::ModuleBackgroundMap2()
{
	// Map 2
	map2 = { 228, 0, 224, 248 };
}

ModuleBackgroundMap2::~ModuleBackgroundMap2()
{}

// Load assets
bool ModuleBackgroundMap2::Start()
{
	LOG("Loading maps(2).");
	bool ret = true;
	graphics = App->textures->Load("maps.png");

	// Enable and disable modules
	App->player->Enable();
	App->ghost_blue->Enable();
	return ret;
}

// Load assets
bool ModuleBackgroundMap2::CleanUp()
{
	LOG("Unloading maps(2) stage");
	return true;
}

// Update: draw background
update_status ModuleBackgroundMap2::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 2, 15, &map2, 1.0f); // map 1

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->map2, App->end_screen, 2.0F);
	}

	return UPDATE_CONTINUE;
}