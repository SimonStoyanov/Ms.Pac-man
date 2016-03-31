#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 109;
	position.y = 209;

	// idle animation
	idle.PushBack({1, 1, 11, 14});
	idle.PushBack({18, 1, 13, 14});
	idle.PushBack({34, 1, 15, 14});
	idle.speed = 0.25f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Pac-man & Ghosts.png");
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		position.y += speed;
	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}