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

	// right animation
	right.PushBack({ 33, 1, 15, 14 });
	right.PushBack({ 17, 1, 13, 14 });
	right.PushBack({ 1, 1, 11, 14 });
	right.speed = 0.25f;

	// left animation
	left.PushBack({ 33, 36, 15, 14 });
	left.PushBack({ 17, 36, 13, 14 });
	left.PushBack({ 1, 36, 11, 14 });
	left.speed = 0.25f;

	// up animation
	up.PushBack({ 33, 51, 14, 15 });
	up.PushBack({ 17, 51, 14, 13 });
	up.PushBack({ 1, 51, 14, 11 });
	up.speed = 0.25f;

	// down animation
	down.PushBack({ 33, 18, 14, 15 });
	down.PushBack({ 17, 18, 14, 13 });
	down.PushBack({ 1, 19, 14, 11 });
	down.speed = 0.25f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Pac-man & Ghosts.png");
	prev_anim = &right;
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = prev_anim;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &right;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &left;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &up;
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &down;
		position.y += speed;
	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}