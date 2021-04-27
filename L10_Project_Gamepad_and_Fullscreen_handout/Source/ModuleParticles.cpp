#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

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
	bomb_texture = App->textures->Load("Assets/special_elements/Bomb.png");
	Fire_texture = App->textures->Load("Assets/effects/Fire.png");
	Dead_texture = App->textures->Load("Assets/bomberman/Bomberman.png");

	// Explosion particle
	bom.anim.PushBack({ 0, 0, 16, 16 });
	bom.anim.PushBack({ 16, 0, 16, 16 });
	bom.anim.PushBack({ 33, 0, 16, 16 });
	bom.speed.x = 0;
	bom.lifetime = 60;
	bom.anim.speed = 0.1f;
	bom.anim.loop = true;

	dead.anim.PushBack({ 2, 51, 15, 20 });
	dead.anim.PushBack({ 19, 51, 13, 19 });
	dead.anim.PushBack({ 33, 51, 19, 20 });
	dead.anim.PushBack({ 51, 51, 21, 19 });
	dead.anim.PushBack({ 71, 51, 21, 19 });
	dead.anim.PushBack({ 93, 50, 22, 21 });
	dead.lifetime = 60;
	dead.anim.speed = 0.1f;
	dead.anim.loop = true;

	explosion.anim.PushBack({ 3, 3, 16, 16 });
	explosion.anim.loop = true;
	explosion.anim.speed = 0.5f;
	explosion.lifetime = 90;

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
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
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
			if (particle->collider->type == Collider::Type::DEAD)
			{
				App->render->DrawTexture(Dead_texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
			if (particle->collider->type == Collider::Type::PLAYER_SHOT)
			{
				App->render->DrawTexture(bomb_texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
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