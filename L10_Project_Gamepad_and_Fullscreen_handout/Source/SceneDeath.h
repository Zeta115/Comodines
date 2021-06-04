#ifndef __SCENEDEATH_H__
#define __SCENEDEATH_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneDeath : public Module
{
public:
	// Constructor
	SceneDeath(bool startEnabled);

	// Destructor
	~SceneDeath();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	SDL_Texture* gameOver = nullptr;
	SDL_Rect BackGround;
	SDL_Rect GameOverImg;

	Animation GameOver;
	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	int sceneCount = 0;

};

#endif	// __SCENEDEATH_H__