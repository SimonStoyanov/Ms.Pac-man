#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleGhostBlue::ModuleGhostBlue()
{
	position.x = 92;
	position.y = 135;

	// right animation
	right.PushBack({ 1, 112, 14, 14 });
	right.PushBack({ 17, 112, 14, 14 });
	right.speed = 0.10f;

	// left animation
	left.PushBack({ 1, 112, 14, 14 });
	left.PushBack({ 17, 112, 14, 14 });
	left.speed = 0.10f;

	// up animation
	up.PushBack({ 65, 112, 14, 14 });
	up.PushBack({ 81, 112, 14, 14 });
	up.speed = 0.10f;

	// down animation
	down.PushBack({ 33, 112, 14, 14 });
	down.PushBack({ 49, 112, 14, 14 });
	down.speed = 0.10f;

	//vulnerable animation
	vulnerable.PushBack({ 1, 127, 14, 14 });
	vulnerable.PushBack({ 17, 127, 14, 14 });
	vulnerable.speed = 0.10f;

}

ModuleGhostBlue::~ModuleGhostBlue()
{}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading blue ghost textures");
	bool ret = true;
	graphics = App->textures->Load("Pac-man & Ghosts.png");
	prev_anim = &up;
	return ret;
}

// Update: draw background
update_status ModuleGhostBlue::Update()
{
	Animation* current_animation = prev_anim;
	
	// Draw everything --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &vulnerable;
	}
	else
	{
		current_animation = &up;
	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}