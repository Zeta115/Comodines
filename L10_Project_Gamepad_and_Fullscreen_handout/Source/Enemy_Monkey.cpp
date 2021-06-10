#include "Enemy_Monkey.h"
#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Monkey::Enemy_Monkey(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 132, 138, 26, 27 });

	// Up
	upAnim.PushBack({ 132, 138, 26, 27 });
	upAnim.PushBack({ 165, 138, 26, 27 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 132, 138, 26, 27 });
	downAnim.PushBack({165, 138, 26, 27});
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Right
	rightAnim.PushBack({ 132, 138, 26, 27 });
	rightAnim.PushBack({165, 138, 26, 27});
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Left 
	leftAnim.PushBack({ 132, 138, 26, 27 });
	leftAnim.PushBack({ 165, 138, 26, 27 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;
	//DeathAnim
	Death.PushBack({ 198, 138, 26, 37 });
	Death.PushBack({ 233, 140, 22, 18 });

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

void Enemy_Monkey::Update()
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
