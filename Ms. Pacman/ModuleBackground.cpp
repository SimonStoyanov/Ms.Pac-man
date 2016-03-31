#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Xip
	ship.x = 0;
	ship.y = 9;
	ship.w = 550;
	ship.h = 200;

	// Woman Animation
	woman.PushBack({ 625, 17, 32, 56 });
	woman.PushBack({ 625, 81, 32, 56 });
	woman.PushBack({ 625, 145, 32, 56 });
	woman.speed = 0.08f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	static int loop = 0;
	loop++;
	if (loop % 25 == 0){
		if (loop % 6 == 0 || loop % 6 == 1 || loop % 6 == 2){
			move_ship += 1;
		}
		else{
			move_ship -= 1;
		}
	}
	App->render->Blit(graphics, -100, move_ship, &ship, 0.8f);
	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	App->render->Blit(graphics, 100, move_ship + 120, &(woman.GetCurrentFrame()), 0.8f);


	App->render->Blit(graphics, 0, 170, &ground);

	return UPDATE_CONTINUE;
}