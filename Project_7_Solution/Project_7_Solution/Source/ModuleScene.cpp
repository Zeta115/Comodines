#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bgTexture = App->textures->Load("Assets/Map/mapa2.png");

	App->audio->PlayMusic("Assets/Audio/music/Area_1.ogg", 1.0f);

	// Colliders

	//Limits
	//Bottom
	App->collisions->AddCollider({ 0, 242, 3930, 16 }, Collider::Type::WALL);
	//Top
	App->collisions->AddCollider({ 0, 33, 3930, 30 }, Collider::Type::WALL);
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
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 100, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 180, 80);

	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.x += 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}