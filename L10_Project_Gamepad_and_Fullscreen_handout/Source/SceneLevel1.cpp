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
	decoration = App->textures->Load("Assets/Map/MapaDecoration.png");
	App->audio->PlayMusic("Assets/Audio/music/area_1.ogg", 1.0f);
	loseScreen = App->textures->Load("Assets/Screens/lose.PNG");
	winScreen = App->textures->Load("Assets/Screens/win.PNG");
	hud = App->textures->Load("Assets/Hud/hud.png");
	machineTexture = App->textures->Load("Assets/Map/reactor_1.png");

	// Colliders

//Limits
    //Bottom
	App->collisions->AddCollider({ 0, 239, 600, 17 }, Collider::Type::WALL);
	//Top
	App->collisions->AddCollider({ 0, 0, 600, 57 }, Collider::Type::WALL);
	//Left
	App->collisions->AddCollider({ 0, 33, 23, 600 }, Collider::Type::WALL);
	//Right
	App->collisions->AddCollider({ 232, 33, 23, 600 }, Collider::Type::WALL);

	// Stones
	/// 1r: donde empieza la piedra a partir de la x - 2n: donde empieza la piedra a partir de la y - 3r: ample de la pedra - 4rt: al�ada de la pedra

	//First two columns colliders
	//Fila 1
	App->collisions->AddCollider({ 40, 80, 15, 15 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 73, 80, 15, 15 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 80, 15, 15 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 80, 15, 15 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 80, 15, 15 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 80, 15, 15 }, Collider::Type::WALL);//6

	//Fila 2
	App->collisions->AddCollider({ 40, 112, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 112, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 112, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 112, 15, 15 }, Collider::Type::WALL);

	//machine
	App->collisions->AddCollider({ 105, 117, 46, 22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 105, 139, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 139, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, 139, 14, 14 }, Collider::Type::MACHINE);

	//PowerUp
	App->collisions->AddCollider({ 89 ,80, 15,15 }, Collider::Type::POWERUP);

	//Fila 3
	App->collisions->AddCollider({ 40, 145, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 145,  15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 145, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 145,  15, 15 }, Collider::Type::WALL);

	//Fila 4
	App->collisions->AddCollider({ 40, 176, 15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 176,  15, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 176, 15, 15 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 176, 15, 15 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 176, 15, 15 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 176, 15, 15 }, Collider::Type::WALL);//6

	//Fila 5
	App->collisions->AddCollider({ 40, 208, 15, 15 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 73, 208, 15, 15 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 208, 15, 15 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 208, 15, 15 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 208, 15, 15 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 208, 15, 15 }, Collider::Type::WALL);//6
	
	//Flowers
	App->enemies->AddEnemy(Enemy_Type::PLANT, 88, 96);
	App->enemies->AddEnemy(Enemy_Type::PLANT, 152, 96);
	App->enemies->AddEnemy(Enemy_Type::PLANT, 88, 192);	
	App->enemies->AddEnemy(Enemy_Type::PLANT, 152, 192);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 64);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 72, 64);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 136, 64);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 152, 64);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 80);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 80);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 80);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 72, 96);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 104, 96);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 136, 96);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 184, 96);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 24, 112);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 112);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 112);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 130, 112);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 184, 112);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 128);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 72, 128);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 200, 128);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 128);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 40, 160);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 160);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 120, 160);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 160);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 24, 192);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 40, 192);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 104, 192);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 168, 192);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 200, 192);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 192);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 208);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 208);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 120, 208);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 152, 208);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 184, 208);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 208);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 40, 224);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 224);
	

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::RABBIT, 150, 200);
	App->enemies->AddEnemy(Enemy_Type::CARGOL, 182, 114);
	App->enemies->AddEnemy(Enemy_Type::BLUE_MACHINE, 182, 114);
	App->enemies->AddEnemy(Enemy_Type::BROWNROBOT, 53, 155);
	

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
	/*if (App->input->keys[SDL_SCANCODE_0] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}*/

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	
	App->render->DrawTexture(bgTexture, 0, 0, NULL);
	App->render->DrawTexture(decoration, 0, 0, NULL);
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