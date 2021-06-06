#include "SceneLevel1.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModuleFlower.h"
#include "ModulePlayer.h"
#include "SceneLevel2.h"
#include "ModuleParticles.h"

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
	machineTracking= App->textures->Load("Assets/Hud/Machine_Traking.png");

	// Colliders

//Limits
    //Bottom
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
	App->collisions->AddCollider({ 40, 47, 16, 16 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 72, 47, 16, 16 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 47, 16, 16 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 47, 16, 16 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 47, 16, 16 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 47, 16, 16 }, Collider::Type::WALL);//6

	//Fila 2
	App->collisions->AddCollider({ 40, 79, 16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 79, 16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 79, 16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 79, 16, 16 }, Collider::Type::WALL);

	//machine
	App->collisions->AddCollider({ 104, 79, 48, 22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 101, 16, 26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 136, 101, 16, 26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, 99, 14, 14 }, Collider::Type::MACHINE);

	//PowerUp
	App->collisions->AddCollider({ 89 ,80, 15,15 }, Collider::Type::POWERUP);

	//Fila 3
	App->collisions->AddCollider({ 40, 111, 16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 111,  16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 168, 111, 16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 111,  16, 16 }, Collider::Type::WALL);

	//Fila 4
	App->collisions->AddCollider({ 40, 143, 16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 72, 143,  16, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 104, 143, 16, 16 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 143, 16, 16 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 143, 16, 16 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 143, 16, 16 }, Collider::Type::WALL);//6

	//Fila 5
	App->collisions->AddCollider({ 40, 175, 16, 16 }, Collider::Type::WALL);//1
	App->collisions->AddCollider({ 72, 175, 16, 16 }, Collider::Type::WALL);//2
	App->collisions->AddCollider({ 104, 175, 16, 16 }, Collider::Type::WALL);//3
	App->collisions->AddCollider({ 136, 175, 16, 16 }, Collider::Type::WALL);//4
	App->collisions->AddCollider({ 168, 175, 16, 16 }, Collider::Type::WALL);//5
	App->collisions->AddCollider({ 200, 175, 16, 16 }, Collider::Type::WALL);//6
	
	

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::RABBIT, 40, 85);
	App->enemies->AddEnemy(Enemy_Type::BROWNROBOT, 149, 130); // 104, 31
	//App->enemies->AddEnemy(Enemy_Type::BLUE_MACHINE, 184, 36);
	//App->enemies->AddEnemy(Enemy_Type::BLUE_MACHINE2, 55, 150);
	//App->enemies->AddEnemy(Enemy_Type::BROWNROBOT, 16, 44);
	//App->enemies->AddEnemy(Enemy_Type::BROWNROBOT2, 70, 140);
	//App->enemies->AddEnemy(Enemy_Type::CARGOL, 70, 140);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->particles->Enable();
	App->Placebomb->Enable();
	App->flowers->Enable();

	inLevel1 = true;
	App->sceneLevel_2->inLevel2 = false;
	App->sceneLevel_Boss->inLevel3 = false;
	return ret;
}

UpdateResult SceneLevel1::Update()
{
	
	if (App->input->keys[SDL_SCANCODE_0] == KeyState::KEY_DOWN || App->player->win == true)
	{
		inLevel1 = false;
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
		App->player->Disable();
		App->enemies->Disable();
		App->collisions->Disable();
		App->particles->Disable();
		App->Placebomb->Disable();
		App->flowers->Disable();
	}
	if (App->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_DOWN)
	{
		machine1--;
		machine2--;
	}
	/*if (App->input->keys[SDL_SCANCODE_9] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}*/

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	
	App->render->DrawTexture(bgTexture, 0, 15, NULL); 
	App->render->DrawTexture(decoration, 0, 15, NULL);
	App->render->DrawTexture(hud, 0, 0, NULL);   
	App->render->DrawTexture(machineTexture, 104, 64, NULL);
	

	if (machine2 <= 0)
	{
		App->render->DrawTexture(machineTracking, 64, 8, NULL);
	}
	if (machine1 <= 0)
	{
		App->render->DrawTexture(machineTracking, 56, 8, NULL);
	}
	if (App->player->destroyed == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 160);
	}

	if (App->player->win == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
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