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
	position.x = 107;
	position.y = 196 + DISTANCE;

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
		if (App->map1->map1[App->player->player_tile.y][App->player->player_tile.x + 1] == 0 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x + 1] == 28 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x + 1] == 27)
		{
			go_right = true; go_left = false; go_up = false; go_down = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[App->player->player_tile.y][App->player->player_tile.x - 1] == 0 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x - 1] == 28 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x - 1] == 27)
		{
			go_left = true; go_right = false; go_up = false; go_down = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[App->player->player_tile.y - 1][App->player->player_tile.x] == 0 || App->map1->map1[App->player->player_tile.y - 1][App->player->player_tile.x] == 28 || App->map1->map1[App->player->player_tile.y - 1][App->player->player_tile.x] == 27)
		{
			go_up = true; go_right = false; go_left = false; go_up = true; go_down = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map1->map1[App->player->player_tile.y + 1][App->player->player_tile.x] == 0 || App->map1->map1[App->player->player_tile.y + 1][App->player->player_tile.x] == 28 || App->map1->map1[App->player->player_tile.y + 1][App->player->player_tile.x] == 27)
		{
			go_down = true; go_right = false; go_left = false; go_up = false;
		}
	}

	if (go_right)
	{
		if (App->map1->map1[App->player->player_tile.y][App->player->player_tile.x + 1] == 0 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x + 1] == 28 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x + 1] == 27)
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
		if (App->map1->map1[App->player->player_tile.y][App->player->player_tile.x - 1] == 0 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x - 1] == 28 || App->map1->map1[App->player->player_tile.y][App->player->player_tile.x - 1] == 27)
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
		if (App->map1->map1[App->player->player_tile.y - 1][App->player->player_tile.x] == 0 || App->map1->map1[App->player->player_tile.y - 1][App->player->player_tile.x] == 28 || App->map1->map1[App->player->player_tile.y - 1][App->player->player_tile.x] == 27)
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
		if (App->map1->map1[App->player->player_tile.y + 1][App->player->player_tile.x] == 0 || App->map1->map1[App->player->player_tile.y + 1][App->player->player_tile.x] == 28 || App->map1->map1[App->player->player_tile.y + 1][App->player->player_tile.x] == 27)
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

	int x = position.x; x += 10;
	int y = position.y; y -= 5;

	player_tile.x = (x / 8);
	player_tile.y = (y / 8);

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	prev_anim = current_animation;
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}


