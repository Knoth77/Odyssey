#pragma once
#include "Bullet.h"
#include "src\sssf\game\Game.h"
class MageBullet :public Bullet
{
public:

	MageBullet();
	~MageBullet();

	void test();

	void handleCollision(Game *game);
	Bullet *clone(Game *game);
};

