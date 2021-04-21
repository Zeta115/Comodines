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

	//Bottom
	App->collisions->AddCollider({ 0, 242, 3930, 16 }, Collider::Type::WALL);

	//Top
	App->collisions->AddCollider({ 0, 30, 3930, 16 }, Collider::Type::WALL);

	//Left
	//App->collisions->AddCollider({ 0, 30, 1375, 16 }, Collider::Type::WALL);
	//Right
	//App->collisions->AddCollider({ 0, 30, 3930, 16 }, Collider::Type::WALL);


	//First two columns colliders
	App->collisions->AddCollider({ 40, 32, 48, 56 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

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