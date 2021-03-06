#ifndef __SCENEBOSS_H__
#define __SCENEBOSS_H__

#include "Module.h"
#include "Animation.h"


struct SDL_Texture;

class SceneLevelBoss : public Module
{
public:
	// Constructor
	SceneLevelBoss(bool startEnabled);

	// Destructor
	~SceneLevelBoss();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* decoration = nullptr;
	SDL_Texture* winScreen = nullptr;
	SDL_Texture* loseScreen = nullptr;
	SDL_Texture* hud = nullptr;
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
	SDL_Texture* machineTexture = nullptr;


	bool inLevel3 = false;

};

#endif  // __SCENELEVEL1_H__