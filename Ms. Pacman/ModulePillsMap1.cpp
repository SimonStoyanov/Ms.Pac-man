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

	_PDot[0] = App->collision->AddCollider({ 10, 31, 6, 6 }, COLLIDER_PILL);
	_PDot[1] = App->collision->AddCollider({ 10, 231, 2, 2 }, COLLIDER_PILL);

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
	if (!_PDot[0]->to_delete)
		App->render->Blit(graphics, 9, 31, &(PDot.GetCurrentFrame()), 1);
	

	App->render->Blit(graphics, 209, 31, &(PDot.GetCurrentFrame()), 1);
	App->render->Blit(graphics, 209, 231, &(PDot.GetCurrentFrame()), 1);
	App->render->Blit(graphics, 9, 231, &(PDot.GetCurrentFrame()), 1);

	
	// Load scene when press space

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map1, App->map2, 2.0f);
	}
	return UPDATE_CONTINUE;
}

void ModulePillsMap1::OnCollision(Collider* c1, Collider* c2){
	LOG("\n\n\n------------------Peneeeeeeeeeeeeeeee----------------------\n\n\n");
	for (int i = 0; i <= 220; i++)
	{
		if (c1 != nullptr && c2 == _PDot[i] && c1->type == COLLIDER_PLAYER)
		{
			_PDot[i]->to_delete == true;
		}
	}
}
