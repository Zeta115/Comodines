#include "Application.h"

#include "ModuleBomb.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"


#include <stdio.h>
#include <iostream>
#include <SDL/include/SDL_gamecontroller.h>


ModuleBomb::ModuleBomb(bool startEnabled) : Module(startEnabled)
{


	
}

ModuleBomb::~ModuleBomb()
{

}

bool ModuleBomb::Start()
{
	ColliderBomb = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::BOMB);

	ColliderFireCenter = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);

	ColliderFireup1 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);
	ColliderFireup2 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);

	ColliderFiredown1 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);
	ColliderFiredown2 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);

	ColliderFireleft1 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);
	ColliderFireleft2 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);

	CollideFireright1 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);
	CollideFireright2 = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::FIRE);
	placeFx = App->audio->LoadFx("Assets/Audio/Fx/bomb_plant.wav");
	blastFx = App->audio->LoadFx("Assets/Audio/Fx/bomb_blast.wav");

	return true;
}



UpdateResult ModuleBomb::PreUpdate()
{

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleBomb::Update()
{
	ColliderFireCenter->SetPos(position.x,position.y);
	ColliderFireup1->SetPos(position.x, position.y-16);;
	ColliderFireup2->SetPos(position.x, position.y-32);;
	ColliderFiredown1->SetPos(position.x, position.y+16);;
	ColliderFiredown2->SetPos(position.x, position.y+32);;
	ColliderFireleft1->SetPos(position.x-16, position.y);;
	ColliderFireleft2->SetPos(position.x-32, position.y);;
	CollideFireright1->SetPos(position.x+16, position.y);;
	CollideFireright2->SetPos(position.x+32, position.y);;

	return UpdateResult::UPDATE_CONTINUE;
}



UpdateResult ModuleBomb::PostUpdate()
{

	return UpdateResult::UPDATE_CONTINUE;
}


void ModuleBomb::OnCollision(Collider* c1, Collider* c2)
{

	
	if (c1 == ColliderFireup1 && BombUp == false )
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireUp1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireUp1 = false;
		}
		BombUp = true;
	}

	if (c1 == ColliderFireup2 && BombUp == false )
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireUp2 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireUp2 = false;
		}
		BombUp = true;
	}

	if (c1 == ColliderFiredown1 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireDown1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireDown1 = false;
		}
		BombUp = true;
	}

	if (c1 == ColliderFiredown2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireDown2 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireDown2 = false;
		}
		BombUp = true;
	}

	if (c1 == CollideFireright1 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireRight1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireRight1 = false;
		}
		BombUp = true;
	}

	if (c1 == CollideFireright2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireLeft1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireRight2 = false;
		}
		BombUp = true;
	}
	if (c1 == ColliderFireleft1 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireLeft1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireLeft1 = false;
		}
		BombUp = true;
	}

	if (c1 == ColliderFireleft2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireLeft2 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireLeft2 = false;
		}
		BombUp = true;
	}
}

void ModuleBomb::PutBomb()
{
	App->audio->PlayFx(placeFx);
	App->particles->AddParticle(App->particles->bom, App->particles->bom.position.x, App->particles->bom.position.y + 6, Collider::Type::BOMB);
	
	if (ExplosionUp == true)
	{

		if (timerE <= 100) {
			timerE++;
		}

		if (timerE >= 100)
		{
			timerE = 0;
			App->particles->bom.isAlive = false;
			ExplosionUp = false;
		}
	}

	if (BombUp == true) {
		if (timerB < 150) {
			timerB++;
		}
		if (timerB == 150) {
			timerB = 0;
			BombUp = false;
		}
	}
}


void ModuleBomb::DrawBomb()
{
	if (App->particles->bom.isAlive = false)
	{
		App->particles->AddParticle(App->particles->explosion, App->particles->bom.position.x, App->particles->bom.position.y + 6, Collider::Type::FIRE);

		if (FireUp2 == true)
		{
			App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIRE, 0);
			if (FireUp1 == true)
			{
				App->particles->AddParticle(App->particles->explosion_up_1, App->particles->bom.position.x, App->particles->bom.position.y + -26, Collider::Type::FIRE, 0);
			}
		}

		if (FireDown2 == true)
		{
			App->particles->AddParticle(App->particles->explosion_down_2, App->particles->bom.position.x, App->particles->bom.position.y + 22, Collider::Type::FIRE, 0);
			if (FireDown1 == true)
			{
				App->particles->AddParticle(App->particles->explosion_down_1, App->particles->bom.position.x, App->particles->bom.position.y + 32, Collider::Type::FIRE, 0);
			}
		}
		
		if (FireRight2 == true)
		{
			App->particles->AddParticle(App->particles->explosion_right_2, App->particles->bom.position.x+ +16, App->particles->bom.position.y + 6, Collider::Type::FIRE, 0);
			if (FireRight1 == true)
			{
				App->particles->AddParticle(App->particles->explosion_right_1, App->particles->bom.position.x + 32, App->particles->bom.position.y + 6, Collider::Type::FIRE, 0);
			}
		}
		
		if (FireLeft2 == true)
		{
			App->particles->AddParticle(App->particles->explosion_left_2, App->particles->bom.position.x + -16, App->particles->bom.position.y + 6, Collider::Type::FIRE, 0);
			if (FireLeft1 == true)
			{
				App->particles->AddParticle(App->particles->explosion_left_1, App->particles->bom.position.x + -32, App->particles->bom.position.y + 6, Collider::Type::FIRE, 0);
			}
		}
		App->audio->PlayFx(blastFx);
		App->input->ShakeController(0, 60, 1.0f);
		App->particles->bom.isAlive = true;
	}	
	
}