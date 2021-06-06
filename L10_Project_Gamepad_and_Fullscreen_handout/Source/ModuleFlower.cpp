#include "ModuleFlower.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModuleFlower::ModuleFlower(bool startEnabled) : Module(startEnabled)
{
	// Idle
	idle.PushBack({ 0, 0, 16, 16 });

	// Dead
	dead.PushBack({ 16, 0, 16, 16 });
}

ModuleFlower::~ModuleFlower()
{

}

// Load assets
bool ModuleFlower::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	flowerTexture = App->textures->Load("Assets/SpecialElements/YellowFlower.png");


	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		currentAnimation[i] = &idle;
	}

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		App->sceneLevel_2->Disable();
		flowers[0] = CreateFlower(88, 63, flowerTexture);
		flowers[1] = CreateFlower(152, 63, flowerTexture);
		flowers[2] = CreateFlower(88, 159, flowerTexture);
		flowers[3] = CreateFlower(152, 159, flowerTexture);
	

		flowers[5] = CreateFlower(88, 31, flowerTexture);
		flowers[6] = CreateFlower(72, 31, flowerTexture);
		flowers[7] = CreateFlower(136, 31, flowerTexture);
		flowers[8] = CreateFlower(152, 31, flowerTexture);

		flowers[9] = CreateFlower(88, 47, flowerTexture);
		flowers[10] = CreateFlower(56, 47, flowerTexture);
		flowers[11] = CreateFlower(216, 47, flowerTexture);

		flowers[12] = CreateFlower(72, 63, flowerTexture);
		flowers[13] = CreateFlower(104, 63, flowerTexture);
		flowers[14] = CreateFlower(168, 63, flowerTexture);
		flowers[15] = CreateFlower(184, 63, flowerTexture);

		flowers[16] = CreateFlower(24, 79, flowerTexture);
		flowers[17] = CreateFlower(56, 79, flowerTexture);
		flowers[18] = CreateFlower(88, 79, flowerTexture);
		flowers[19] = CreateFlower(152, 79, flowerTexture);
		flowers[20] = CreateFlower(184, 79, flowerTexture);

		flowers[21] = CreateFlower(56, 95, flowerTexture);
		flowers[22] = CreateFlower(72, 95, flowerTexture);
		flowers[23] = CreateFlower(200, 95, flowerTexture);
		flowers[24] = CreateFlower(216, 95, flowerTexture);

		flowers[25] = CreateFlower(40, 127, flowerTexture);
		flowers[26] = CreateFlower(88, 127, flowerTexture);
		flowers[27] = CreateFlower(120, 127, flowerTexture);
		flowers[28] = CreateFlower(216, 127, flowerTexture);

		flowers[29] = CreateFlower(24, 159, flowerTexture);
		flowers[30] = CreateFlower(40, 159, flowerTexture);
		flowers[31] = CreateFlower(104, 159, flowerTexture);
		flowers[32] = CreateFlower(168, 159, flowerTexture);
		flowers[33] = CreateFlower(200, 159, flowerTexture);
		flowers[34] = CreateFlower(216, 159, flowerTexture);

		flowers[35] = CreateFlower(56, 175, flowerTexture);
		flowers[36] = CreateFlower(88, 175, flowerTexture);
		flowers[37] = CreateFlower(120, 175, flowerTexture);
		flowers[38] = CreateFlower(152, 175, flowerTexture);
		flowers[39] = CreateFlower(184, 175, flowerTexture);
		flowers[40] = CreateFlower(216, 175, flowerTexture);

		flowers[41] = CreateFlower(40, 191, flowerTexture);
		flowers[42] = CreateFlower(88, 191, flowerTexture);

	}
	if (App->sceneLevel_2->IsEnabled() == true)
	{
		App->sceneLevel_1->Disable();
		//LEFT OF THE BRIDGE

		flowers[0] = CreateFlower(120, 112, flowerTexture);

		flowers[1] = CreateFlower(152, 48, flowerTexture);

		flowers[2] = CreateFlower(24, 64, flowerTexture);
		flowers[3] = CreateFlower(56, 64, flowerTexture);
		flowers[4] = CreateFlower(88, 64, flowerTexture);
		flowers[5] = CreateFlower(104, 64, flowerTexture);
		flowers[6] = CreateFlower(120, 64, flowerTexture);
		flowers[7] = CreateFlower(136, 64, flowerTexture);
		flowers[8] = CreateFlower(168, 64, flowerTexture);
		flowers[9] = CreateFlower(200, 64, flowerTexture);
		flowers[10] = CreateFlower(216, 64, flowerTexture);

		flowers[11] = CreateFlower(152, 80, flowerTexture);
		flowers[12] = CreateFlower(184, 80, flowerTexture);
		flowers[13] = CreateFlower(216, 80, flowerTexture);

		flowers[14] = CreateFlower(24, 96, flowerTexture);
		flowers[15] = CreateFlower(72, 96, flowerTexture);
		flowers[16] = CreateFlower(120, 96, flowerTexture);
		flowers[17] = CreateFlower(152, 96, flowerTexture);
		flowers[18] = CreateFlower(168, 96, flowerTexture);
		flowers[19] = CreateFlower(184, 96, flowerTexture);
		flowers[20] = CreateFlower(216, 96, flowerTexture);

		flowers[21] = CreateFlower(56, 112, flowerTexture);
		flowers[22] = CreateFlower(104, 112, flowerTexture);

		flowers[23] = CreateFlower(168, 128, flowerTexture);
		flowers[24] = CreateFlower(216, 128, flowerTexture);
		flowers[25] = CreateFlower(120, 128, flowerTexture);
		flowers[26] = CreateFlower(152, 128, flowerTexture);

		flowers[27] = CreateFlower(120, 144, flowerTexture);
		flowers[28] = CreateFlower(152, 144, flowerTexture);

		flowers[29] = CreateFlower(40, 160, flowerTexture);
		flowers[30] = CreateFlower(88, 160, flowerTexture);
		flowers[31] = CreateFlower(104, 160, flowerTexture);
		flowers[32] = CreateFlower(120, 160, flowerTexture);
		flowers[33] = CreateFlower(184, 160, flowerTexture);
		flowers[34] = CreateFlower(200, 160, flowerTexture);

		flowers[35] = CreateFlower(88, 192, flowerTexture);
		flowers[36] = CreateFlower(156, 192, flowerTexture);
		flowers[37] = CreateFlower(184, 192, flowerTexture);
		flowers[38] = CreateFlower(1000, 1000, flowerTexture);
		flowers[39] = CreateFlower(1000, 1000, flowerTexture);
		flowers[40] = CreateFlower(1000, 1000, flowerTexture);

		flowers[41] = CreateFlower(1000, 1000, flowerTexture);
		flowers[42] = CreateFlower(1000, 1000, flowerTexture);
		
	
	}

	return ret;
}

