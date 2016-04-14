#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"

#include "ModuleBackground_Map1.h"
#include "ModulePillsMap1.h"
#include "ModuleBackground_Map2.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModulePillsMap1::ModulePillsMap1()
{
	// Power Pills
	PDot.PushBack({ 0, 508, 7, 6 });
	PDot.PushBack({ 0, 505, 1, 1 });
	PDot.speed = 0.035f;

	_PDot_to_nullptr();
	_Dot_to_nullptr();
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

	// Collisions
	_PDot[0] = App->collision->AddCollider({ 10, 31, 6, 6 }, COLLIDER_POWER_PILL, this);
	_PDot[1] = App->collision->AddCollider({ 210, 31, 6, 6 }, COLLIDER_POWER_PILL, this);
	_PDot[2] = App->collision->AddCollider({ 10, 231, 6, 6 }, COLLIDER_POWER_PILL, this);
	_PDot[3] = App->collision->AddCollider({ 210, 231, 6, 6 }, COLLIDER_POWER_PILL, this);

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
	// Draw everything --------------------------------------
	if (_PDot[0]->to_delete == false){
		App->render->Blit(graphics, 9, 31, &(PDot.GetCurrentFrame()), 1.0f);
	}
	else;
	if (_PDot[1]->to_delete == false){
		App->render->Blit(graphics, 209, 31, &(PDot.GetCurrentFrame()), 1.0f);
	}
	else;
	if (_PDot[2]->to_delete == false){
		App->render->Blit(graphics, 9, 231, &(PDot.GetCurrentFrame()), 1.0f);
	}
	else;
	if (_PDot[3]->to_delete == false){
		App->render->Blit(graphics, 209, 231, &(PDot.GetCurrentFrame()), 1.0f);
	}
	else;

	
	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2){
	LOG("\n\n\n------------------Player: I've collided----------------------\n\n\n");
	if (c1 != nullptr && c2->type == COLLIDER_POWER_PILL){
		c2->to_delete = true;
	}
}
