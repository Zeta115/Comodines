#include "SceneTransition2.h"
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

SceneTransition2::SceneTransition2(bool startEnabled) : Module(startEnabled)
{

}

SceneTransition2::~SceneTransition2()
{

}

// Load assets
bool SceneTransition2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Map/Inter2.png");
	App->audio->PlayMusic("Assets/Audio/music/title_theme.ogg", 1.0f);

	

	return ret;
}

UpdateResult SceneTransition2::Update()
{


	if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneTransition2::PostUpdate()
{
	// Draw everything	

		App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneTransition2::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)
	App->collisions->Disable();
	return true;
}