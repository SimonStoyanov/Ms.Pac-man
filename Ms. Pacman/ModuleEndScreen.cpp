#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModuleEndScreen::ModuleEndScreen()
{
	// EndScreen
	map1 = { 0, 0, 224, 300};
}

ModuleEndScreen::~ModuleEndScreen()
{}

// Load assets
bool ModuleEndScreen::Start()
{
	LOG("Loading end screen.");
	bool ret = true;
	graphics = App->textures->Load("end_screen.png");

	// Enable and disable modules
	App->player->Disable();
	App->audio->Enable();
	App->ghost_blue->Disable();
	return ret;
}

// Load assets
bool ModuleEndScreen::CleanUp()
{
	LOG("Unloading maps(1) stage.");
	return true;
}

// Update: draw background
update_status ModuleEndScreen::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &map1, 1.0f); // end_screen

	return UPDATE_CONTINUE;
}