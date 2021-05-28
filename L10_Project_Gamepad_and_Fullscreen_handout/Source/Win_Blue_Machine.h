#ifndef __WIN_BLUE_MACHINE_H__
#define __WIN_BLUE_MACHINE_H__

#include "Enemy.h"

class Win_Blue_Machine : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Win_Blue_Machine(int x, int y);
	Collider* collider = nullptr;

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;
	float speed = 0;

	// The enemy animation
	Animation idleAnim;
};

#endif // __WIN_BLUE_MACHINE_H__