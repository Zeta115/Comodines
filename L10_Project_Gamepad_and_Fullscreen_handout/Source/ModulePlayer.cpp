#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 18, 2, 15, 22 });

	// move upwards
	upAnim.PushBack({ 50, 2, 15, 22 });
	upAnim.PushBack({ 65, 2, 15, 22 });
	upAnim.PushBack({ 82, 2, 15, 22 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 2, 2, 15, 22 });
	downAnim.PushBack({ 18, 2, 15, 22 });
	downAnim.PushBack({ 33, 2, 15, 22 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({ 49, 26, 15, 22 });
	leftAnim.PushBack({ 67, 26, 15, 22 });
	leftAnim.PushBack({ 82, 26, 15, 22 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	// Move right
	rightAnim.PushBack({ 2, 26, 15, 22 });
	rightAnim.PushBack({ 17, 26, 15, 22 });
	rightAnim.PushBack({ 33, 26, 15, 22 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	player = App->textures->Load("Assets/bomberman/Bomberman.png");
	currentAnimation = &idleAnim;
	placeFx = App->audio->LoadFx("Assets/Audio/Fx/bomb_plant.wav");
	blastFx = App->audio->LoadFx("Assets/Audio/Fx/bomb_blast.wav");
	deadFx = App->audio->LoadFx("Assets/Audio/Fx/dead.wav");


	position.x = 25;
	position.y = 64;

	// L10: DONE 4: Retrieve the player when playing a second time
	destroyed = false;

	// L6: DONE 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 15, 16 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

UpdateResult ModulePlayer::Update()
{
	// Get gamepad info
	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll
	App->player->position.x += 0;

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 12, 0.33f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 36, 0.66f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}

	// L10: TODO: Implement gamepad support

	if (App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->bom, position.x, position.y + 6, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(placeFx);
		if (App->particles->bom.isAlive == false)
		{
			App->audio->PlayFx(blastFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KeyState::KEY_DOWN) {
		return UpdateResult::UPDATE_STOP;
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_DOWN) destroyed =! destroyed;
	if (App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_DOWN) win = !win;
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE)
		currentAnimation = &idleAnim;
	collider->SetPos(position.x, position.y);
	// Switch gamepad debug info
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debugGamepadInfo = !debugGamepadInfo;

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	// Update shot countdown
	if (shotCountdown > 0) --shotCountdown;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(player, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->DrawText(58, 248, scoreFont, scoreText);

	if (debugGamepadInfo == true) DebugDrawGamepadInfo();
	else App->fonts->DrawText(5, 10, scoreFont, "press f2 to display gamepad debug info");

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if (App->input->keys[SDL_SCANCODE_F1] == KeyState::KEY_DOWN) {
		godmode != godmode;
	}
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == collider) && (destroyed == false)&&godmode==false)
	{
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
		{
			speed = 0;
		}
		if (c1 == collider && destroyed == false && (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY))
		{			
				// L10: DONE 3: Go back to the intro scene when the player gets killed
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 360);
			App->particles->AddParticle(App->particles->dead, position.x, position.y, Collider::Type::DEAD, 9);
			if (App->particles->dead.isAlive == false)
			{
				App->audio->PlayFx(deadFx);
			}
			destroyed = true;
			
		}
		

		if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
		{
			score += 23;
		}
	}
}
void ModulePlayer::DebugDrawGamepadInfo()
{
	GamePad& pad = App->input->pads[0];

	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
	App->fonts->DrawText(5, 10, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
		(pad.a) ? "a" : "",
		(pad.b) ? "b" : "",
		(pad.x) ? "x" : "",
		(pad.y) ? "y" : "",
		(pad.start) ? "start" : "",
		(pad.back) ? "back" : "",
		(pad.guide) ? "guide" : "",
		(pad.l1) ? "lb" : "",
		(pad.r1) ? "rb" : "",
		(pad.l3) ? "l3" : "",
		(pad.r3) ? "r3" : ""
	);
	App->fonts->DrawText(5, 20, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
		(pad.up) ? "up" : "",
		(pad.down) ? "down" : "",
		(pad.left) ? "left" : "",
		(pad.right) ? "right" : ""
	);
	App->fonts->DrawText(5, 30, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
	App->fonts->DrawText(5, 40, scoreFont, scoreText);
	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
	App->fonts->DrawText(5, 50, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.left_x, pad.left_y);
	App->fonts->DrawText(5, 60, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.left_dz);
	App->fonts->DrawText(5, 70, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.right_x, pad.right_y);
	App->fonts->DrawText(5, 80, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.right_dz);
	App->fonts->DrawText(5, 90, scoreFont, scoreText);
}