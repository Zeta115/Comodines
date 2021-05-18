#include "Bomb.h"

#include "Application.h"
#include "ModuleCollisions.h"

Bomb::Bomb(int x, int y) : Enemy(x, y)
{
	
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Bomb::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
