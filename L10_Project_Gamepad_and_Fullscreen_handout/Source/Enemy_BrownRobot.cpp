#include "Enemy_BrownRobot.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BrownRobot::Enemy_BrownRobot(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 110, 172, 23, 30 });

	// Up
	upAnim.PushBack({ 84, 204, 23, 27 });
	upAnim.PushBack({ 109, 206, 23, 27 });
	upAnim.PushBack({ 134, 206, 23, 28 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 84, 174, 23, 28 });
	downAnim.PushBack({ 135, 174, 23, 28 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;

	// Right
	rightAnim.PushBack({ 2, 177, 24, 27 });
	rightAnim.PushBack({ 28, 179, 25, 25 });
	rightAnim.PushBack({ 55, 179, 24, 25 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;

	// Left 
	leftAnim.PushBack({ 2, 208, 24, 27 });
	leftAnim.PushBack({ 28, 208, 25, 25 });
	leftAnim.PushBack({ 55, 206, 24, 27 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;

	

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownRobot::Update()
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
	//collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
