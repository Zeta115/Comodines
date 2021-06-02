#include "SceneLevelBoss.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevelBoss::SceneLevelBoss(bool startEnabled) : Module(startEnabled)
{

}

SceneLevelBoss::~SceneLevelBoss()
{

}

// Load assets
bool SceneLevelBoss::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Map/Final_Boss_1_Map.png");
	App->audio->PlayMusic("Assets/Audio/music/area_1.ogg", 1.0f);
	loseScreen = App->textures->Load("Assets/Screens/lose.PNG");
	winScreen = App->textures->Load("Assets/Screens/win.PNG");
	hud = App->textures->Load("Assets/Hud/hud.png");
	machineTexture = App->textures->Load("Assets/Map/reactor_1.png");

	// Colliders

//Limits
	//down
	App->collisions->AddCollider({ 0, 208, 400, 17 }, Collider::Type::WALL);

	//Top
	App->collisions->AddCollider({ 0, 0, 400, 31 }, Collider::Type::WALL);

	//Left
	App->collisions->AddCollider({ 0, 0, 25, 400 }, Collider::Type::WALL);
	//Right
	App->collisions->AddCollider({ 232, 0, 25, 400 }, Collider::Type::WALL);

	// Stones
	/// 1r: donde empieza la piedra a partir de la x - 2n: donde empieza la piedra a partir de la y - 3r: ample de la pedra - 4rt: alçada de la pedra

	//First two columns colliders
	//Fila 1
	App->collisions->AddCollider({ 104, 48, 15, 15 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 48, 15, 15 }, Collider::Type::WALL);//4
	//Fila 2
	App->collisions->AddCollider({ 40, 80, 15, 15 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 73, 80, 15, 15 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 80, 15, 35 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 80, 15, 15 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 80, 15, 15 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 80, 15, 15 }, Collider::Type::WALL);//6

	//Fila 3
	App->collisions->AddCollider({ 40, 112, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 112, 47, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 112, 45, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 112, 15, 45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 112, 15, 15 }, Collider::Type::WALL);


	//Fila 4
	App->collisions->AddCollider({ 40, 145, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 145,  15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 145, 15, 15 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 168, 145, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 145,  15, 15 }, Collider::Type::WALL);

	//Fila 5
	App->collisions->AddCollider({ 104, 176, 15, 15 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 176, 15, 15 }, Collider::Type::WALL);//4


	// Enemies ---


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	return ret;
}

UpdateResult SceneLevelBoss::Update()
{
	/*if (App->input->keys[SDL_SCANCODE_0] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneBoss, 90);
	}*/

	if (App->input->keys[SDL_SCANCODE_9] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevelBoss::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);
	App->render->DrawTexture(hud, 0, -32, NULL);
	//App->render->DrawTexture(machineTexture, 104, 96, NULL);

	if (App->player->destroyed == true)
	{

		App->render->DrawTexture(loseScreen, -20, 15, NULL);
	}

	if (App->player->win == true)
	{
		App->render->DrawTexture(winScreen, -10, 15, NULL);
	}
	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevelBoss::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)
	App->collisions->Disable();
	return true;
}