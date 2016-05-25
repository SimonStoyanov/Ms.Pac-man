#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"

#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleMenu.h"
#include "ModuleBackground_Map1.h"
#include "ModuleBackground_Map2.h"
#include "ModuleEndScreen.h"

#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"
#include "ModuleCherry.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = menu = new ModuleMenu();
	modules[i++] = map1 = new ModuleBackgroundMap1();
	modules[i++] = map2 = new ModuleBackgroundMap2();
	modules[i++] = end_screen = new ModuleEndScreen();
	modules[i++] = UI = new ModuleUI();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = ghost_blue = new ModuleGhostBlue();
	modules[i++] = ghost_orange = new ModuleGhostOrange();
	modules[i++] = ghost_pink = new ModuleGhostPink();
	modules[i++] = ghost_red = new ModuleGhostRed();
	modules[i++] = cherry = new ModuleCherry();

	modules[i++] = collision = new ModuleCollision(); //it has to be the second last one
	modules[i++] = fade = new ModuleFadeToBlack(); //it has to be always the last one 
}


Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Enable
	App->menu->Enable();

	// Disable
	audio->Disable();
	cherry->Disable();
	map1->Disable();
	map2->Disable();
	end_screen->Disable();
	collision->Disable();
	ghost_blue->Disable();
	player->Disable();
	player2->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}