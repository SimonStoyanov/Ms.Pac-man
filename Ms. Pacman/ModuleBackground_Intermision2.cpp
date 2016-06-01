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
#include "ModuleBackground_Intermision2.h"
#include "ModuleMenu.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"

ModuleBackgroundIntermision2::ModuleBackgroundIntermision2()
{
	//P1 ------------------------
	// right animation
	right.PushBack({ 33, 1, 15, 14 });
	right.PushBack({ 17, 1, 13, 14 });
	right.PushBack({ 1, 1, 11, 14 });
	right.speed = 0.3f;

	// left animation
	left.PushBack({ 15, 34, 15, 15 });
	left.PushBack({ 33, 34, 15, 15 });
	left.PushBack({ 0, 34, 17, 15 });
	left.speed = 0.3f;

	// up animation
	up.PushBack({ 33, 51, 14, 15 });
	up.PushBack({ 17, 51, 14, 13 });
	up.PushBack({ 1, 51, 14, 11 });
	up.speed = 0.3f;

	// down animation
	down.PushBack({ 33, 17, 14, 15 });
	down.PushBack({ 17, 17, 14, 15 });
	down.PushBack({ 1, 17, 14, 15 });
	down.speed = 0.3f;

	//P2 ------------------------
	// right animation
	right2.PushBack({ 50, 2, 13, 13 });
	right2.PushBack({ 65, 2, 13, 13 });
	right2.PushBack({ 81, 2, 13, 13 });
	right2.speed = 0.3f;

	// left animation
	left2.PushBack({ 50, 34, 13, 13 });
	left2.PushBack({ 66, 34, 13, 13 });
	left2.PushBack({ 81, 2, 13, 13 });
	left2.speed = 0.3f;

	// up animation
	up2.PushBack({ 50, 53, 13, 9 });
	up2.PushBack({ 65, 51, 13, 12 });
	up2.PushBack({ 81, 2, 13, 13 });
	up2.speed = 0.3f;

	// down animation
	down2.PushBack({ 50, 18, 13, 13 });
	down2.PushBack({ 66, 18, 13, 13 });
	down2.PushBack({ 81, 2, 13, 13 });
	down2.speed = 0.3f;

	// misc ------------------------
	claqueta.PushBack({ 0, 0, 33, 33 });
	claqueta.PushBack({ 37, 0, 33, 33 });
	claqueta.PushBack({ 75, 0, 33, 33 });
	claqueta.speed = 0.3f;
}

ModuleBackgroundIntermision2::~ModuleBackgroundIntermision2()
{}

// Load assets
bool ModuleBackgroundIntermision2::Start()
{
	LOG("Loading Menu.");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Pac-man & Ghosts.png");
	misc = App->textures->Load("Sprites/Misc.png");

	// Enable and disable modules
	App->player->Disable();
	App->audio->Enable();
	App->ghost_blue->Disable();
	App->ghost_orange->Disable();
	App->ghost_pink->Disable();
	App->ghost_red->Disable();
	App->UI->Disable();

	// Seting time of the start
	start_time = SDL_GetTicks();

	player.x = -60;
	player.y = 100;

	player2.x = 0;
	player2.y = 100;

	claquet.x = 97;
	claquet.y = 110;

	one_time = true;
	return ret;
}

// Load assets
bool ModuleBackgroundIntermision2::CleanUp()
{
	LOG("Unloading Menu.");
	App->textures->Unload(graphics);
	App->audio->Disable();

	player.x = 250;
	player.y = 150;

	player2.x = -30;
	player2.y = 100;

	claquet.x = 97;
	claquet.y = 110;

	one_time = true;
	return true;
}

// Update: draw background
update_status ModuleBackgroundIntermision2::Update()
{
	now = SDL_GetTicks() - start_time;
	if (now > 22000.0f && one_time)
	{
		App->fade->FadeToBlack(App->intermision2, App->map3, 1.0f); //1
		one_time = false;
	}
	else if (now > 18400.0f){
		App->render->Blit(graphics, player.x, player.y, &right.GetCurrentFrame(), 1.0f);
		player.x += 3.75f;

		App->render->Blit(graphics, player2.x, player2.y, &right2.GetCurrentFrame(), 1.0f);
		player2.x += 3.5f;
	}
	else if (now > 18340.0f){
		player.x = -60;
		player.y = 100;

		player2.x = 0;
		player2.y = 100;
	}
	else if (now > 16400.0f){
		App->render->Blit(graphics, player.x, player.y, &left.GetCurrentFrame(), 1.0f);
		player.x -= 3.5f;

		App->render->Blit(graphics, player2.x, player2.y, &left2.GetCurrentFrame(), 1.0f);
		player2.x -= 3.75f;
	}
	else if (now > 16340.0f){
		player.x = 250;
		player.y = 175;

		player2.x = 310;
		player2.y = 175;
	}
	else if (now > 11800.0f){
		App->render->Blit(graphics, player.x, player.y, &right.GetCurrentFrame(), 1.0f);
		player.x += 2.0f;

		App->render->Blit(graphics, player2.x, player2.y, &right2.GetCurrentFrame(), 1.0f);
		player2.x += 1.75f;
	}
	else if (now > 11710.0f){
		player.x = -60;
		player.y = 100;

		player2.x = 0;
		player2.y = 100;
	}
	else if (now > 7700.0f){
		App->render->Blit(graphics, player.x, player.y, &left.GetCurrentFrame(), 1.0f);
		player.x -= 1.75f;

		App->render->Blit(graphics, player2.x, player2.y, &left2.GetCurrentFrame(), 1.0f);
		player2.x -= 2.0f;
	}
	else if (now > 7660.0f){
		player.x = 250;
		player.y = 175;

		player2.x = 310;
		player2.y = 175;
	}
	else if (now > 3710.0f)
	{
		App->render->Blit(graphics, player.x, player.y, &right.GetCurrentFrame(), 1.0f);
		player.x += 2.0f;

		App->render->Blit(graphics, player2.x, player2.y, &right2.GetCurrentFrame(), 1.0f);
		player2.x += 1.75f;
	}
	else if (now > 3.4 * 0.5f * 1000.0f)
	{
		claqueta.speed = 0.0f;
		App->render->Blit(misc, claquet.x, claquet.y, &claqueta.GetCurrentFrame(), 1.0f);
		App->render->Blit(App->UI->graphics, claquet.x + 22, claquet.y + 23, &App->UI->tile2, 1.0f);
	}
	else if (now > 3 * 0.5f * 1000.0f)
	{
		claqueta.speed = 0.3f;
		App->render->Blit(misc, claquet.x, claquet.y, &claqueta.GetCurrentFrame(), 1.0f);
		App->render->Blit(App->UI->graphics, claquet.x + 22, claquet.y + 23, &App->UI->tile2, 1.0f);
	}
	else if (now > 0.5 * 0.5f * 1000.0f)
	{
		claqueta.speed = 0;
		App->render->Blit(misc, claquet.x, claquet.y, &claqueta.GetCurrentFrame(), 1.0f);
		App->render->Blit(App->UI->graphics, claquet.x + 22, claquet.y + 23, &App->UI->tile2, 1.0f);
	}


	return UPDATE_CONTINUE;
}
