#ifndef __MODULEBOMB_H__
#define __MODULEBOMB_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class ModuleBomb : public Module
{
public:
	// Constructor
	ModuleBomb(bool startEnabled);

	// Destructor
	~ModuleBomb();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	UpdateResult Update() override;

	UpdateResult PreUpdate() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	UpdateResult PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Draws gamepad debug info in the screen
	void DrawBomb();
	void PutBomb();

private:
	// Position of the player in the map
	fPoint position;
	fPoint prevposition;

	// A set of steps that define the position in the screen
// And an animation for each step


	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	bool bomb = true;	bool ExplosionUp = false;
	bool BombUp = true;
	
	bool FireUp1 = true;
	bool FireUp2 = true;
	bool FireDown1 = true;
	bool FireDown2 = true;
	bool FireRight1 = true;
	bool FireRight2 = true;
	bool FireLeft1 = true;
	bool FireLeft2 = true;
	int timerB = 0;
	int timerE = 0;
	uint blastFx = 0;
	uint placeFx = 0;
	Collider* ColliderFireCenter = nullptr;

	Collider* ColliderFireup1 = nullptr;
	Collider* ColliderFireup2 = nullptr;

	Collider* ColliderFiredown1 = nullptr;
	Collider* ColliderFiredown2 = nullptr;

	Collider* CollideFireright1 = nullptr;
	Collider* CollideFireright2 = nullptr;

	Collider* ColliderFireleft1 = nullptr;
	Collider* ColliderFireleft2 = nullptr;

	Collider* ColliderBomb = nullptr;
};


#endif // __MODULEBOMB_H__