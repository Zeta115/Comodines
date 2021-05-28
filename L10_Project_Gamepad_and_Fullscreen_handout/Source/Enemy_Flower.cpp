#include "Enemy_Flower.h"

#include "Application.h"
#include "ModuleCollisions.h"


Enemy_Flower::Enemy_Flower(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 239, 237, 16, 16 });

	collider = App->collisions->AddCollider({ 0, 0, 16, 10 }, Collider::Type::PASIVEFLOWER, (Module*)App->enemies);
}

void Enemy_Flower::Update()
{
	currentAnim = &idleAnim;
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
