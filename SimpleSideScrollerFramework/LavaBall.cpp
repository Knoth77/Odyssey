#include "LavaBall.h"
#include "src\sssf\gsm\state\GameStateManager.h"

LavaBall::LavaBall()
{
	speed = 10;
	initCollide = false;
	type = L"LAVA_BALL";
	primaryDamage = 10;
	//secondaryDamage = 30;
	//cooldown = 30;
}


LavaBall::~LavaBall()
{
}

void LavaBall::handleCollision(Game *game)
{
	initCollide = true;
}



Bullet*	LavaBall::clone(Game *game)
{
	LavaBall *clone = new LavaBall();
	game->getGSM()->getPhyiscs()->initLavaBullet(clone);
	clone->setSpriteType(this->getSpriteType());
	clone->setAlpha(255);
	return clone;
}
