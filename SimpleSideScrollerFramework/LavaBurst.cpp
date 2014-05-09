#include "LavaBurst.h"
#include "src\sssf\gsm\state\GameStateManager.h"

LavaBurst::LavaBurst()
{
	speed = 10;
	initCollide = false;
	type = L"LAVA_BURST";
	primaryDamage = 10;
	//secondaryDamage = 30;
}


LavaBurst::~LavaBurst()
{
}

void LavaBurst::handleCollision(Game *game)
{
	initCollide = true;
}




Bullet*	LavaBurst::clone(Game *game)
{
	LavaBurst *clone = new LavaBurst();
	game->getGSM()->getPhyiscs()->initBullet(clone);
	clone->setSpriteType(this->getSpriteType());
	clone->setAlpha(255);
	return clone;
}
