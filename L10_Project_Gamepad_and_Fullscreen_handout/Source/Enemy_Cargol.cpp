#include "Enemy_Cargol.h"


#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"


Enemy_Cargol::Enemy_Cargol(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 3, 55, 22, 28 });

	// Up
	upAnim.PushBack({ 200, 52, 22, 32 });
	upAnim.PushBack({ 233, 53, 22, 31 });
	upAnim.PushBack({ 2, 93, 22, 30 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 2, 54, 22, 28 });
	downAnim.PushBack({ 35, 55, 22, 28 });
	downAnim.PushBack({ 68, 55, 23, 28 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;
	// Right 
	rightAnim.PushBack({ 165, 91, 27, 29 });
	rightAnim.PushBack({ 134, 92, 28, 28 });
	rightAnim.PushBack({ 99, 90, 26, 30 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;
	// Left
	leftAnim.PushBack({ 99, 53, 27, 29 });
	leftAnim.PushBack({ 129, 54, 28, 28 });
	leftAnim.PushBack({ 166, 52, 26, 30 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;

	

	collider = App->collisions->AddCollider({0, 0, 21, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Cargol::Update()
{
	if (down == true) {
		currentAnim = &downAnim;
		if (position.y >= 30) {
			position.y += speed;
			if (position.y == 215) {
				down = false;
				up = true;
			}
		}
	}

	if (up == true) {
		currentAnim = &upAnim;
		if (position.y < 300) {
			position.y -= speed;
			if (position.y == 50) {
				down = true;
				up = false;
			}
		}

	}
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
