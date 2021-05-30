#include "SceneLogo.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"


SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{

}

SceneLogo::~SceneLogo()
{

}

// Load assets
bool SceneLogo::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	logoTexture = App->textures->Load("Assets/Screens/logo.png");
	logo2Texture = App->textures->Load("Assets/Screens/logo_sega.png");
	logo3Texture = App->textures->Load("Assets/Screens/logo_hudson_soft.png");
	//App->audio->PlayMusic("Assets/Audio/music/title_theme.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

UpdateResult SceneLogo::Update()
{

	if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN && sceneCount == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	if (App->player->destroyed == true)sceneCount = 0;
	if (App->player->win == true) sceneCount = 0;
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLogo::PostUpdate()
{


	if (sceneCount == 0)
	{
		App->render->DrawTexture(logoTexture, 0, 0, NULL);
		App->player->destroyed = false;
		App->player->win = false;
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
		}
	}
	else if (sceneCount == 1)
	{
		App->render->DrawTexture(logo2Texture, 0, 0, NULL);
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
		}
	}
	else if (sceneCount == 2)
	{
		App->render->DrawTexture(logo3Texture, 0, 0, NULL);
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
		}
	}


	return UpdateResult::UPDATE_CONTINUE;
}