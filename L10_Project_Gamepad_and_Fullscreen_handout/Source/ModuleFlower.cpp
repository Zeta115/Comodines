#include "ModuleFlower.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModuleFlower::ModuleFlower(bool startEnabled) : Module(startEnabled)
{
	idle.PushBack({ 0, 0, 16, 16 });
	dead.PushBack({ 16, 0, 16, 16 });
}

ModuleFlower::~ModuleFlower()
{

}

bool ModuleFlower::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	TextureFlower = App->textures->Load("Assets/SpecialElements/YellowFlower.png");

	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		currentAnimation[i] = &idle;
	}

	if (App->sceneLevel_1->Enabled() == true)
	{
		App->sceneLevel_2->Disable();
		pasiveflower[0] = CreateFlower(88, 63, TextureFlower	);
		pasiveflower[1] = CreateFlower(152, 63, TextureFlower);
		pasiveflower[2] = CreateFlower(88, 159, TextureFlower);
		pasiveflower[3] = CreateFlower(152, 159, TextureFlower);
	

		pasiveflower[5] = CreateFlower(88, 31, TextureFlower);
		pasiveflower[6] = CreateFlower(72, 31, TextureFlower);
		pasiveflower[7] = CreateFlower(136, 31, TextureFlower);
		pasiveflower[8] = CreateFlower(152, 31, TextureFlower);

		pasiveflower[9] = CreateFlower(88, 47, TextureFlower);
		pasiveflower[10] = CreateFlower(56, 47, TextureFlower);
		pasiveflower[11] = CreateFlower(216, 47, TextureFlower);

		pasiveflower[12] = CreateFlower(72, 63, TextureFlower);
		pasiveflower[13] = CreateFlower(104, 63, TextureFlower);
		pasiveflower[14] = CreateFlower(168, 63, TextureFlower);
		pasiveflower[15] = CreateFlower(184, 63, TextureFlower);

		pasiveflower[16] = CreateFlower(24, 79, TextureFlower);
		pasiveflower[17] = CreateFlower(56, 79, TextureFlower);
		pasiveflower[18] = CreateFlower(88, 79, TextureFlower);
		pasiveflower[19] = CreateFlower(152, 79, TextureFlower);
		pasiveflower[20] = CreateFlower(184, 79, TextureFlower);

		pasiveflower[21] = CreateFlower(56, 95, TextureFlower);
		pasiveflower[22] = CreateFlower(72, 95, TextureFlower);
		pasiveflower[23] = CreateFlower(200, 95, TextureFlower);
		pasiveflower[24] = CreateFlower(216, 95, TextureFlower);

		pasiveflower[25] = CreateFlower(40, 127, TextureFlower);
		pasiveflower[26] = CreateFlower(88, 127, TextureFlower);
		pasiveflower[27] = CreateFlower(120, 127, TextureFlower);
		pasiveflower[28] = CreateFlower(216, 127, TextureFlower);

		pasiveflower[29] = CreateFlower(24, 159, TextureFlower);
		pasiveflower[30] = CreateFlower(40, 159, TextureFlower);
		pasiveflower[31] = CreateFlower(104, 159, TextureFlower);
		pasiveflower[32] = CreateFlower(168, 159, TextureFlower);
		pasiveflower[33] = CreateFlower(200, 159, TextureFlower);
		pasiveflower[34] = CreateFlower(216, 159, TextureFlower);

		pasiveflower[35] = CreateFlower(56, 175, TextureFlower);
		pasiveflower[36] = CreateFlower(88, 175, TextureFlower);
		pasiveflower[37] = CreateFlower(120, 175, TextureFlower);
		pasiveflower[38] = CreateFlower(152, 175, TextureFlower);
		pasiveflower[39] = CreateFlower(184, 175, TextureFlower);
		pasiveflower[40] = CreateFlower(216, 175, TextureFlower);

		pasiveflower[41] = CreateFlower(40, 191, TextureFlower);
		pasiveflower[42] = CreateFlower(88, 191, TextureFlower);

	}
	if (App->sceneLevel_2->Enabled() == true)
	{
		App->sceneLevel_1->Disable();

		pasiveflower[0] = CreateFlower(120, 112, TextureFlower);

		pasiveflower[1] = CreateFlower(152, 48, TextureFlower);

		pasiveflower[2] = CreateFlower(24, 64, TextureFlower);
		pasiveflower[3] = CreateFlower(56, 64, TextureFlower);
		pasiveflower[4] = CreateFlower(88, 64, TextureFlower);
		pasiveflower[5] = CreateFlower(104, 64, TextureFlower);
		pasiveflower[6] = CreateFlower(120, 64, TextureFlower);
		pasiveflower[7] = CreateFlower(136, 64, TextureFlower);
		pasiveflower[8] = CreateFlower(168, 64, TextureFlower);
		pasiveflower[9] = CreateFlower(200, 64, TextureFlower);
		pasiveflower[10] = CreateFlower(216, 64, TextureFlower);

		pasiveflower[11] = CreateFlower(152, 80, TextureFlower);
		pasiveflower[12] = CreateFlower(184, 80, TextureFlower);
		pasiveflower[13] = CreateFlower(216, 80, TextureFlower);

		pasiveflower[14] = CreateFlower(24, 96, TextureFlower);
		pasiveflower[15] = CreateFlower(72, 96, TextureFlower);
		pasiveflower[16] = CreateFlower(120, 96, TextureFlower);
		pasiveflower[17] = CreateFlower(152, 96, TextureFlower);
		pasiveflower[18] = CreateFlower(168, 96, TextureFlower);
		pasiveflower[19] = CreateFlower(184, 96, TextureFlower);
		pasiveflower[20] = CreateFlower(216, 96, TextureFlower);

		pasiveflower[21] = CreateFlower(56, 112, TextureFlower);
		pasiveflower[22] = CreateFlower(24, 112, TextureFlower);

		pasiveflower[23] = CreateFlower(168, 128, TextureFlower);
		pasiveflower[24] = CreateFlower(216, 128, TextureFlower);
		pasiveflower[25] = CreateFlower(120, 128, TextureFlower);
		pasiveflower[26] = CreateFlower(152, 128, TextureFlower);

		pasiveflower[27] = CreateFlower(120, 144, TextureFlower);
		pasiveflower[28] = CreateFlower(152, 144, TextureFlower);

		pasiveflower[29] = CreateFlower(40, 160, TextureFlower);
		pasiveflower[30] = CreateFlower(88, 160, TextureFlower);
		pasiveflower[31] = CreateFlower(104, 160, TextureFlower);
		pasiveflower[32] = CreateFlower(120, 160, TextureFlower);
		pasiveflower[33] = CreateFlower(184, 160, TextureFlower);
		pasiveflower[34] = CreateFlower(200, 160, TextureFlower);

		pasiveflower[35] = CreateFlower(88, 192, TextureFlower);
		pasiveflower[36] = CreateFlower(120, 192, TextureFlower);
		pasiveflower[37] = CreateFlower(152, 192, TextureFlower);
		pasiveflower[38] = CreateFlower(1000, 1000, TextureFlower);
		pasiveflower[39] = CreateFlower(1000, 1000, TextureFlower);
		pasiveflower[40] = CreateFlower(1000, 1000, TextureFlower);

		pasiveflower[41] = CreateFlower(1000, 1000, TextureFlower);
		pasiveflower[42] = CreateFlower(1000, 1000, TextureFlower);
		
	
	}

	return ret;
}

