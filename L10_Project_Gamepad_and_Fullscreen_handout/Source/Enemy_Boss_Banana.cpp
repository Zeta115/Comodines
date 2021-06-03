#include "Enemy_Boss_Banana.h"
#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Boss_Banana::Enemy_Boss_Banana(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 207, 283, 47,  66 });

	//273
	// Up
	upAnim.PushBack({ 4, 529, 45, 63 });
	upAnim.PushBack({ 56, 526, 43, 66 });
	upAnim.PushBack({ 107, 523, 43, 69 });
	upAnim.PushBack({ 158, 522, 43, 70 });
	upAnim.PushBack({ 208, 522, 45, 70 });
	upAnim.PushBack({ 259, 524, 45, 68 });
	upAnim.PushBack({ 310, 526, 45, 66 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Down
	downAnim.PushBack({ 256, 280, 43, 69 });
	downAnim.PushBack({ 156, 280, 47,  69 });
	downAnim.PushBack({ 311, 278, 43, 71 });
	downAnim.PushBack({ 362, 276, 43, 73 });
	downAnim.PushBack({ 5, 2, 316, 74 });
	downAnim.PushBack({ 54, 3, 320, 73 });
	downAnim.PushBack({ 105, 5, 320, 71 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Right
	rightAnim.PushBack({ 258, 448, 41, 63 });
	rightAnim.PushBack({ 309, 445, 41, 66 });
	rightAnim.PushBack({ 360, 446, 41, 68 });
	rightAnim.PushBack({ 3, 441, 41, 70 });
	rightAnim.PushBack({ 53, 440, 40, 71 });
	rightAnim.PushBack({ 104, 441, 40, 70 });
	rightAnim.PushBack({ 155, 443, 40, 68 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Left 
	leftAnim.PushBack({ 108, 365, 41, 63 });
	leftAnim.PushBack({ 57, 365, 41, 66});
	leftAnim.PushBack({ 6, 363, 41, 68 });
	leftAnim.PushBack({ 363, 358, 41, 70 });
	leftAnim.PushBack({ 314, 357, 40, 71 });
	leftAnim.PushBack({ 263, 358, 40, 70 });
	leftAnim.PushBack({ 212, 360, 40, 68 });
	leftAnim.loop = true;
	leftAnim.speed = 1.f;
	//DeathAnim
	Death.PushBack({ 17, 614, 47, 66 });
	Death.PushBack({ 96, 614, 47, 67 });
	Death.PushBack({ 171, 614, 56, 66 });
	Death.PushBack({ 250, 614, 56, 66 });
	Death.PushBack({ 333, 606, 48, 74 });
	Death.PushBack({ 408, 598, 55, 82 });
	Death.PushBack({ 95, 706, 47, 66 });
	Death.PushBack({ 175, 706, 47, 66 });
	Death.PushBack({ 254, 706, 47, 66 });
	Death.PushBack({ 329, 706, 56, 66 });
	Death.PushBack({ 400, 705, 72, 72 });
	Death.PushBack({ 3, 795, 76, 76 });
	Death.PushBack({ 92, 798, 59, 66 });
	Death.PushBack({ 169, 798, 60, 67 });
	Death.PushBack({ 250, 798, 56, 66 });
	Death.PushBack({ 329, 798, 56, 66 });
	Death.PushBack({ 408, 798, 56, 66 });
	Death.PushBack({ 12, 890, 57, 64 });
	Death.PushBack({ 96, 891, 48, 63 });
	Death.PushBack({ 171, 890, 57, 63 });
	Death.PushBack({ 248, 890, 60, 63 });

	path.PushBack({ 0.4f, 0.0f }, 40 * 6, &rightAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, 0.4f }, 40 * 2, &downAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ -0.4f, 0.0f }, 40 * 6, &leftAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, -0.4f }, 40 * 2, &upAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);

	collider = App->collisions->AddCollider({ 0, 0, 47, 66 }, Collider::Type::ENEMY, (Module*)App->enemies);
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
