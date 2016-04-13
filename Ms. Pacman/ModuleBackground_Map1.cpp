#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModuleBackgroundMap1::ModuleBackgroundMap1()
{
	// Map 1

	map1 = { 0, 0, 224, 248 };

	// Power Pills
	PowerPill.PushBack({ 0, 508, 7, 6 });
	PowerPill.PushBack({ 0, 505, 1, 1 });
	PowerPill.speed = 0.035f;
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
	App->collision->Enable();

	// Collisions

	Dot_coll = App->collision->AddCollider({ 50, 50, 2, 2 }, COLLIDER_PILL);
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
	App->render->Blit(graphics, 9, 31, &(PowerPill.GetCurrentFrame()), 1);
	App->render->Blit(graphics, 209, 31, &(PowerPill.GetCurrentFrame()), 1);
	App->render->Blit(graphics, 209, 231, &(PowerPill.GetCurrentFrame()), 1);
	App->render->Blit(graphics, 9, 231, &(PowerPill.GetCurrentFrame()), 1);
	
	if (Dot_coll->to_delete == false){
		App->render->Blit(graphics, 50, 50, &Dot1, 1.0f);
	}
	
	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}
	return UPDATE_CONTINUE;
}
