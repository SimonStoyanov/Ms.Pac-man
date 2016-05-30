#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleMenu.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleGhostBlue.h"

ModuleEndScreen::ModuleEndScreen()
{
	// EndScreen
	map1 = { 0, 0, 224, 300};
}

ModuleEndScreen::~ModuleEndScreen()
{}

// Load assets
bool ModuleEndScreen::Start()
{
	LOG("Loading end screen.");
	bool ret = true;
	graphics = App->textures->Load("Sprites/end_screen.png");

	// Enable and disable modules
	App->player->Disable();
	App->player2->Disable();
	App->ghost_blue->Disable();

	pressed_space = false;

	return ret;
}

// Load assets
bool ModuleEndScreen::CleanUp()
{
	LOG("Unloading maps(1) stage.");
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEndScreen::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &map1, 1.0f); // end_screen
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && pressed_space == false)
	{
		pressed_space = true;
		App->fade->FadeToBlack(App->end_screen, App->menu, 2.0f);
	}

	char tmp_map[31][28]
	{	//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
		{ 1, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 2 }, //1
		{ 8, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 10 }, //2
		{ 8, 27, 11, 17, 17, 12, 28, 15, 16, 28, 11, 17, 17, 17, 17, 17, 17, 12, 28, 15, 16, 28, 11, 17, 17, 12, 27, 10 }, //3
		{ 8, 28, 13, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 18, 18, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 14, 28, 10 }, //4
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //5
		{ 3, 9, 12, 28, 11, 12, 28, 11, 17, 17, 17, 12, 28, 11, 12, 28, 11, 17, 17, 17, 12, 28, 11, 12, 28, 11, 9, 4 }, //6
		{ 0, 0, 8, 28, 15, 16, 28, 15, 30, 30, 30, 16, 28, 15, 16, 28, 15, 30, 30, 30, 16, 28, 15, 16, 28, 10, 0, 0 }, //7
		{ 7, 7, 14, 28, 15, 16, 28, 13, 18, 18, 18, 14, 28, 15, 16, 28, 13, 18, 18, 18, 14, 28, 15, 16, 28, 13, 7, 7 }, //8
		{ 0, 0, 0, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 28, 28, 28, 15, 16, 28, 0, 0, 0 }, //9
		{ 9, 9, 12, 28, 15, 23, 17, 17, 12, 0, 11, 17, 17, 24, 23, 17, 17, 12, 0, 11, 17, 17, 24, 16, 28, 11, 9, 9 }, //10
		{ 0, 0, 8, 28, 13, 18, 18, 18, 14, 0, 13, 18, 18, 18, 18, 18, 18, 14, 0, 13, 18, 18, 18, 14, 28, 10, 0, 0 }, //11
		{ 0, 0, 8, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 10, 0, 0 }, //12
		{ 0, 0, 8, 28, 11, 17, 17, 17, 12, 0, 19, 9, 9, 29, 29, 9, 9, 20, 0, 11, 17, 17, 17, 12, 28, 10, 0, 0 }, //13
		{ 0, 0, 8, 28, 15, 25, 18, 18, 14, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 13, 18, 18, 26, 16, 28, 10, 0, 0 }, //14
		{ 0, 0, 8, 28, 15, 16, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 15, 16, 28, 10, 0, 0 }, //15
		{ 0, 0, 8, 28, 15, 16, 0, 11, 12, 0, 10, 0, 0, 0, 0, 0, 0, 8, 0, 11, 12, 0, 15, 16, 28, 10, 0, 0 }, //16
		{ 7, 7, 14, 28, 13, 14, 0, 15, 16, 0, 21, 7, 7, 7, 7, 7, 7, 22, 0, 15, 16, 0, 13, 14, 28, 13, 7, 7 }, //17
		{ 0, 0, 0, 28, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 28, 0, 0, 0 }, //18
		{ 9, 9, 12, 28, 11, 17, 17, 24, 23, 17, 17, 12, 0, 11, 12, 0, 11, 17, 17, 24, 23, 17, 17, 12, 28, 11, 9, 9 }, //19
		{ 0, 0, 8, 28, 13, 18, 18, 18, 18, 18, 18, 14, 0, 15, 16, 0, 13, 18, 18, 18, 18, 18, 18, 14, 28, 10, 0, 0 }, //20
		{ 0, 0, 8, 28, 28, 28, 28, 28, 28, 28, 0, 0, 0, 15, 16, 0, 0, 0, 28, 28, 28, 28, 28, 28, 28, 10, 0, 0 }, //21
		{ 0, 0, 8, 28, 11, 17, 17, 17, 12, 28, 11, 17, 17, 24, 23, 17, 17, 12, 28, 11, 17, 17, 17, 12, 28, 10, 0, 0 }, //22
		{ 1, 7, 14, 28, 13, 18, 18, 18, 14, 28, 13, 18, 18, 18, 18, 18, 18, 14, 28, 13, 18, 18, 18, 14, 28, 13, 7, 2 }, //23
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 0, 0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //24
		{ 8, 28, 11, 17, 17, 12, 28, 11, 17, 17, 17, 12, 28, 11, 12, 28, 11, 17, 17, 17, 12, 28, 11, 17, 17, 12, 28, 10 }, //25
		{ 8, 28, 15, 30, 30, 16, 28, 15, 25, 18, 18, 14, 28, 15, 16, 28, 13, 18, 18, 26, 16, 28, 15, 30, 30, 16, 28, 10 }, //26
		{ 8, 28, 15, 30, 30, 16, 28, 15, 16, 28, 28, 28, 28, 15, 16, 28, 28, 28, 28, 15, 16, 28, 15, 30, 30, 16, 28, 10 }, //27
		{ 8, 27, 15, 30, 30, 16, 28, 15, 16, 28, 11, 17, 17, 24, 23, 17, 17, 12, 28, 15, 16, 28, 15, 30, 30, 16, 27, 10 }, //28
		{ 8, 28, 13, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 18, 18, 18, 18, 14, 28, 13, 14, 28, 13, 18, 18, 14, 28, 10 }, //29
		{ 8, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 10 }, //30
		{ 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, } //31

	};

	// Passing map to the header --------
	for (int i = 0; i < 31; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			App->map1->g_map[i][y] = tmp_map[i][y];
		}
	}

	return UPDATE_CONTINUE;
}