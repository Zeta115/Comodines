#ifndef __ENEMY_CONILL_H__
#define __ENEMY_CONILL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Conill : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Conill(int x, int y);
	
	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	
	Path path;

	// The enemy animation
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation Death;
};

#endif // __ENEMY_REDBIRD_H__