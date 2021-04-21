#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_RedBird : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_RedBird(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	bool right = false;
	bool left = true;
	float speed = 1;
	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	

	// The enemy animation
	Animation enemyAnim;
};

#endif // __ENEMY_REDBIRD_H__