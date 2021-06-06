#pragma once
#ifndef __MODULE_FLOWER_H__
#define __MODULE_FLOWER_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"

#define NUM_FLOWERS 100

struct SDL_Texture;

struct Flower {
	Collider* collider = nullptr;
	SDL_Texture* flowerT = nullptr;

	int x;
	int y;
	bool Destroyed = false;
	uint dCount = 0;
	bool dead = false;
};

class ModuleFlower : public Module
{
public:
	//Constructor
	ModuleFlower(bool startEnabled);

	//Destructor
	~ModuleFlower();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

public:

	iPoint position;


	SDL_Texture* TextureFlower = nullptr;

	Flower pasiveflower[NUM_FLOWERS] = { nullptr };

	Flower CreateFlower(int x, int y, SDL_Texture* t);

	Animation* currentAnimation[NUM_FLOWERS] = { nullptr };
	Animation idle;
	Animation dead;

};

#endif