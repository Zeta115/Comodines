#include "Enemy_RedBird.h"


#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"


Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 110, 172, 23, 30 });

	// Up
	upAnim.PushBack({ 84, 204, 23, 27 });
	upAnim.PushBack({ 109, 206, 23, 27 });
	upAnim.PushBack({ 134, 206, 23, 28 });
	upAnim.loop = true;
	upAnim.speed = 0.03f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 84, 174, 23, 28 });
	downAnim.PushBack({ 135, 174, 23, 28 });	
	downAnim.loop = true;
	downAnim.speed = 0.03f;

	// Right
	rightAnim.PushBack({ 2, 177, 24, 27 });
	rightAnim.PushBack({ 28, 179, 25, 25 });
	rightAnim.PushBack({ 55, 179, 24, 25 });
	rightAnim.loop = true;
	rightAnim.speed = 0.03f;

	// Left 
	leftAnim.PushBack({ 2, 206, 24, 27});
	leftAnim.PushBack({ 28, 208, 25, 25});
	leftAnim.PushBack({ 55, 208, 24, 27});
	leftAnim.loop = true;
	leftAnim.speed = 0.03f;

	currentAnim = &rightAnim;

	//collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{
	if (right == true) {
		if (position.x >= 30) {
			position.x += speed;
			if (position.x == 200) {
				right = false;
				left = true;
			}
		}
	}

	if (left == true) {
		if (position.x < 300) {
			position.x -= speed;
			if (position.x == 30) {
				right = true;
				left = false;
			}
		}

	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
