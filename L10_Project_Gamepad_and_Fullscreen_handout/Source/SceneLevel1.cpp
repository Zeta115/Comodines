#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Map/mapa.png");
	App->audio->PlayMusic("Assets/Audio/music/Area_1.ogg", 1.0f);
	loseScreen = App->textures->Load("Assets/Screens/lose.PNG");
	winScreen = App->textures->Load("Assets/Screens/win.PNG");
	hud = App->textures->Load("Assets/Hud/hud.png");
	machineTexture = App->textures->Load("Assets/Map/Reactor_1.png");
	PowerUp = App->textures->Load("Assets/SpecialElements/Powerups.png");

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
	App->collisions->AddCollider({ 42, 83, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 83, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 106, 83, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 138, 83, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 83, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 202, 83, 13, 10 }, Collider::Type::WALL);

	//Fila 2
	App->collisions->AddCollider({ 42, 115, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 115, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 115, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 202, 115, 13, 10 }, Collider::Type::WALL);

	//machine
	App->collisions->AddCollider({ 105, 117, 46, 22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 105, 139, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 139, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, 139, 14, 14 }, Collider::Type::MACHINE);

	//Fila 3
	App->collisions->AddCollider({ 42, 147, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 147, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 147, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 202, 147, 13, 10 }, Collider::Type::WALL);

	//Fila 4
	App->collisions->AddCollider({ 42, 179, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 179, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 106, 179, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 138, 179, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 179, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 202, 179, 13, 10 }, Collider::Type::WALL);

	//Fila 5
	App->collisions->AddCollider({ 42, 211, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 211, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 106, 211, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 138, 211, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 211, 13, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 202, 211, 13, 10 }, Collider::Type::WALL);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 150, 220);
	App->enemies->AddEnemy(Enemy_Type::CARGOL, 182, 114);



	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	return ret;
}

UpdateResult SceneLevel1::Update()
{
	

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	
	
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);
	App->render->DrawTexture(hud, 0, -8, NULL);
	App->render->DrawTexture(machineTexture, 104, 96, NULL);
	App->render->DrawTexture(PowerUp, 88, 78, NULL);
	if (App->player->destroyed == true|| App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_DOWN)
	{
		App->render->DrawTexture(loseScreen, -20, 15, NULL);
		App->enemies->Disable();
	}
	if (App->player->win == true|| App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_DOWN)
	{
		App->render->DrawTexture(winScreen, -10, 15, NULL);
		App->enemies->Disable();
	}
	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	
	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)
	App->collisions->Disable();
	return true;
}