#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "Enemy.h"
#include "Enemy_BrownRobot.h"
#include "Enemy_Cargol.h"
#include "Enemy_Flower.h"
#include "Pasive_Flower.h"
#include "Win_Blue_Machine.h"
#include "Enemy_Conill.h"
#include "Enemy_Monkey.h"
#include "Enemy_Boss_Banana.h"
#include "Enemy_Boss_Monkey.h"


#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	enemyTexture = App->textures->Load("Assets/enemies/enemies.png");
	//enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}

	return true;
}

UpdateResult ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Update();

			if (enemies[i]->death)
			{
				if (enemies[i]->cooldown >= 100)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
				else
				{
					enemies[i]->cooldown++;
				}
			}
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::BROWNROBOT:
					enemies[i] = new Enemy_BrownRobot(info.x, info.y);
					break;
				case Enemy_Type::CARGOL:
					enemies[i] = new Enemy_Cargol(info.x, info.y);
					break;
				case Enemy_Type::PLANT:
					enemies[i] = new Enemy_Flower(info.x, info.y);
					break;
				case Enemy_Type::PASIVEPLANT:
					enemies[i] = new Pasive_Flower(info.x, info.y);
					break;
				case Enemy_Type::BLUE_MACHINE:
					enemies[i] = new Win_Blue_Machine(info.x, info.y);
					break;
				case Enemy_Type::RABBIT:
					enemies[i] = new Enemy_Conill(info.x, info.y);
					break;
				case Enemy_Type::MONKEY:
					enemies[i] = new Enemy_Monkey(info.x, info.y);
					break;
				case Enemy_Type::BANANA_BOSS:
					enemies[i] = new Enemy_Boss_Banana(info.x, info.y);
					break; 
				case Enemy_Type::MONKEY_BOSS:
					enemies[i] = new Enemy_Boss_Monkey(info.x, info.y);
					break;
			}
			enemies[i]->texture = enemyTexture;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (c2->type == Collider::Type::FIRE)
			{
				enemies[i]->death = true;
			}
			
		}

	}

}

//void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
//{
//	for (uint i = 0; i < MAX_ENEMIES; ++i)
//	{
//		if (enemies[i] != nullptr)
//		{
//			enemies[i]->OnCollision(c1, c2);
//			if (enemies[i]->death)
//			{
//				App->collisions->RemoveCollider(enemies[i]->collider);
//				delete enemies[i];
//				enemies[i] = nullptr;
//			}
//		}
//		break;
//	}
//}


