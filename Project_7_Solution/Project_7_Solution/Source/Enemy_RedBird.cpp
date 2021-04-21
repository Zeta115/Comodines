#include "Enemy_RedBird.h"


#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	enemyAnim.PushBack({2,177,24,27});
	enemyAnim.PushBack({28, 179, 25, 25});
	enemyAnim.PushBack({55, 179, 24, 25});
	enemyAnim.speed = 0.02f;

	currentAnim = &enemyAnim;

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
