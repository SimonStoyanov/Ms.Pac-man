#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModulePillsMap1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModulePillsMap1::ModulePillsMap1()
{
	// Power Pills

}

ModulePillsMap1::~ModulePillsMap1()
{}

// Load assets
bool ModulePillsMap1::Start()
{
	LOG("Loading maps(1).");
	bool ret = true;
	graphics = App->textures->Load("void_maps.png");

	// Enable and disable modules

	return ret;
}

// Load assets
bool ModulePillsMap1::CleanUp()
{
	LOG("Unloading maps(1) stage.");
	return true;
}

// Update: draw background
update_status ModulePillsMap1::Update()
{


	return UPDATE_CONTINUE;
}

