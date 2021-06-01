/*#ifndef __SCENELEVEL2_H__
#define __SCENELEVEL2_H__

#include "Module.h"
#include "Animation.h"


struct SDL_Texture;

class SceneLevel2 : public Module
{
public:
	// Constructor
	SceneLevel2(bool startEnabled);

	// Destructor
	~SceneLevel2();

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
	SDL_Texture* winScreen = nullptr;
	SDL_Texture* loseScreen = nullptr;
	SDL_Texture* hud = nullptr;
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
	SDL_Texture* machineTexture = nullptr;


};

#endif  // __SCENELEVEL2_H__*/