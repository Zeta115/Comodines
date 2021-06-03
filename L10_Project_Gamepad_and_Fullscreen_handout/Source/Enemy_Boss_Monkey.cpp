#include "Enemy_Boss_Monkey.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Boss_Monkey::Enemy_Boss_Monkey(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 369, 0, 24, 19 });

	// Up
	upAnim.PushBack({ 317, 91, 19, 17 });
	upAnim.PushBack({ 366, 90, 19, 17 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 317, 46, 16, 18 });
	downAnim.PushBack({ 369, 46, 16, 18 });
	downAnim.PushBack({ 109, 206, 23, 27 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;

	// Right
	rightAnim.PushBack({ 315, 69, 21, 18 });
	rightAnim.PushBack({ 345, 68, 28, 19 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;

	// Left 
	rightAnim.PushBack({ 390, 69, 21, 18 });
	rightAnim.PushBack({ 368, 68, 19, 19 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;
	//DeathAnim
	Death.PushBack({ 162, 172, 23, 30 });

	path.PushBack({ 0.4f, 0.0f }, 40 * 6, &rightAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, 0.4f }, 40 * 2, &downAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ -0.4f, 0.0f }, 40 * 6, &leftAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, -0.4f }, 40 * 2, &upAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);

	collider = App->collisions->AddCollider({ 0, 0, 24, 19 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//type = TypeEnemy::BROWNROBOT;
}

void Enemy_Boss_Monkey::Update()
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
