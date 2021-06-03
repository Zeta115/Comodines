#include "Enemy_Boss_Banana.h"
#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Boss_Banana::Enemy_Boss_Banana(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 156, 7, 47,  69 });

	// Up
	upAnim.PushBack({ 4, 256, 45, 63 });
	upAnim.PushBack({ 56, 253, 43, 66 });
	upAnim.PushBack({ 107, 250, 43, 69 });
	upAnim.PushBack({ 158, 249, 43, 70 });
	upAnim.PushBack({ 208, 249, 45, 70 });
	upAnim.PushBack({ 259, 251, 45, 68 });
	upAnim.PushBack({ 310, 263, 45, 66 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Down
	downAnim.PushBack({ 256, 7, 43, 69 });
	downAnim.PushBack({ 156, 7, 47,  69 });
	downAnim.PushBack({ 311, 5, 43, 71 });
	downAnim.PushBack({ 362, 3, 43, 73 });
	downAnim.PushBack({ 5, 2, 43, 74 });
	downAnim.PushBack({ 54, 3, 47, 73 });
	downAnim.PushBack({ 105, 5, 47, 71 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Right
	rightAnim.PushBack({ 258, 175, 41, 63 });
	rightAnim.PushBack({ 309, 172, 41, 66 });
	rightAnim.PushBack({ 360, 170, 41, 68 });
	rightAnim.PushBack({ 3, 168, 41, 70 });
	rightAnim.PushBack({ 53, 167, 40, 71 });
	rightAnim.PushBack({ 104, 168, 40, 70 });
	rightAnim.PushBack({ 155, 170, 40, 68 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Left 
	leftAnim.PushBack({ 108, 92, 41, 63 });
	leftAnim.PushBack({ 57, 89, 41, 66});
	leftAnim.PushBack({ 6, 87, 41, 68 });
	leftAnim.PushBack({ 363, 85, 41, 70 });
	leftAnim.PushBack({ 314, 84, 40, 71 });
	leftAnim.PushBack({ 263, 85, 40, 70 });
	leftAnim.PushBack({ 212, 87, 40, 68 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;
	//DeathAnim
	Death.PushBack({ 17, 341, 47, 66 });
	Death.PushBack({ 96, 341, 47, 67 });
	Death.PushBack({ 171, 341, 56, 66 });
	Death.PushBack({ 250, 341, 56, 66 });
	Death.PushBack({ 333, 333, 48, 74 });
	Death.PushBack({ 408, 325, 55, 82 });
	Death.PushBack({ 95, 433, 47, 66 });
	Death.PushBack({ 175, 433, 47, 66 });
	Death.PushBack({ 254, 433, 47, 66 });
	Death.PushBack({ 329, 433, 56, 66 });
	Death.PushBack({ 400, 432, 72, 72 });
	Death.PushBack({ 3, 522, 76, 76 });
	Death.PushBack({ 92, 525, 59, 66 });
	Death.PushBack({ 169, 525, 60, 67 });
	Death.PushBack({ 250, 525, 56, 66 });
	Death.PushBack({ 329, 525, 56, 66 });
	Death.PushBack({ 408, 525, 56, 66 });
	Death.PushBack({ 12, 617, 57, 64 });
	Death.PushBack({ 96, 618, 48, 63 });
	Death.PushBack({ 171, 617, 57, 63 });
	Death.PushBack({ 248, 617, 60, 63 });

	/*path.PushBack({ 0.4f, 0.0f }, 40 * 6, &rightAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, 0.4f }, 40 * 2, &downAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ -0.4f, 0.0f }, 40 * 6, &leftAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, -0.4f }, 40 * 2, &upAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);*/

	collider = App->collisions->AddCollider({ 0, 0, 19, 19 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//type = TypeEnemy::BROWNROBOT;
}

void Enemy_Boss_Banana::Update()
{
	if (death)
	{
		currentAnim = &Death;
	}
	else {
		path.Update();
		position = spawnPos + path.GetRelativePosition();
		currentAnim = path.GetCurrentAnimation();
	}
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