UpdateResult ModuleFlower::Update()
{
	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		currentAnimation[i]->Update();

		if (pasiveflower[i].Destroyed)
		{
				pasiveflower[i].dead = true;
				pasiveflower[i].collider->pendingToDelete = true;
		}
	}
	return UpdateResult::UPDATE_CONTINUE;
}


UpdateResult ModuleFlower::PostUpdate()
{

	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		if (App->sceneLevel_1->Enabled() == true && pasiveflower[i].dead == false)
		{
			App->render->DrawTexture(pasiveflower[i].flowerT, pasiveflower[i].x, pasiveflower[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
		if (App->sceneLevel_2->Enabled() == true && pasiveflower[i].dead == false)
		{
			App->render->DrawTexture(pasiveflower[i].flowerT, pasiveflower[i].x, pasiveflower[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return UpdateResult::UPDATE_CONTINUE;
}



void ModuleFlower::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < NUM_FLOWERS; ++i)
	{
		if (pasiveflower[i].collider == c1 && !pasiveflower[i].Destroyed)
		{
			if (c2->type == Collider::Type::FIRE)
			{
				pasiveflower[i].Destroyed = true;
				currentAnimation[i] = &dead;
			}
		}
	}
}

Flower ModuleFlower::CreateFlower(int x, int y, SDL_Texture* t)
{
	Flower Flowers;

	Flowers.collider = App->collisions->AddCollider({ x, y, 16, 16 }, Collider::Type::FLOWER, this);
	Flowers.flowerT = t;
	Flowers.x = x;
	Flowers.y = y;

	return Flowers;
}