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
	claqueta.PushBack({ 0, 0, 33, 33});
	claqueta.PushBack({ 37, 0, 33, 33 });
	claqueta.PushBack({ 75, 0, 33, 33 });
	claqueta.speed = 0.3f;

	hearth.PushBack ({2, 35, 15, 14});


	// Pink ------------------------
	// left animation
	leftp.PushBack({ 113, 97, 14, 14 });
	leftp.PushBack({ 97, 97, 14, 14 });
	leftp.speed = 0.10f;

	// up animation 
	upp.PushBack({ 65, 97, 14, 14 });
	upp.PushBack({ 81, 97, 14, 14 });
	upp.speed = 0.10f;

	// down animation
	downp.PushBack({ 33, 97, 14, 14 });
	downp.PushBack({ 49, 97, 14, 14 });
	downp.speed = 0.10f;

	// right animation
	rightp.PushBack({ 1, 97, 14, 14 });
	rightp.PushBack({ 17, 97, 14, 14 });
	rightp.speed = 0.10f;

	//Blue ------------------------
	// right animation
	rightb.PushBack({ 1, 112, 14, 14 });
	rightb.PushBack({ 17, 112, 14, 14 });
	rightb.speed = 0.10f;

	// left animation
	leftb.PushBack({ 113, 112, 14, 14 });
	leftb.PushBack({ 97, 112, 14, 14 });
	leftb.speed = 0.10f;

	// up animation
	upb.PushBack({ 65, 112, 14, 14 });
	upb.PushBack({ 81, 112, 14, 14 });
	upb.speed = 0.10f;

	// down animation
	downb.PushBack({ 33, 112, 14, 14 });
	downb.PushBack({ 49, 112, 14, 14 });
	downb.speed = 0.10f;
}

ModuleBackgroundIntermision1::~ModuleBackgroundIntermision1()
{}

// Load assets
bool ModuleBackgroundIntermision1::Start()
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

	player.x = 250;
	player.y = 150;

	player2.x = -30;
	player2.y = 100;

	claquet.x = 97;
	claquet.y = 110;

	pink.x = 280;
	pink.y = 150;

	blue.x = -60;
	blue.y = 100;

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
	now = SDL_GetTicks() - start_time;
	if (now > 18.5 * 0.5f * 1000.0f)
	{
		App->render->Blit(graphics, player.x, player.y, &right.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, pink.x, pink.y, &rightp.GetCurrentFrame(), 1.0f);
	

		App->render->Blit(graphics, player2.x, player2.y, &left2.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, blue.x, blue.y, &leftb.GetCurrentFrame(), 1.0f);
		if (now > 19 * 0.5f * 1000.0f)
		{
			App->render->Blit(misc, player.x+13, player.y-20, &hearth.GetCurrentFrame(), 1.0f);
		}
		if (now > 19.5 * 0.5f * 1000.0f)
		{
			right.speed = 0;
			left2.speed = 0;
		}
	}
	else if (now > 16.2 * 0.5f * 1000.0f)
	{
		App->render->Blit(graphics, player.x, player.y, &up.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, pink.x, pink.y, &rightp.GetCurrentFrame(), 1.0f);
		player.y -= 1.2f;

		App->render->Blit(graphics, player2.x, player2.y, &up2.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, blue.x, blue.y, &leftb.GetCurrentFrame(), 1.0f);
		player2.y -= 1.2f;


		if (now < 16.95 * 0.5f * 1000.0f)
		{
			blue.x -= 1.4f;
			pink.x += 1.4f;
		}
		else if (now < 17.2 * 0.5f * 1000.0f)
		{
			blue.x += 1.7f;
			pink.x -= 1.7f;
		}
	}
	else if (now > 13 * 0.5f * 1000.0f)
	{
		App->render->Blit(graphics, player.x, player.y, &right.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, pink.x, pink.y, &rightp.GetCurrentFrame(), 1.0f);
		player.x += 1.4f;
		pink.x += 1.4f;

		App->render->Blit(graphics, player2.x, player2.y, &left2.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, blue.x, blue.y, &leftb.GetCurrentFrame(), 1.0f);
		player2.x -= 1.4f;
		blue.x -= 1.4f;

	}
	else if (now > 12.2 * 0.5f * 1000.0f)
	{
		player.x = -30;
		player.y = 125;

		player2.x = 250;
		player2.y = 125;

		pink.x = -60;
		pink.y = 125;

		blue.x = 280;
		blue.y = 125;
	}
	else if (now > 3.5 * 0.5f * 1000.0f)
	{
		App->render->Blit(graphics, player.x, player.y, &left.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, pink.x, pink.y, &leftp.GetCurrentFrame(), 1.0f);
		player.x -= 1.4f;
		pink.x -= 1.4f;

		App->render->Blit(graphics, player2.x, player2.y, &right2.GetCurrentFrame(), 1.0f);
		App->render->Blit(graphics, blue.x, blue.y, &rightb.GetCurrentFrame(), 1.0f);
		player2.x += 1.4f;
		blue.x += 1.4f;
	}
	else if (now > 3.4 * 0.5f * 1000.0f)
	{
		claqueta.speed = 0.0f;
		App->render->Blit(misc, claquet.x, claquet.y, &claqueta.GetCurrentFrame(), 1.0f);
	}
	else if (now > 3 * 0.5f * 1000.0f)
	{
		claqueta.speed = 0.3f;
		App->render->Blit(misc, claquet.x, claquet.y, &claqueta.GetCurrentFrame(), 1.0f);
	}
	else if (now > 0.5 * 0.5f * 1000.0f)
	{
		claqueta.speed = 0;
		App->render->Blit(misc, claquet.x, claquet.y, &claqueta.GetCurrentFrame(), 1.0f);
	}


	return UPDATE_CONTINUE;
}
