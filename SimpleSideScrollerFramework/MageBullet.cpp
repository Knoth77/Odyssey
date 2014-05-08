#include "MageBullet.h"
#include "src\sssf\gsm\state\GameStateManager.h"

MageBullet::MageBullet()
{
	speed = 0;
	initCollide = false;
	type = L"MAGE_BULLET";
	primaryDamage = 70;
	//this->setSecondaryDamage(50);
	//cooldown = 50;
}


MageBullet::~MageBullet()
{
}

void MageBullet::handleCollision(Game *game)
{
	initCollide = true;
}


void MageBullet::test()
{}

Bullet*	MageBullet::clone(Game *game)
{
	MageBullet *clone = new MageBullet();
	game->getGSM()->getPhyiscs()->initBullet(clone);
	clone->setSpriteType(this->getSpriteType());
	clone->setAlpha(255);
	return clone;
}
