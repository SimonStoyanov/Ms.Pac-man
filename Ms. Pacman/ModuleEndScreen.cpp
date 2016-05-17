#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleMenu.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModulePlayer2.h"
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
	App->player2->Disable();
	App->audio->Enable();
	App->ghost_blue->Disable();
	App->map1->Disable();
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
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->end_screen, App->menu, 2.0f);
	}
	return UPDATE_CONTINUE;
}