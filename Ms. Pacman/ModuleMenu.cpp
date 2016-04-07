#include "SDL/include/SDL_timer.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModuleMenu.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

ModuleMenu::ModuleMenu()
{
	// Background
	background = { 0, 0, 224, 288 };

	// Rectangle Animation
	Rectangle.PushBack({ 225, 1, 134, 63 });
	Rectangle.PushBack({ 225, 67, 134, 63 });
	Rectangle.PushBack({ 225, 133, 134, 63 });
	Rectangle.PushBack({ 225, 199, 134, 63 });
	Rectangle.PushBack({ 225, 265, 134, 63 });
	Rectangle.PushBack({ 225, 331, 134, 63 });
	Rectangle.speed = 0.2f;

	// Red Ghost animation
	red.x = 250;
	red.y = 158;

	Red_left.PushBack({ 1, 307, 14, 14 });
	Red_left.PushBack({ 17, 307, 14, 14 });
	Red_left.speed = 0.2f;

	Red_up.PushBack({ 33, 307, 14, 14 });
	Red_up.PushBack({ 49, 307, 14, 14 });
	Red_up.speed = 0.2f;

	// Time
	start_time = SDL_GetTicks();
	total_time_red = (Uint32)(time * 0.5f * 1000.0f);

}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading Menu.");
	bool ret = true;
	graphics = App->textures->Load("Menu.png");

	// Enable and disable modules
	App->player->Disable();
	App->audio->Enable();
	App->ghost_blue->Disable();

	return ret;
}

// Load assets
bool ModuleMenu::CleanUp()
{
	LOG("Unloading  Menu.");
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &background, 1.0f);
	App->render->Blit(graphics, 60, 88, &Rectangle.GetCurrentFrame(), 1.0f);

	// Ghosts animations --------------------------------------
	float speed_left = 0.1f;
	float speed_up = 0.1f;

	Uint32 now = SDL_GetTicks() - start_time; //time since start
	
	// Red ghost
	if (now >= total_time_red)
	{
		if (red.x>=40) // left
		{
			red.x -= speed_left;
			App->render->Blit(graphics, red.x, red.y, &Red_left.GetCurrentFrame(), 1.0f);
		}
		else if (red.y > 89) //up
		{
			red.y -= speed_up;
			App->render->Blit(graphics, red.x, red.y, &Red_up.GetCurrentFrame(), 1.0f);
		}
		else // stoped
		{ 
			App->render->Blit(graphics, red.x, red.y, &Red_up.GetCurrentFrame(), 1.0f); 
		} 

	}

	// Red ghost

	//Fade To Black
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->menu, App->map1, 2.0f);
	}

	return UPDATE_CONTINUE;
}
