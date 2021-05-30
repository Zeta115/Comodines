#include "Enemy_Conill.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Conill::Enemy_Conill(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 15, 27, 2, 2 });

	// Up
	upAnim.PushBack({ 15, 26, 137, 2 });
	upAnim.PushBack({ 15, 27, 104, 2 });
	upAnim.PushBack({ 15, 26, 121, 2 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 15, 26, 19, 2 });
	downAnim.PushBack({ 15, 27, 2, 2 });
	downAnim.PushBack({ 15, 26, 36, 2 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;

	// Right
	rightAnim.PushBack({ 15, 26, 154, 2 });
	rightAnim.PushBack({ 15, 27, 171, 2 });
	rightAnim.PushBack({ 15, 26, 188, 2 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;

	// Left 
	leftAnim.PushBack({ 15, 26, 53, 2 });
	leftAnim.PushBack({ 15, 27, 71, 2 });
	leftAnim.PushBack({ 15, 26, 88, 2 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;



	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Conill::Update()
{
	if (right == true) {
		currentAnim = &rightAnim;
		if (position.x >= 20) {
			position.x += speed;
			if (position.x == 150) {
				right = false;
				left = true;
			}
		}
	}

	if (left == true) {
		currentAnim = &leftAnim;
		if (position.x < 300) {
			position.x -= speed;
			if (position.x == 53) {
				up = true;
				left = false;
			}
		}

	}
	if (up == true) {
		currentAnim = &downAnim;
		if (position.y < 270) {
			position.y -= speed;
			if (position.y == 50) {
				up = false;
				down = true;
			}
		}

	}
	if (down == true) {
		currentAnim = &upAnim;
		if (position.y >= 10) {
			position.y += speed;
			if (position.y == 215) {
				down = false;
				right = true;
			}
		}

	}
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
