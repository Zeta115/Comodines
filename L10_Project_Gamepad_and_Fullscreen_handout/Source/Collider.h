#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "Point.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		BOMB,
		FIRE,
		/*FIREUP1,
		FIREUP2,
		FIREDOWN1,
		FIREDOWN2,
		FIRERIGHT1,
		FIRERIGHT2,
		FIRELEFT1,
		FIRELEFT2,*/

		FLOWER,
		DEAD,
		MACHINE,
		POWERUP,
		BLUE_MACHINE,
		BLUE_MACHINE2,
		MAX
	};

	// Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;
	iPoint getPos();

	void AddListener(Module* listener);

	// Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

