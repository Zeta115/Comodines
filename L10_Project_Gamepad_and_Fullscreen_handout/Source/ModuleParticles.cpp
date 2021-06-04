#include "ModuleParticles.h"

#include "Application.h"

#include "Enemy.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleInput.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	bomb_texture = App->textures->Load("Assets/SpecialElements/Bomb.png");

	// Explosion particle
	bom.anim.PushBack({ 2, 227, 16, 16 }); //BOMB COL
	bom.anim.PushBack({ 18, 226, 16, 16 });
	bom.anim.PushBack({ 35, 226, 16, 16 });
	bom.speed.x = 0;
	bom.lifetime = 120;
	bom.anim.speed = 0.07f;
	bom.anim.loop = true;

	explosion.anim.PushBack({ 2, 2, 16,16 }); //FIRE COL
	explosion.anim.PushBack({ 3, 76, 16,16 });
	explosion.anim.PushBack({ 2, 150, 16,16 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.5f;
	explosion.lifetime = 60;

	explosion_up_1.anim.PushBack({ 20, 38, 14, 16 });
	explosion_up_1.anim.PushBack({ 21, 112, 14, 16 });
	explosion_up_1.anim.PushBack({ 20, 188, 16, 16 });
	explosion_up_1.anim.loop = false;
	explosion_up_1.anim.speed = 0.5f;
	explosion_up_1.lifetime = 60;

	explosion_down_2.anim.PushBack({ 3, 38, 14, 16 });
	explosion_down_2.anim.PushBack({ 4, 112, 14, 16 });
	explosion_down_2.anim.PushBack({ 2, 188, 16, 16 });
	explosion_down_2.anim.loop = false;
	explosion_down_2.anim.speed = 0.5f;
	explosion_down_2.lifetime = 60;

	explosion_down_1.anim.PushBack({ 20, 57, 14, 16 });
	explosion_down_1.anim.PushBack({ 21, 131, 14, 16 });
	explosion_down_1.anim.PushBack({ 20, 207, 16, 16 });
	explosion_down_1.anim.loop = false;
	explosion_down_1.anim.speed = 0.5f;
	explosion_down_1.lifetime = 60;

	explosion_up_2.anim.PushBack({ 3, 57, 16, 14 });
	explosion_up_2.anim.PushBack({ 4, 131, 16, 14 });
	explosion_up_2.anim.PushBack({ 2, 207, 16, 16 });
	explosion_up_2.anim.loop = false;
	explosion_up_2.anim.speed = 0.5f;
	explosion_up_2.lifetime = 60;

	explosion_right_1.anim.PushBack({ 40, 3, 16, 14 });
	explosion_right_1.anim.PushBack({ 41, 77, 16, 14 });
	explosion_right_1.anim.PushBack({ 41, 150, 16, 16 });
	explosion_right_1.anim.loop = false;
	explosion_right_1.anim.speed = 0.5f;
	explosion_right_1.lifetime = 60;

	explosion_right_2.anim.PushBack({ 21, 3, 16, 14 });
	explosion_right_2.anim.PushBack({ 22, 3, 16, 14 });
	explosion_right_2.anim.PushBack({ 22, 150, 16, 16 });
	explosion_right_2.anim.loop = false;
	explosion_right_2.anim.speed = 0.5f;
	explosion_right_2.lifetime = 60;

	explosion_left_1.anim.PushBack({ 2, 21, 15, 14 });
	explosion_left_1.anim.PushBack({ 21, 95, 16, 14 });
	explosion_left_1.anim.PushBack({ 22, 169, 16, 16 });
	explosion_left_1.anim.loop = false;
	explosion_left_1.anim.speed = 0.5f;
	explosion_left_1.lifetime = 60;

	explosion_left_2.anim.PushBack({ 20, 21, 16, 16 });
	explosion_left_2.anim.PushBack({ 3, 95, 16, 14 });
	explosion_left_2.anim.PushBack({ 2, 169, 16, 16 });
	explosion_left_2.anim.loop = false;
	explosion_left_2.anim.speed = 0.5f;
	explosion_left_2.lifetime = 60;

	return true;
}

UpdateResult ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	
	if (ExplosionUp == true)
	{

		if (timerE <= 100) {
			timerE++;
		}

		if (timerE >= 100)
		{
			
			App->particles->bom.isAlive = false;
			ExplosionUp = false;
			timerE = 0;
		}
	}

	if (c1->type == Collider::Type::FIREUP2 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIREUP2 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
		{
			App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIREUP2);
			
			if (c1->type == Collider::Type::FIREUP1 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIREUP1!= c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
			{
				App->particles->AddParticle(App->particles->explosion_up_1, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIREUP1);
			}
		}

	if (c1->type == Collider::Type::FIREDOWN2 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIREDOWN2 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
	{
		App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIREDOWN2);

		if (c1->type == Collider::Type::FIREDOWN1 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIREDOWN1 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
		{
			App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIREDOWN1);
		}
	}

	if (c1->type == Collider::Type::FIRERIGHT2 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIRERIGHT2 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
	{
		App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIRERIGHT2);

		if (c1->type == Collider::Type::FIRERIGHT1 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIRERIGHT1 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
		{
			App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIRERIGHT1);
		}
	}

	if (c1->type == Collider::Type::FIRELEFT1 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIRELEFT1 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
	{
		App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIRELEFT1);

		if (c1->type == Collider::Type::FIRELEFT2 != c2->type == Collider::Type::WALL && App->particles->bom.isAlive == false || c1->type == Collider::Type::FIRELEFT2 != c2->type == Collider::Type::FLOWER && App->particles->bom.isAlive == false)
		{
			App->particles->AddParticle(App->particles->explosion_up_2, App->particles->bom.position.x, App->particles->bom.position.y + -10, Collider::Type::FIRELEFT2);
		}
	}






		// Always destroy particles that collide
		/*if (particles[i] != nullptr && particles[i]->collider == c1)
		{
		//	particles[i]->pendingToDelete = true;
			//particles[i]->collider->pendingToDelete = true;
			break;
		}*/
	/*for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		
	}*/
	// Here we delete enemies as they touch the fire

	/*if (c1->type == Collider::Type::FIRE && c2->type == Collider::Type::ENEMY)
	{
		App->textures->Disable();
	}*/

}

UpdateResult ModuleParticles::Update()
{
	if ((App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_DOWN)) //|| (pad.x))
	{
		App->particles->bom.position.x = App->player->position.x;
		App->particles->bom.position.y = App->player->position.y;

		if (App->player->BombUp == true)
		{
			App->particles->AddParticle(App->particles->bom, App->particles->bom.position.x, App->particles->bom.position.y + 6, Collider::Type::BOMB);
			App->audio->PlayFx(App->player->placeFx);
			App->player->BombUp = false;
			ExplosionUp = true;
		}
		
	}
	if (App->particles->bom.isAlive == false) //ara no entra aqui
		{
			//center
			App->particles->AddParticle(App->particles->explosion, App->particles->bom.position.x, App->particles->bom.position.y + 6, Collider::Type::FIRE);
			App->audio->PlayFx(App->player->blastFx);
			App->input->ShakeController(0, 60, 1.0f);
			App->particles->bom.isAlive = true;
		}
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleParticles::PostUpdate()
{
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];
		
		if (particle != nullptr && particle->isAlive)
		{
				App->render->DrawTexture(bomb_texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}
	
	return UpdateResult::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}