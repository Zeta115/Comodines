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
#include "ModuleEnemies.h"

#include <stdio.h>
#include <iostream>
#include <SDL/include/SDL_gamecontroller.h>

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

	// Dead
	deadAnim.PushBack({ 2, 51, 15, 20 });
	deadAnim.PushBack({ 19, 51, 13, 19 });
	deadAnim.PushBack({ 33, 51, 19, 20 });
	deadAnim.PushBack({ 51, 51, 21, 19 });
	deadAnim.PushBack({ 71, 51, 21, 19 });
	deadAnim.PushBack({ 93, 50, 22, 21 });
	deadAnim.loop = false;
	deadAnim.speed = 0.05f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	currentAnimation = &idleAnim;

	player = App->textures->Load("Assets/bomberman/Bomberman.png");
	placeFx = App->audio->LoadFx("Assets/Audio/Fx/bomb_plant.wav");
	blastFx = App->audio->LoadFx("Assets/Audio/Fx/bomb_blast.wav");
	deadFx = App->audio->LoadFx("Assets/Audio/Fx/dead.wav");
	winFx = App->audio->LoadFx("Assets/Audio/Fx/stage_clear.wav");
	powerUpText = App->textures->Load("Assets/SpecialElements/Powerups.png");




	position.x = 25;
	position.y = 64;

	// L10: DONE 4: Retrieve the player when playing a second time
	destroyed = false;
	win = false;

	// L6: DONE 3: Add a collider to the player
	collider = App->collisions->AddCollider({ (int)position.x, (int)position.y + 7, 15, 15 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	score = 0;
	lifes = 3;
	return ret;
}

UpdateResult ModulePlayer::Update()
{

	prevposition = position;
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

	if ((App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT) || (pad.left))
	{
		position.x -= speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if ((App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT) || (pad.right))
	{
		position.x += speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if ((App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) || (pad.down))
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if ((App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT) || (pad.up))
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
		if (App->particles->bom.isAlive == true)
		{
		App->particles->AddParticle(App->particles->bom, position.x, position.y + 6, Collider::Type::BOMB);
		App->audio->PlayFx(placeFx);
		}
		
		else if (App->particles->bom.isAlive == false)
		{
			//center
			App->particles->AddParticle(App->particles->explosion, position.x, position.y + 6, Collider::Type::FIRE);
			//up
			App->particles->AddParticle(App->particles->explosion_up_2, position.x, position.y + -10, Collider::Type::FIRE);
			App->particles->AddParticle(App->particles->explosion_up_1, position.x, position.y + -26, Collider::Type::FIRE);
			//down
			App->particles->AddParticle(App->particles->explosion_down_2, position.x, position.y + 21, Collider::Type::FIRE);
			App->particles->AddParticle(App->particles->explosion_down_1, position.x, position.y + 37, Collider::Type::FIRE);
			//right
			App->particles->AddParticle(App->particles->explosion_right_2, position.x + 15, position.y, Collider::Type::FIRE);
			App->particles->AddParticle(App->particles->explosion_right_1, position.x + 31, position.y , Collider::Type::FIRE);
			//left
			App->particles->AddParticle(App->particles->explosion_left_2, position.x + -16, position.y, Collider::Type::FIRE);
			App->particles->AddParticle(App->particles->explosion_left_1, position.x + -32, position.y, Collider::Type::FIRE);
			App->audio->PlayFx(blastFx);
			//App->input->ShakeController(0, 60, 1.0f);
		}
		score += 1000;
	}


	//Debbug Keys
	
	//godmode
	if (App->input->keys[SDL_SCANCODE_F1] == KeyState::KEY_DOWN) {
		godmode = !godmode;
	}

	// Switch gamepad debug info && show colliders
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debugGamepadInfo = !debugGamepadInfo;

	//insta win
	if (App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_REPEAT)
	{
		App->audio->PlayFx(winFx);
		win = true;
	}

	//insta lose
	if (App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_DOWN)
	{
		lifes = 0;
		App->audio->PlayFx(deadFx);
	}

	//reset position
	if (App->input->keys[SDL_SCANCODE_F5] == KeyState::KEY_DOWN)
	{
		position.x = 25;
		position.y = 64;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KeyState::KEY_DOWN) {
		return UpdateResult::UPDATE_STOP;
	}
	
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE) {
		if (lifes>0)
		{
			currentAnimation = &idleAnim;
		}
		
	}	
	
	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y + 7);

	currentAnimation->Update();

	// Update shot countdown
	if (shotCountdown > 0) --shotCountdown;

	if (powerTouch == true){
		if (timer < 150) {
			timer++;
		}
		if (timer == 150) {
			powerTouch = false;
			timer = 0;
		}
	}
	
	if (lifes == 0)
	{

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 360);
		currentAnimation = &deadAnim;
		destroyed = true;
	}
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{

	if (!destroyed||!win)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(player, position.x, position.y, &rect);
	}
	if (win == true)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 360);
	}
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->DrawText(140, 31, scoreFont, scoreText);
	sprintf_s(scoreText, 10, "%7d", lifes);
	App->fonts->DrawText(185, 31, scoreFont, scoreText);

	if (debugGamepadInfo == true) DebugDrawGamepadInfo();
	else App->fonts->DrawText(5, 10, scoreFont, "press f2 to display gamepad debug info");
	if (powerActive == true)
	{
		App->render->DrawTexture(powerUpText, 88, 78, NULL);
	}

	return UpdateResult::UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{	
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == collider) && (destroyed == false))
	{

		if (godmode == false)
		{

			if (c1 == collider && destroyed == false) {
				switch (c2->type) {
				case Collider::Type::WALL:
					if (c1->rect.y < c2->rect.y) // up
					{
						position.y -= speed;
					}
					else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
					{
						position.y += speed;
					}
					if (c1->rect.x < c2->rect.x) // left
					{
						position.x -= speed;
					}
					else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
					{
						position.x += speed;
					}; break;
				case Collider::Type::FLOWER:
						if (c1->rect.y < c2->rect.y) // up
						{
							position.y -= speed;
						}
						else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
						{
							position.y += speed;
						}
						if (c1->rect.x < c2->rect.x) // left
						{
							position.x -= speed;
						}
						else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
						{
							position.x += speed;
						}; break;
				}
				if (c1->type == Collider::Type::PLAYER != c2->type == Collider::Type::POWERUP)
				{
					powerActive = false;
				}


				//player and enemies
				if (c1 == collider && destroyed == false && (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY))
				{
					if (powerTouch == false) {
						if (timer <= 35)timer++;

						if (timer == 35)
						{
							lifes -= 1;
							timer = 0;
						}
						if (App->particles->dead.isAlive == false && lifes == 0)
						{
							App->audio->PlayFx(deadFx);
						}
					}
				}
			}
			if (c1->type == Collider::Type::BOMB && c2->type == Collider::Type::ENEMY)
			{
				score += 23;
			}
			if (c1->type == Collider::Type::FIRE && c2->type == Collider::Type::ENEMY)
			{
				score += 23;
			}
		}
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::MACHINE)
		{
			App->audio->PlayFx(winFx);
			win = true;
		}
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::POWERUP) {
			powerActive = false;
			powerTouch = true;

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