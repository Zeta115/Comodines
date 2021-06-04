#ifndef __ENEMY_CARGOL_H__
#define __ENEMY_CARGOL_H__

#include "Enemy.h"
#include "path.h"

class Enemy_Cargol : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Cargol(int x, int y);

	//destructor
	~Enemy_Cargol();

	void OnCollision(Collider* c1, Collider* c2);
	Collider* collider = nullptr;

	// The enemy is going to perform a sinusoidal movement
	void Update() override;
	void SetToDelete();
	

private:
	// The position (as ratio) in the wave at a specific moment
	// The speed at which the wave ratio is increased
	bool up = false;
	bool down = true;
	float speed = 0.25f;

	bool destroyed = false;
	bool pendingToDelete = false;
	bool death = false;
	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave

	Path path;

	// The enemy animation
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
};

#endif // __ENEMY_REDB