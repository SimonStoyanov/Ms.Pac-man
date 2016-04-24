#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleBackground_Map1.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer() 
{
	position.x = 106; //106
	position.y = 195 + DISTANCE; //195

	test = { 3, 120, 1, 1 };

	// right animation
	right.PushBack({ 33, 1, 15, 14 });
	right.PushBack({ 17, 1, 13, 14 });
	right.PushBack({ 1, 1, 11, 14 });
	right.speed = 0.25f;

	// left animation
	left.PushBack({ 33, 34, 15, 15 });
	left.PushBack({ 15, 34, 15, 15 });
	left.PushBack({ 0, 34, 17, 15 });
	left.speed = 0.25f;

	// up animation
	up.PushBack({ 33, 51, 14, 15 });
	up.PushBack({ 17, 51, 14, 13 });
	up.PushBack({ 1, 51, 14, 11 });
	up.speed = 0.25f;

	// down animation
	down.PushBack({ 33, 17, 14, 15 });
	down.PushBack({ 17, 17, 14, 15 });
	down.PushBack({ 1, 17, 14, 15 });
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
	prev_anim = &left;
	

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = prev_anim;

	// Movement---------------------------------------
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[p_right.y][p_right.x + 1] == 0 || App->map1->map1[p_right.y][p_right.x + 1] == 28 || App->map1->map1[p_right.y][p_right.x + 1] == 27)
		{
			if ((position.x + 7) == (p_mid.x * 8) + 3 && (position.y - 7) == (p_mid.y * 8) + 4 || go_left == true)
			{
				go_right = true; go_left = false; go_up = false; go_down = false;
			}
		}

	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[p_left.y][p_left.x - 1] == 0 || App->map1->map1[p_left.y][p_left.x - 1] == 28 || App->map1->map1[p_left.y][p_left.x - 1] == 27)
		{
			if ((position.x + 7) == (p_mid.x * 8) + 3 && (position.y - 7) == (p_mid.y * 8) + 4 || go_right == true)
			{
				go_left = true; go_right = false; go_up = false; go_down = false;
			}
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[p_up.y - 1][p_up.x] == 0 || App->map1->map1[p_up.y - 1][p_up.x] == 28 || App->map1->map1[p_up.y - 1][p_up.x] == 27)
		{
			if ((position.x + 7) == (p_mid.x * 8) + 3 && (position.y - 7) == (p_mid.y * 8) + 4 || go_down == true)
			{
				go_up = true; go_right = false; go_left = false; go_up = true; go_down = false;
			}
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[p_down.y + 1][p_down.x] == 0 || App->map1->map1[p_down.y + 1][p_down.x] == 28 || App->map1->map1[p_down.y + 1][p_down.x] == 27)
		{
			if ((position.x + 7) == (p_mid.x * 8) + 3 && (position.y - 7) == (p_mid.y * 8) + 4 || go_up == true)
			{
				go_down = true; go_right = false; go_left = false; go_up = false;
			}
		}
	}

	if (go_right)
	{
		if (App->map1->map1[p_right.y][p_right.x + 1] == 0 || App->map1->map1[p_right.y][p_right.x + 1] == 28 || App->map1->map1[p_right.y][p_right.x + 1] == 27)
		{
			right.speed = 0.25f;
			current_animation = &right;
			position.x += speed;
			wakawaka = true;
			go_left = false; go_up = false; go_down = false;
		}
		else
			right.speed = 0.00000001f;
	}
	if (go_left)
	{
		if (App->map1->map1[p_left.y][p_left.x - 1] == 0 || App->map1->map1[p_left.y][p_left.x - 1] == 28 || App->map1->map1[p_left.y][p_left.x - 1] == 27)
		{
			left.speed = 0.25f;
			current_animation = &left;
			position.x -= speed;
			wakawaka = true;
			go_right = false; go_up = false; go_down = false;
		}
		else
			left.speed = 0.00000001f;
	}
	if (go_up)
	{
		if (App->map1->map1[p_up.y - 1][p_up.x] == 0 || App->map1->map1[p_up.y - 1][p_up.x] == 28 || App->map1->map1[p_up.y - 1][p_up.x] == 27)
		{
			up.speed = 0.25f;
			current_animation = &up;
			position.y -= speed;
			wakawaka = true;
			go_right = false; go_left = false; go_up = true; go_down = false;
		}
		else
			up.speed = 0.00000001f;
	}
	if (go_down)
	{
		if (App->map1->map1[p_down.y + 1][p_down.x] == 0 || App->map1->map1[p_down.y + 1][p_down.x] == 28 || App->map1->map1[p_down.y + 1][p_down.x] == 27)
		{
				down.speed = 0.25f;
				current_animation = &down;
				position.y += speed;
				wakawaka = true;
				go_right = false; go_left = false; go_up = false;
		}
		else
			down.speed = 0.00000001f;
	}

	p_up.x = (position.x + 7) / 8;
	p_up.y = (position.y - 4) / 8;

	p_down.x = (position.x + 7) / 8;
	p_down.y = (position.y - 11) / 8;

	p_left.x = (position.x + 11) / 8;
	p_left.y = (position.y - 7) / 8;

	p_right.x = (position.x + 4) / 8;
	p_right.y = (position.y - 7) / 8;

	p_mid.x = (position.x + 6) / 8;
	p_mid.y = (position.y - 7) / 8;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	App->render->Blit(graphics, (position.x +7), (position.y - 7), &test, 1.0f); //
	App->render->Blit(graphics, (p_mid.x * 8) + 3, (p_mid.y * 8) + 4, &test, 1.0f); //

	return UPDATE_CONTINUE;
}


