#include "SDL/include/SDL_timer.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleUI.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleBackground_Map3.h"
#include "ModuleBackground_Map4.h"
#include "ModuleBackground_Intermision1.h"
#include "ModuleMenu.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"

ModuleBackgroundIntermision1::ModuleBackgroundIntermision1()
{

}

ModuleBackgroundIntermision1::~ModuleBackgroundIntermision1()
{}

// Load assets
bool ModuleBackgroundIntermision1::Start()
{
	LOG("Loading Menu.");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Menu.png");

	// Enable and disable modules
	App->player->Disable();
	App->audio->Enable();
	App->ghost_blue->Disable();
	App->ghost_orange->Disable();
	App->ghost_pink->Disable();
	App->ghost_red->Disable();
	App->UI->Disable();

	// Seting time of the start
	//start_time = SDL_GetTicks();

	return ret;
}

// Load assets
bool ModuleBackgroundIntermision1::CleanUp()
{
	LOG("Unloading Menu.");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleBackgroundIntermision1::Update()
{
	// Draw everything --------------------------------------
//	App->render->Blit(graphics, 0, 0, &background, 1.0f);


	return UPDATE_CONTINUE;
}
