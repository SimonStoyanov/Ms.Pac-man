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
#include "ModuleMenu.h"

#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"

ModuleMenu::ModuleMenu()
{
	// Background
	background = { 0, 0, 224, 288 };
	With = { 111, 307, 32, 8 };
	Blinky = { 64, 307, 46, 8 };
	Sue = { 64, 322, 23, 9 };
	Pinky = { 64, 337, 38, 8 };
	Inky = { 64, 351, 30, 8 };
	Starring = { 111 , 316, 62, 8 };
	MsPacMan = { 64, 367, 77, 8 };
	voidspace = { 86, 457, 77, 9 };

	// Rectangle Animation
	Rectangle.PushBack({ 225, 1, 134, 63 });
	Rectangle.PushBack({ 225, 67, 134, 63 });
	Rectangle.PushBack({ 225, 133, 134, 63 });
	Rectangle.PushBack({ 225, 199, 134, 63 });
	Rectangle.PushBack({ 225, 265, 134, 63 });
	Rectangle.PushBack({ 225, 331, 134, 63 });
	Rectangle.speed = 0.2f;

	// Red Ghost animation

	Red_left.PushBack({ 1, 307, 14, 14 });
	Red_left.PushBack({ 17, 307, 14, 14 });
	Red_left.speed = 0.2f;

	Red_up.PushBack({ 33, 307, 14, 14 });
	Red_up.PushBack({ 49, 307, 14, 14 });
	Red_up.speed = 0.2f;

	// Pink Ghost animation
	Pink_left.PushBack({ 1, 337, 14, 14 });
	Pink_left.PushBack({ 17, 337, 14, 14 });
	Pink_left.speed = 0.2f;

	Pink_up.PushBack({ 33, 337, 14, 14 });
	Pink_up.PushBack({ 49, 337, 14, 14 });
	Pink_up.speed = 0.2f;

	//Blue Ghost animation
	Blue_left.PushBack({ 1, 352, 14, 14 });
	Blue_left.PushBack({ 17, 352, 14, 14 });
	Blue_left.speed = 0.2f;

	Blue_up.PushBack({ 33, 352, 14, 14 });
	Blue_up.PushBack({ 49, 352, 14, 14 });
	Blue_up.speed = 0.2f;

	//Orange Ghost animation
	Orange_left.PushBack({ 1, 322, 14, 14 });
	Orange_left.PushBack({ 17, 322, 14, 14 });
	Orange_left.speed = 0.2f;

	Orange_up.PushBack({ 33, 322, 14, 14 });
	Orange_up.PushBack({ 49, 322, 14, 14 });
	Orange_up.speed = 0.2f;

	//Pacman animation
	Pacman_left.PushBack({ 38, 368, 15, 15 });
	Pacman_left.PushBack({ 20, 368, 15, 15 });
	Pacman_left.PushBack({ 5, 368, 15, 15 });
	Pacman_left.speed = 0.2f;

	//from seconds to miliseconds
	total_time_red = (Uint32)(time_red * 0.5f * 1000.0f);
	total_time_blue = (Uint32)(time_blue * 0.5f * 1000.0f);
	total_time_orange = (Uint32)(time_orange * 0.5f * 1000.0f);
	total_time_pink = (Uint32)(time_pink * 0.5f * 1000.0f);
	total_time_pacman = (Uint32)(time_pacman * 0.5f * 1000.0f);
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
	App->audio->Disable();
	App->ghost_blue->Disable();
	App->ghost_orange->Disable();
	App->ghost_pink->Disable();
	App->ghost_red->Disable();
	App->map1->Disable();
	App->UI->Enable();

	// Ghosts start position
	red.x = pink.x = blue.x = orange.x = pacman.x = 250;
	red.y = pink.y = blue.y = orange.y = pacman.y = 158;

	// Seting time of the start
	start_time = SDL_GetTicks();

	App->UI->score = 0;
	App->UI->_score = 0;

	credits_used = 0;

	return ret;
}

