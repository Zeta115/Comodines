#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

#include <iostream>
using namespace std;


SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	cout << "ESTOY EN SCENE INTRO";

	bgTexture = App->textures->Load("Assets/Screens/title.png");
	logoTexture = App->textures->Load("Assets/Screens/logo.png");
	logo2Texture = App->textures->Load("Assets/Screens/logo_sega.png");
	logo3Texture = App->textures->Load("Assets/Screens/logo_hudson_soft.png");
	App->audio->PlayMusic("Assets/Audio/music/title_theme.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

UpdateResult SceneIntro::Update()
{

	if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN && sceneCount == 0)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->player->destroyed == true)sceneCount = 0;
	if (App->player->win == true) sceneCount = 0;
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneIntro::PostUpdate()
{
	/*sceneCount == 0;
	cout << sceneCount << endl;

	if (sceneCount == 0)
	{
		App->render->DrawTexture(logoTexture, 0, 0, NULL);
		App->player->destroyed = false;
		App->player->win = false;

		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
			cout << sceneCount << endl;
		}
	}

	if (sceneCount == 1)
	{
		App->render->DrawTexture(bgTexture, 0, 15, NULL); 
	}*/


	if (sceneCount == 0)
	{
		App->render->DrawTexture(bgTexture, 0, 15, NULL);
		App->player->destroyed = false;
		App->player->win = false;
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
			cout << sceneCount << endl;
		}
	}
	/*else if (sceneCount == 1)
	{
		App->render->DrawTexture(logo2Texture, 0, 0, NULL);
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
			cout << sceneCount << endl;
		}
	}
	else if (sceneCount == 2)
	{
		App->render->DrawTexture(logo3Texture, 0, 0, NULL);
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
			cout << sceneCount << endl;
		}
	}
	else if (sceneCount == 3)
	{
		App->render->DrawTexture(bgTexture, 0, 0, NULL);
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
			cout << sceneCount << endl;
		}
	}*/


	return UpdateResult::UPDATE_CONTINUE;
}