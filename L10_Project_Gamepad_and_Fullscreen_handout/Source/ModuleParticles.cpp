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
	
	if (c1->type == Collider::Type::FIRE && c2->type == Collider::Type::WALL)
	{
		//c1->pendingToDelete = true;
	}

}

UpdateResult ModuleParticles::Update()
{

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

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, SDL_Rect rec, Collider::Type colliderType, uint delay)
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
			rec.x = newParticle->anim.GetCurrentFrame().x;
			rec.y = newParticle->anim.GetCurrentFrame().y;
			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(rec, colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}