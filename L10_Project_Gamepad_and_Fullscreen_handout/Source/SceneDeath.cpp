#include "SceneDeath.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

#include <stdio.h>


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

	gameOver = App->textures->Load("Assets/Hud/game_over.png");
	BackGround = { 256, 0, 256, 224 };
	GameOverImg = { 0, 0, 256, 224 };
	App->audio->PlayMusic("Assets/Audio/music/game_over.ogg", 1.0f);
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFontDeath = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 1);
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
	
}

UpdateResult SceneDeath::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_DOWN || pad.a == true && sceneCount == 0)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		App->player->lifes = 3;
	}

	if (App->player->destroyed == true)sceneCount = 0;
	if (App->player->win == true) sceneCount = 0;
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneDeath::PostUpdate()
{

	if (sceneCount == 0)
	{
		App->render->DrawTexture(gameOver, 0 , 0, &BackGround, NULL);
		App->render->DrawTexture(gameOver, 0, 0, &GameOverImg, NULL);
		App->player->destroyed = false;
		App->player->win = false;
	}
	sprintf_s(App->player->scoreText, 100, "%7d", App->player->score);
	App->fonts->DrawText(75, 155, scoreFontDeath, App->player->scoreText);
	return UpdateResult::UPDATE_CONTINUE;
}