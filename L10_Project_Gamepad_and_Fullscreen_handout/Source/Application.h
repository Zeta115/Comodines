#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "SceneLevel2.h"
#include "SceneLevelBoss.h"
#include "ModuleFlower.h"

#define NUM_MODULES 19

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneLogo;
class SceneIntro;
class SceneDeath;
class SceneLevel1;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleBomb;

class Application
{
public:

	// Constructor. Creates all necessary modules for the application
	Application();

	// Destructor. Removes all module objects
	~Application();

	// Initializes all modules
	bool Init();

	// Updates all modules (PreUpdate, Update and PostUpdate)
	UpdateResult Update();

	// Releases all the application data
	bool CleanUp();

public:

	// Array to store the pointers for the different modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;

	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneLogo* sceneLogo = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneDeath* sceneDeath = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel2* sceneLevel_2 = nullptr;
	SceneLevelBoss* sceneLevel_Boss = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleFlower* flowers = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleBomb* Placebomb = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__