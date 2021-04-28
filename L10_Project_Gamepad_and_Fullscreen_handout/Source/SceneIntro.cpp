#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
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
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	// Colliders

	//Limits
	//Bottom
	App->collisions->AddCollider({ 0, 242, 600, 16 }, Collider::Type::WALL);
	//Top
	App->collisions->AddCollider({ 0, 33, 600, 30 }, Collider::Type::WALL);
	//Left
	App->collisions->AddCollider({ 0, 33, 24, 600 }, Collider::Type::WALL);
	//Right
	App->collisions->AddCollider({ 232, 33, 25, 600 }, Collider::Type::WALL);

	// Stones
	/// 1r: donde empieza la piedra a partir de la x - 2n: donde empieza la piedra a partir de la y - 3r: ample de la pedra - 4rt: alçada de la pedra

	//First two columns colliders
	//Fila 1
	App->collisions->AddCollider({ 40, 80, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 80, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 80, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 80, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 80, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 80, 16, 10 }, Collider::Type::WALL);

	//Fila 2
	App->collisions->AddCollider({ 40, 112, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 112, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 112, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 112, 16, 10 }, Collider::Type::WALL);

	//Fila 3
	App->collisions->AddCollider({ 40, 144, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 144, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 144, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 144, 16, 10 }, Collider::Type::WALL);

	//Fila 4
	App->collisions->AddCollider({ 40, 176, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 176, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 176, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 176, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 176, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 176, 16, 10 }, Collider::Type::WALL);

	//Fila 5
	App->collisions->AddCollider({ 40, 208, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 208, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 208, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 208, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 208, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 208, 16, 10 }, Collider::Type::WALL);

	// Enemies
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 70, 180);
	App->enemies->AddEnemy(Enemy_Type::CARGOL, 85, 114);


	return ret;
}

UpdateResult SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneIntro::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);
	App->render->DrawTexture(hud, 0, -20, NULL);
	if (App->player->destroyed == true || App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_REPEAT)
	{
		App->render->DrawTexture(loseScreen, 0, -20, NULL);
	}
	if (App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_REPEAT)
	{
		App->render->DrawTexture(winScreen, 0, -20, NULL);
	}
	return UpdateResult::UPDATE_CONTINUE;
	return UpdateResult::UPDATE_CONTINUE;
}