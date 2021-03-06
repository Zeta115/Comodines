#ifndef __SCENELEVEL1_H__
#define __SCENELEVEL1_H__

#include "Module.h"
#include "Animation.h"


struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	// Constructor
	SceneLevel1(bool startEnabled);

	// Destructor
	~SceneLevel1();

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
	SDL_Texture* machineTracking = nullptr;
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
	SDL_Texture* machineTexture = nullptr;

	int machine1 = 1;
	int machine2 = 1;
	bool inLevel1 = false;
};

#endif  // __SCENELEVEL1_H__