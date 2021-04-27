#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
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
	

	position.x = 121;
	position.y = 125;

	collider = App->collisions->AddCollider({ position.x, position.y, 15, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.x += 0;

	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->bom, position.x, position.y+6, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(placeFx);
		if (App->particles->bom.isAlive == false)
		{
			App->audio->PlayFx(blastFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}
	
		
		// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)

	currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{

		destroyedCountdown--;
		if (destroyedCountdown <= 0)
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(player, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN) {

	}
		if (c1 == collider && destroyed == false)
		{
			App->particles->AddParticle(App->particles->dead, position.x, position.y, Collider::Type::DEAD, 9);
			if (App->particles->dead.isAlive == false)
			{
				App->audio->PlayFx(deadFx);
			}

			destroyed = true;
		}
	
}