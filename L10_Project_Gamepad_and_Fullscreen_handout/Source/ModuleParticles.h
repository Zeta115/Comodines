#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#include "ModuleBomb.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	UpdateResult PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	UpdateResult PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(const Particle& particle, int x, int y, SDL_Rect rec = {0,0,12,12}, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	//Template particle for an explosion
	Particle explosion;
	Particle explosion_up_1;
	Particle explosion_up_2;

	Particle explosion_down_1;
	Particle explosion_down_2;

	Particle explosion_right_1;
	Particle explosion_right_2;

	Particle explosion_left_1;
	Particle explosion_left_2;
	Particle bom;
	Particle dead;

	

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* bomb_texture = nullptr;
	//SDL_Texture* Dead_texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };
};

#endif // __MODULEPARTICLES_H__