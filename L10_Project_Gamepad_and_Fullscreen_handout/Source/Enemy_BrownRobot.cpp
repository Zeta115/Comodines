#include "Enemy_BrownRobot.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

Enemy_BrownRobot::Enemy_BrownRobot(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 110, 172, 23, 30 });

	// Up
	upAnim.PushBack({ 84, 174, 23, 28 });
	upAnim.PushBack({ 110, 172, 23, 30 });
	upAnim.PushBack({ 135, 174, 23, 28 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 84, 206, 23, 27 });
	downAnim.PushBack({ 134, 204, 23, 28 });
	downAnim.PushBack({ 109, 206, 23, 27 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;

	// Right
	rightAnim.PushBack({ 28, 179, 25, 25 });
	rightAnim.PushBack({ 2, 177, 24, 27 });
	rightAnim.PushBack({ 55, 179, 24, 25 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;

	// Left 
	leftAnim.PushBack({ 2, 208, 24, 25 });
	leftAnim.PushBack({ 55, 206, 24, 27 });
	leftAnim.PushBack({ 28, 208, 25, 25 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;

	//DeathAnim
	Death.PushBack({162, 172, 23, 30});

	path.PushBack({ 0.4f, 0.0f }, 40 * 6, &rightAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, 0.4f }, 40 * 2, &downAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ -0.4f, 0.0f }, 40 * 6, &leftAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, -0.4f }, 40 * 2, &upAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);

	collider = App->collisions->AddCollider({0, 0, 19, 19}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownRobot::Update()
{
	if (App->enemies->Dead)
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
