#include <iostream>
#include <random>
using namespace std;

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleCherry.h"
#include "ModuleBackground_Map1.h"
#include "ModuleAudio.h"
#include <time.h>
#include <stdlib.h>

ModuleCherry::ModuleCherry()
{
	// Cherry Animation
	cherry = { 1, 2, 12, 12 };
}

ModuleCherry::~ModuleCherry()
{
	
}

bool ModuleCherry::CleanUp()
{
	LOG("Blue ghost CleanUp");
	App->textures->Unload(graphics);
	
	return true;
}

// Load assets
bool ModuleCherry::Start()
{
	LOG("Loading fruitt textures");
	bool ret = true;
	graphics = App->textures->Load("Fruits.png");

	position.x = 0;
	position.y = 85;

	fruit_collision = App->collision->AddCollider({ position.x, position.y, 10, 10 }, COLLIDER_FRUIT, this);

	count = 0;
	return ret;

}

// Update: draw background
update_status ModuleCherry::Update()
{
	count++;
	App->render->Blit(graphics, position.x, position.y, &cherry);
	fruit_collision->SetPos(position.x + 1, position.y + 1);
	// Animation--------------------------------------------------------------
	if (count == 10){
		if (!Mix_Paused(4)){
			Mix_PlayChannel(4, App->audio->fruitmovement, 0);
		}
		position.y += 2;
	}
	else if (count == 20){
		position.y -= 2;
		count = 0;
	}
	//------------------------------------------------------------------------
	return UPDATE_CONTINUE;
}