UpdateResult ModuleFlower::Update()
{
	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		currentAnimation[i]->Update();

		if (flowers[i].isDestroyed)
		{
			flowers[i].dCount++;
			if (flowers[i].dCount >= 90)
			{
				flowers[i].destroyed = true;
			}
			if (flowers[i].destroyed)
			{
				flowers[i].colliderT->pendingToDelete = true;
			}
		}
	}


	return UpdateResult::UPDATE_CONTINUE;
}


UpdateResult ModuleFlower::PostUpdate()
{

	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		if (App->sceneLevel_1->IsEnabled() == true && !flowers[i].destroyed)
		{
			App->render->DrawTexture(flowers[i].flowerT, flowers[i].x, flowers[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
		if (App->sceneLevel_2->IsEnabled() == true && !flowers[i].destroyed)
		{
			App->render->DrawTexture(flowers[i].flowerT, flowers[i].x, flowers[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}



void ModuleFlower::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < NUM_FLOWERS; ++i)
	{
		if (flowers[i].colliderT == c1 && !flowers[i].isDestroyed)
		{
			switch (c2->type)
			{
			case Collider::Type::FIRE:
			{
				flowers[i].isDestroyed = true;
				currentAnimation[i] = &dead;
			} break;

			default:
				break;
			}
			break;
		}
	}
}

Flower ModuleFlower::CreateFlower(int x, int y, SDL_Texture* t)
{
	Flower f;

	f.colliderT = App->collisions->AddCollider({ x, y, 16, 16 }, Collider::Type::FLOWER, this);
	f.flowerT = t;
	f.x = x;
	f.y = y;
	f.isDestroyed = false;

	return f;
}