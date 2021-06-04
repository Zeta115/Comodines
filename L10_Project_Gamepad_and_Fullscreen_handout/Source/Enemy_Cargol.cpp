#include "Enemy_Cargol.h"


#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include <iostream>
using namespace std;

Enemy_Cargol::~Enemy_Cargol()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

Enemy_Cargol::Enemy_Cargol(int x, int y) : Enemy(x, y)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 3, 55, 22, 28 });

	// Up
	upAnim.PushBack({ 200, 66, 22, 32 });
	upAnim.PushBack({ 233, 67, 22, 31 });
	upAnim.PushBack({ 2, 107, 22, 30 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Down
	//downAnim.PushBack({ 110, 172, 23, 30 });
	downAnim.PushBack({ 2, 68, 22, 28 });
	downAnim.PushBack({ 35, 69, 22, 28 });
	downAnim.PushBack({ 68, 69, 22, 28 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;
	// Right 
	rightAnim.PushBack({ 100, 105, 26, 30 });
	rightAnim.PushBack({ 135, 107, 28, 28 });
	rightAnim.PushBack({ 166, 106, 27, 39 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;
	// Left
	leftAnim.PushBack({ 99, 67, 27, 29 });
	leftAnim.PushBack({ 129, 68, 28, 28 });
	leftAnim.PushBack({ 166, 66, 26, 30 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;

	

	collider = App->collisions->AddCollider({ 0, 0, 21, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Cargol::OnCollision(Collider* c1, Collider* c2)
{

	cout << "c1 es:" << c1 << " || c2 es:" << c2;

	if ((c1 == collider) && (destroyed == false))
	{

			if (c1 == collider && destroyed == false) {
				switch (c2->type) {
				case Collider::Type::WALL:
					cout << "SNAIL HITS WALL";
					if (c1->rect.y < c2->rect.y) // up
					{
						position.y -= speed;
					}
					else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
					{
						position.y += speed;
					}
					if (c1->rect.x < c2->rect.x) // left
					{
						position.x -= speed;
					}
					else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
					{
						position.x += speed;
					}; break;

				case Collider::Type::FLOWER:
					cout << "SNAIL HITS FLOWER";
					if (c1->rect.y < c2->rect.y) // up
					{
						position.y -= speed;
					}
					else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
					{
						position.y += speed;
					}
					if (c1->rect.x < c2->rect.x) // left
					{
						position.x -= speed;
					}
					else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
					{
						position.x += speed;
					}; break;

				case Collider::Type::ENEMY:
					cout << "SNAIL HITS ANOTHER ENEMY";
					if (c1->rect.y < c2->rect.y) // up
					{
						position.y -= speed;
					}
					else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
					{
						position.y += speed;
					}
					if (c1->rect.x < c2->rect.x) // left
					{
						position.x -= speed;
					}
					else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
					{
						position.x += speed;
					}; break;

				case Collider::Type::PLAYER:
					cout << "SNAIL HITS PLAYER";

					death = true;
					SetToDelete();

					if (c1->rect.y < c2->rect.y) // up
					{
						position.y = position.y;
					}
					else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
					{
						position.y = position.y;
					}
					if (c1->rect.x < c2->rect.x) // left
					{
						position.x = position.x;
					}
					else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
					{
						position.x += position.x;
					}; break;
				}

			/*	if (c1->type == Collider::Type::PLAYER != c2->type == Collider::Type::POWERUP)
				{
					powerActive = false;
				}*/


				//player and enemies
				if (c1 == collider && destroyed == false && (c1->type == Collider::Type::ENEMY && c2->type == Collider::Type::PLAYER))
				{
					death = true;
					SetToDelete();
					cout << "SNAIL HITS PLAYER v2";

				}
			}

		/*if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::MACHINE)
		{
			App->audio->PlayFx(winFx);
			win = true;
		}
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::POWERUP) {
			powerActive = false;
			powerTouch = true;

		}*/
	}
}

void Enemy_Cargol::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;

}

void Enemy_Cargol::Update()
{

	if (death == true)
	{
		destroyed = true;
		death = false;
		cout << "Cargol eliminat";
	}

	if (down == true) {
		currentAnim = &downAnim;
		if (position.y >= 30) {
			position.y += speed;
			if (position.y == 215) {
				down = false;
				up = true;
			}
		}
	}

	if (up == true) {
		currentAnim = &upAnim;
		if (position.y < 300) {
			position.y -= speed;
			if (position.y == 50) {
				down = true;
				up = false;
			}
		}

	}

	collider->SetPos(position.x, position.y);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position


	Enemy::Update();
}
