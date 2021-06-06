#include "Enemy_Conill.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

Enemy_Conill::Enemy_Conill(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 2, 2, 15, 27 });

	// Up
	upAnim.PushBack({ 121, 2, 15, 26 });
	upAnim.PushBack({ 104, 2, 15, 27 });
	upAnim.PushBack({ 137, 2, 15, 26 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 19, 2, 15, 26 });
	downAnim.PushBack({ 2, 2, 15, 27 });
	downAnim.PushBack({ 36, 2, 15, 26 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;

	// Right
	rightAnim.PushBack({ 154, 2, 15, 26 });
	rightAnim.PushBack({ 171, 2, 15, 27 });
	rightAnim.PushBack({ 188, 2, 15, 26 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;

	// Left 
	leftAnim.PushBack({ 53, 2, 15, 26 });
	leftAnim.PushBack({ 71, 2, 15, 27 });
	leftAnim.PushBack({ 88, 2, 15, 26 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;

	Death.PushBack({ 2, 33, 15, 26 });
	Death.PushBack({ 19, 33, 15, 28 });
	Death.PushBack({ 36, 39, 15, 9 });
	Death.PushBack({ 71, 46, 15, 9 });
	Death.PushBack({ 90, 45, 11, 7 });
	Death.PushBack({ 90, 45, 11, 7 });
	Death.PushBack({ 109, 45, 7, 7 });
	Death.PushBack({ 123, 49, 13, 7 });
	Death.loop = true;
	Death.speed = true;

	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ -0.4f, 0.0f }, 20 * 2, &leftAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, 0.4f }, 60 * 2, &downAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.0f, -0.4f }, 60 * 2, &upAnim);
	path.PushBack({ 0.0f, 0.0f }, 40 * 2, &idleAnim);
	path.PushBack({ 0.4f, 0.0f }, 20 * 2, &rightAnim);

	collider = App->collisions->AddCollider({ 0, 0, 16, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Conill::Update()
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

	collider->SetPos(position.x, position.y + 20);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
