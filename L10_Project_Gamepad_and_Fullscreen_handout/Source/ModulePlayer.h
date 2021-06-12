#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleBomb.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	UpdateResult PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;
	

	// Draws gamepad debug info in the screen
	void DebugDrawGamepadInfo();

public:
	// Position of the player in the map
	fPoint position;
	fPoint prevposition;

	// The speed in which we move the player (pixels per frame)
	float speed = 0.5f;
	int lifes = 3;
	int timer = 0;
	int timerS = 00;
	int timerM = 4;
	int comodin = 0;


	// Countdown to handle shot spacing
	int shotMaxCountdown = 20;
	int shotCountdown = 0;
	
	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* player = nullptr;
	SDL_Texture* powerTouchText = nullptr;
	SDL_Texture* BombPlusText = nullptr;
	SDL_Texture* machineTraking = nullptr;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation deadAnim;


	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool godmode = false;
	bool win = false;
	bool powerActive = true;
	bool powerTouch = false;
	bool death = false;
	bool stop = false;
	// Sound effects indices

	uint deadFx = 0;
	uint winFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[150] = { "\0" };
	

	// Debugdraw for gamepad data
	bool debugGamepadInfo = false;

};

#endif // __MODULEPLAYER_H__