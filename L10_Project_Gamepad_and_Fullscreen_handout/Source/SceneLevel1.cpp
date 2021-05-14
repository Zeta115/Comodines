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

	bgTexture = App->textures->Load("Assets/Map/Mapa.png");
	App->audio->PlayMusic("Assets/Audio/music/Area_1.ogg", 1.0f);
	loseScreen = App->textures->Load("Assets/Screens/lose.PNG");
	winScreen = App->textures->Load("Assets/Screens/win.PNG");
	hud = App->textures->Load("Assets/Hud/hud.png");
	machineTexture = App->textures->Load("Assets/Map/Reactor_1.png");

	// Colliders

//Limits
//Bottom
	App->collisions->AddCollider({ 0, 239, 600, 17 }, Collider::Type::WALL);
	//Top
	App->collisions->AddCollider({ 0, 0, 600, 57 }, Collider::Type::WALL);
	//Left
	App->collisions->AddCollider({ 0, 33, 25, 600 }, Collider::Type::WALL);
	//Right
	App->collisions->AddCollider({ 232, 33, 25, 600 }, Collider::Type::WALL);

	// Stones
	/// 1r: donde empieza la piedra a partir de la x - 2n: donde empieza la piedra a partir de la y - 3r: ample de la pedra - 4rt: alçada de la pedra

	//First two columns colliders
	//Fila 1
	App->collisions->AddCollider({ 40, 79, 16, 10 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 73, 79, 16, 10 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 79, 16, 10 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 79, 16, 10 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 79, 16, 10 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 79, 16, 10 }, Collider::Type::WALL);//6

	//Fila 2
	App->collisions->AddCollider({ 40, 111, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 111, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 111, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 111, 16, 10 }, Collider::Type::WALL);

	//machine
	App->collisions->AddCollider({ 105, 117, 46, 22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 105, 139, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 139, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, 139, 14, 14 }, Collider::Type::MACHINE);

	//PowerUp
	App->collisions->AddCollider({ 89 ,80, 15,15 }, Collider::Type::POWERUP);

	//Fila 3
	App->collisions->AddCollider({ 40, 143, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 143, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 143, 16, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 143, 16, 10 }, Collider::Type::WALL);

	//Fila 4
	App->collisions->AddCollider({ 40, 175, 16, 10 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 73, 175, 16, 10 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 175, 16, 10 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 175, 16, 10 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 175, 16, 10 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 175, 16, 10 }, Collider::Type::WALL);//6

	//Fila 5
	App->collisions->AddCollider({ 40, 207, 16, 10 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 73, 207, 16, 10 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 207, 16, 10 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 207, 16, 10 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 207, 16, 10 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 207, 16, 10 }, Collider::Type::WALL);//6

	//flower collider
	App->collisions->AddCollider({ 56, 111, 15, 10 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 150, 220);
	App->enemies->AddEnemy(Enemy_Type::CARGOL, 182, 114);
	App->enemies->AddEnemy(Enemy_Type::PLANT, 56, 112);


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

bool SceneLevel1::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	
	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)
	App->collisions->Disable();
	return true;
}