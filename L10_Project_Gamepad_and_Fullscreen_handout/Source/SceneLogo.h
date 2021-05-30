#ifndef __SCENELOGO_H__
#define __SCENELOGO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLogo : public Module
{
public:
	// Constructor
	SceneLogo(bool startEnabled);

	// Destructor
	~SceneLogo();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* logoTexture = nullptr;
	SDL_Texture* logo2Texture = nullptr;
	SDL_Texture* logo3Texture = nullptr;

	int sceneCount = 0;

};

#endif	// __SCENELOGO_H__