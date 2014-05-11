#pragma once
#include "Bullet.h"
#include "src\sssf\game\Game.h"
class LavaBall :public Bullet
{
public:

	LavaBall();
	~LavaBall();

	void handleCollision(Game *game);
	Bullet *clone(Game *game);
};

