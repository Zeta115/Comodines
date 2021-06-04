#include "SceneLevel1.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "SceneLevel2.h"

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
	App->collisions->AddCollider({ 104, 101, 16, 26 }, Collider::Type::FLOWER);
	App->collisions->AddCollider({ 136, 101, 16, 26 }, Collider::Type::FLOWER);
	//App->collisions->AddCollider({ 120, 99, 14, 14 }, Collider::Type::MACHINE);

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
	
	//Flowers
	App->enemies->AddEnemy(Enemy_Type::PLANT, 88, 63);
	App->enemies->AddEnemy(Enemy_Type::PLANT, 152, 63);
	App->enemies->AddEnemy(Enemy_Type::PLANT, 88, 159);	
	App->enemies->AddEnemy(Enemy_Type::PLANT, 152, 159);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 31);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 72, 31);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 136, 31);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 152, 31); //64

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 47);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 47); //80
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 47);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 72, 63);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 104, 63);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 168, 63);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 184, 63);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 24, 79);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 79);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 79);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 152, 79);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 184, 79);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 95);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 72, 95);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 200, 95);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 95);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 40, 127);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 127);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 120, 127);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 127);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 24, 159);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 40, 159);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 104, 159);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 168, 159);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 200, 159);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 159);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 56, 175);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 175);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 120, 175);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 152, 175);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 184, 175);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 216, 175);

	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 40, 191);
	App->enemies->AddEnemy(Enemy_Type::PASIVEPLANT, 88, 191);
	

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
	if (App->input->keys[SDL_SCANCODE_0] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
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

	if (App->player->destroyed == true)
	{

		App->render->DrawTexture(loseScreen, -20, 0, NULL);
	}

	if (App->player->win == true)
	{
		App->render->DrawTexture(winScreen, -10, 0, NULL);
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