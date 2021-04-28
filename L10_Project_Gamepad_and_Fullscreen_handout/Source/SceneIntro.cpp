#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"


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
	App->audio->PlayMusic("Assets/Audio/music/Title_Theme.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;




	return ret;
}

UpdateResult SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneIntro::PostUpdate()
{
	App->render->DrawTexture(bgTexture, 0, 15, NULL);
	return UpdateResult::UPDATE_CONTINUE;
}