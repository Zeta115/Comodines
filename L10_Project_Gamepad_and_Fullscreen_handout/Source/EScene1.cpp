#include "EScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "SceneLevel2.h"

EScene1::EScene1(bool startEnabled) : Module(startEnabled)
{

}

EScene1::~EScene1()
{

}

// Load assets
bool EScene1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Map/Inter1.png");
	return ret;
}

UpdateResult EScene1::Update()
{

	if (App->input->keys[SDL_SCANCODE_0] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
	}
	if (App->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_DOWN)
	{
		machine1--;
		machine2--;
	}
	if (App->input->keys[SDL_SCANCODE_9] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult EScene1::PostUpdate()
{
	// Draw everything	

	return UpdateResult::UPDATE_CONTINUE;
}

bool EScene1::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)
	App->collisions->Disable();
	return true;
}