#include "Application.h"

#include "ModuleBomb.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"


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
	ColliderBomb = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::BOMB);

	ColliderFireCenter = App->collisions->AddCollider({ App->particles->explosion.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);

	ColliderFireup1 = App->collisions->AddCollider({ App->particles->explosion_up_1.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);
	ColliderFireup2 = App->collisions->AddCollider({ App->particles->explosion_up_2.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);

	ColliderFiredown1 = App->collisions->AddCollider({ App->particles->explosion_down_1.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);
	ColliderFiredown2 = App->collisions->AddCollider({ App->particles->explosion_down_2.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);

	ColliderFireleft1 = App->collisions->AddCollider({ App->particles->explosion_left_1.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);
	ColliderFireleft2 = App->collisions->AddCollider({ App->particles->explosion_left_2.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);

	CollideFireright1 = App->collisions->AddCollider({ App->particles->explosion_right_1.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);
	CollideFireright2 = App->collisions->AddCollider({ App->particles->explosion_right_1.position.x, App->particles->explosion.position.y, 12, 12 }, Collider::Type::INFIRE, this);


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

	ColliderFireCenter->SetPos(App->particles->bom.position.x + 1, App->particles->bom.position.y+6);//cc
	ColliderFireup1->SetPos(App->particles->bom.position.x + 1, App->particles->bom.position.y -7);//c
	ColliderFireup2->SetPos(App->particles->bom.position.x + 1, App->particles->bom.position.y -24);// e
	ColliderFiredown1->SetPos(App->particles->bom.position.x +1, App->particles->bom.position.y + 21);//c
	ColliderFiredown2->SetPos(App->particles->bom.position.x +1, App->particles->bom.position.y + 36);//e
	ColliderFireleft1->SetPos(App->particles->bom.position.x-12, App->particles->bom.position.y + 6);//c
	ColliderFireleft2->SetPos(App->particles->bom.position.x-29, App->particles->bom.position.y + 6);//e
	CollideFireright1->SetPos(App->particles->bom.position.x+12, App->particles->bom.position.y + 6);//c
	CollideFireright2->SetPos(App->particles->bom.position.x+29, App->particles->bom.position.y + 6);//e

	if (ExplosionUp == true)
	{

		if (timerE <= 120) {
			timerE++;
		}

		if (timerE >= 120)
		{
			timerE = 0;
			App->particles->bom.isAlive = false;
			/*ColliderFireup1->pendingToDelete = true;
			ColliderFireCenter->pendingToDelete = true;
			ColliderFireup1->pendingToDelete = true;
			ColliderFireup2->pendingToDelete = true;
			ColliderFiredown1->pendingToDelete = true;
			ColliderFiredown2->pendingToDelete = true;
			CollideFireright1->pendingToDelete = true;
			CollideFireright2->pendingToDelete = true;
			ColliderFireleft1->pendingToDelete = true;
			ColliderFireleft2->pendingToDelete = true;*/
			DrawBomb();
			ExplosionUp = false;
		}
	}

	if (BombUp == false) {
		if (timerB < 150) {
			timerB++;
		}
		if (timerB == 150) {
			timerB = 0;
			BombUp = true;
		}
	}
	return UpdateResult::UPDATE_CONTINUE;
}



UpdateResult ModuleBomb::PostUpdate()
{

	return UpdateResult::UPDATE_CONTINUE;
}


void ModuleBomb::OnCollision(Collider* c1, Collider* c2)
{

	if (c1 == ColliderFireup1)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireUp1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireUp1 = true;
		}
	}

	if (c1 == ColliderFireup2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireUp2 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireUp2 = true;
		}
	}

	if (c1 == ColliderFiredown1 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireDown1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireDown1 = true;
		}
	}

	if (c1 == ColliderFiredown2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireDown2 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireDown2 = true;
		}
	}

	if (c1 == CollideFireright1 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireRight1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireRight1 = true;
		}
	}

	if (c1 == CollideFireright2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireLeft1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireRight2 = true;
		}
	}
	if (c1 == ColliderFireleft1 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireLeft1 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireLeft1 = true;
		}
	}

	if (c1 == ColliderFireleft2 && BombUp == false)
	{
		if (c2->type == Collider::Type::WALL)
		{
			FireLeft2 = false;
		}
		if (c2->type == Collider::Type::FLOWER)
		{
			FireLeft2 = true;
		}
		
	}

}
	

void ModuleBomb::PutBomb()
{

	FireUp1 = true;
	FireUp2 = true;
	FireDown1 = true;
	FireDown2 = true;
	FireRight1 = true;
	FireRight2 = true;
	FireLeft1 = true;
	FireLeft2 = true;
	App->audio->PlayFx(placeFx);
	App->particles->AddParticle(App->particles->bom, App->particles->bom.position.x, App->particles->bom.position.y + 6, {0,0,16,16}, Collider::Type::BOMB);
}


void ModuleBomb::DrawBomb()
{
	if (App->particles->bom.isAlive == false)
	{
		App->particles->AddParticle(App->particles->explosion, App->particles->bom.position.x, App->particles->bom.position.y + 6, { 0,0,12,12 }, Collider::Type::FIRE);

		if (FireUp1 == true)
		{
			App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			if (FireUp2 == true)
			{
				App->particles->AddParticle(App->particles->explosion_up_1, App->particles->bom.position.x, App->particles->bom.position.y + -26, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			}
		}

		if (FireDown1 == true)
		{
			App->particles->AddParticle(App->particles->explosion_down_2, App->particles->bom.position.x, App->particles->bom.position.y + 22, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			if (FireDown2 == true)
			{
				App->particles->AddParticle(App->particles->explosion_down_1, App->particles->bom.position.x, App->particles->bom.position.y + 38, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			}
		}
		
		if (FireRight1 == true)
		{
			App->particles->AddParticle(App->particles->explosion_right_2, App->particles->bom.position.x+ + 16, App->particles->bom.position.y + 6, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			if (FireRight2 == true)
			{
				App->particles->AddParticle(App->particles->explosion_right_1, App->particles->bom.position.x + 32, App->particles->bom.position.y + 6, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			}
		}
		
		if (FireLeft1 == true)
		{
			App->particles->AddParticle(App->particles->explosion_left_2, App->particles->bom.position.x + -16, App->particles->bom.position.y + 6, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			if (FireLeft2 == true)
			{
				App->particles->AddParticle(App->particles->explosion_left_1, App->particles->bom.position.x + -32, App->particles->bom.position.y + 6, { 0,0,12,12 }, Collider::Type::FIRE, 0);
			}
		}
		App->audio->PlayFx(blastFx);
		App->input->ShakeController(0, 60, 1.0f);
		App->particles->bom.isAlive = true;
	}	
	
}