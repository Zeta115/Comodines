#include "Modulecargol.h"


#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"


Enemy_Cargol::Enemy_Cargol(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 3, 55, 27, 29 });

	// Up
	upAnim.PushBack({ 201, 53, 22, 32 });
	upAnim.PushBack({ 234, 53, 22, 31 });
	upAnim.PushBack({ 3, 94, 22, 30 });
	upAnim.loop = true;
	upAnim.speed = 0.03f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 3, 55, 22, 28 });
	downAnim.PushBack({ 36, 56, 22, 28 });
	downAnim.PushBack({ 69, 56, 23, 28 });
	downAnim.loop = true;
	downAnim.speed = 0.03f;
	// Right 
	rightAnim.PushBack({ 100, 54, 27, 38 });
	rightAnim.PushBack({ 131, 55, 28, 39 });
	rightAnim.PushBack({ 163, 53, 26, 31 });
	rightAnim.loop = true;
	rightAnim.speed = 0.03f;
	// Left
	leftAnim.PushBack({ 166, 93, 27, 30 });
	leftAnim.PushBack({ 135, 94, 28, 29 });
	leftAnim.PushBack({ 101, 92, 26, 31 });
	leftAnim.loop = true;
	leftAnim.speed = 0.03f;

	

	currentAnim = &rightAnim;

	//collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Cargol::Update()
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
