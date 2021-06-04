#include "SceneDeath.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"


SceneDeath::SceneDeath(bool startEnabled) : Module(startEnabled)
{

}

SceneDeath::~SceneDeath()
{

}

// Load assets
bool SceneDeath::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Screens/Lose.png");
	App->audio->PlayMusic("Assets/Audio/music/game_over.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

UpdateResult SceneDeath::Update()
{

	if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN && sceneCount == 0)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->player->destroyed == true)sceneCount = 0;
	if (App->player->win == true) sceneCount = 0;
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneDeath::PostUpdate()
{
	if (sceneCount == 0)
	{
		App->render->DrawTexture(bgTexture, 0, 0, NULL);
		App->player->destroyed = false;
		App->player->win = false;
	}

	return UpdateResult::UPDATE_CONTINUE;
}