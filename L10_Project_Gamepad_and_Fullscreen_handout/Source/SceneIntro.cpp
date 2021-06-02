#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"


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

	bgTexture = App->textures->Load("Assets/Screens/title.png");
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
	if (sceneCount == 0)
	{
		App->render->DrawTexture(bgTexture, 0, 0, NULL);
		App->player->destroyed = false;
		App->player->win = false;
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN) {
			sceneCount++;
		}
	}

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


	return UpdateResult::UPDATE_CONTINUE;
}