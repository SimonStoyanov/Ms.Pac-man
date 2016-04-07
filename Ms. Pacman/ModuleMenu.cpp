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
	Rectangle.PushBack({ 0, 0, 0, 0 });
	Rectangle.PushBack({ 0, 0, 0, 0 });
	Rectangle.PushBack({ 0, 0, 0, 0 });
	Rectangle.PushBack({ 0, 0, 0, 0 });
	Rectangle.PushBack({ 0, 0, 0, 0 });
	Rectangle.speed = 0.2f;

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
	/*App->render->Blit(graphics, 2, 15, &(Rectangle.GetCurrentFrame()), 1.0f);*/ // Rectangle

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 1.0f);

	//Fade To Black
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->menu, App->map1, 2.0f);
	}

	return UPDATE_CONTINUE;
}