// Load assets
bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu.");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 1.0f);
	App->render->Blit(graphics, 60, 88, &Rectangle.GetCurrentFrame(), 1.0f);

	// Ghosts animations --------------------------------------
	float speed_left = 1.0f;
	float speed_up = 0.8f;

	Uint32 now = SDL_GetTicks() - start_time; //time since start
	
	App->player->lifes = 5;
	App->player->end_game = false;

	// Red ghost
	if (now >= total_time_red)
	{
		if (red.x>=40) // left
		{
			App->render->Blit(graphics, 82, 102, &With, 1.0f);
			App->render->Blit(graphics, 106, 131, &Blinky, 1.0f);
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

	// Pink ghost
	if (now >= total_time_pink)
	{
		if (pink.x >= 40) // left
		{
			App->render->Blit(graphics, 82, 102, &voidspace, 1.0f);
			App->render->Blit(graphics, 106, 131, &voidspace, 1.0f);
			App->render->Blit(graphics, 106, 131, &Pinky, 1.0f);
			pink.x -= speed_left;
			App->render->Blit(graphics, pink.x, pink.y, &Pink_left.GetCurrentFrame(), 1.0f);
		}
		else if (pink.y > 105) //up
		{
			pink.y -= speed_up;
			App->render->Blit(graphics, pink.x, pink.y, &Pink_up.GetCurrentFrame(), 1.0f);
		}
		else // stoped
		{
			App->render->Blit(graphics, pink.x, pink.y, &Pink_up.GetCurrentFrame(), 1.0f);
		}

	}

	// Blue ghost
	if (now >= total_time_blue)
	{
		if (blue.x >= 40) // left
		{
			App->render->Blit(graphics, 106, 131, &voidspace, 1.0f);
			App->render->Blit(graphics, 114, 131, &Inky, 1.0f);
			blue.x -= speed_left;
			App->render->Blit(graphics, blue.x, blue.y, &Blue_left.GetCurrentFrame(), 1.0f);
		}
		else if (blue.y > 121) //up
		{
			blue.y -= speed_up;
			App->render->Blit(graphics, blue.x, blue.y, &Blue_up.GetCurrentFrame(), 1.0f);
		}
		else // stoped
		{
			App->render->Blit(graphics, blue.x, blue.y, &Blue_up.GetCurrentFrame(), 1.0f);
		}
	}

	// Orange ghost
	if (now >= total_time_orange)
	{
		if (orange.x >= 40) // left
		{
			App->render->Blit(graphics, 114, 131, &voidspace, 1.0f);
			App->render->Blit(graphics, 118, 131, &Sue, 1.0f);
			orange.x -= speed_left;
			App->render->Blit(graphics, orange.x, orange.y, &Orange_left.GetCurrentFrame(), 1.0f);
		}
		else if (orange.y > 137) //up
		{
			orange.y -= speed_up;
			App->render->Blit(graphics, orange.x, orange.y, &Orange_up.GetCurrentFrame(), 1.0f);
		}
		else // stoped
		{
			App->render->Blit(graphics, orange.x, orange.y, &Orange_up.GetCurrentFrame(), 1.0f);
		}
	}

	if (now >= total_time_pacman)
	{
		App->render->Blit(graphics, 82, 131, &voidspace, 1.0f);
		App->render->Blit(graphics, 82, 102, &Starring, 1.0f);
		App->render->Blit(graphics, 82, 131, &MsPacMan, 1.0f);
		if (pacman.x >= 116) // left
		{
			pacman.x -= speed_left;
			App->render->Blit(graphics, pacman.x, pacman.y, &Pacman_left.GetCurrentFrame(), 1.0f);
		}
		else // stoped
		{
			App->render->Blit(graphics, pacman.x, pacman.y, &Pacman_left.GetCurrentFrame(), 1.0f);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
	{
		if (App->UI->credit < 99)
		App->UI->credit++;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_TAB] == KEY_STATE::KEY_DOWN)
	{
		if (App->player->two_players == true)
			App->player->two_players = false;
		else{
			App->player->two_players = true;
		}
	}

	//Fade To Black
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->UI->credit > 0 && credits_used == 0)
	{
		credits_used++;
		if (App->player->two_players == false){
			App->UI->credit--;
			App->fade->FadeToBlack(App->menu, App->map2, 1.0f);
		}
		else if (App->player->two_players == true && App->UI->credit >= 2){
			App->UI->credit -= 2;
			App->fade->FadeToBlack(App->menu, App->map1, 1.0f);
		}
	}

	App->player->round = 0; //sets the round again to 0

	return UPDATE_CONTINUE;
}
