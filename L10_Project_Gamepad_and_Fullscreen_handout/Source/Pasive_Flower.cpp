#include "Pasive_Flower.h"

#include "Application.h"
#include "ModuleCollisions.h"


Pasive_Flower::Pasive_Flower(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 222, 237, 16, 16 });

	collider = App->collisions->AddCollider({ 0, 0, 14, 14 }, Collider::Type::FLOWER, (Module*)App->enemies);
}

void Pasive_Flower::Update()
{
	currentAnim = &idleAnim;
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}