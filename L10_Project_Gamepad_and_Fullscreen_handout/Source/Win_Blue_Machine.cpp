#include "Win_Blue_Machine.h"

#include "Application.h"
#include "ModuleCollisions.h"


Win_Blue_Machine::Win_Blue_Machine(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 240, 177, 15, 25 });	

	collider = App->collisions->AddCollider({ 0, 0, 15, 25 }, Collider::Type::PASIVEFLOWER, (Module*)App->enemies);
}

void Win_Blue_Machine::Update()
{
	currentAnim = &idleAnim;
	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
