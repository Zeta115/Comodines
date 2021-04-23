#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles();

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
<<<<<<< HEAD
	SDL_Texture* texture = nullptr;

=======
	
	SDL_Texture* bomb_texture = nullptr;
	
	
>>>>>>> d5cc652be73efcba1ab5c03e33f95a2f3e6666e3
	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };
	SDL_Texture* Fire_texture = nullptr;
	SDL_Texture* Dead_texture = nullptr;
public:
	//Template particle for an explosion
	Particle explosion;

<<<<<<< HEAD
	//Template particle for a laser
	Particle laser;
=======
	Particle explosion_Down_1;
	Particle explosion_Down_2;

	Particle explosion_right_1;
	Particle explosion_right_2;

	Particle explosion_left_1;
	Particle explosion_left_2;
	Particle bom;
	Particle dead;
	
	
>>>>>>> d5cc652be73efcba1ab5c03e33f95a2f3e6666e3
};

#endif // !__MODULEPARTICLES_H__