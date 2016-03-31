#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	/* ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	 Woman Animation
	woman.PushBack({ 625, 17, 32, 56 });
	woman.PushBack({ 625, 81, 32, 56 });
	woman.PushBack({ 625, 145, 32, 56 });
	woman.speed = 0.08f;*/

	// Map 1
	map1.x = 0;
	map1.y = 0;
	map1.w = 300;
	map1.h = 300;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("maps.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------

	//App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	App->render->Blit(graphics, 30, 30, &map1, 1.0f); // map 1
	return UPDATE_CONTINUE;
}