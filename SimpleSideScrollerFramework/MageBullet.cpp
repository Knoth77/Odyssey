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

	float pixelScaling = game->getGSM()->getPhyiscs()->getPixelScaling();
	b2Vec2 bullPos = this->getBody()->GetPosition();
	Effect *explosionSprite = game->getGSM()->getSpriteManager()->getEffectRecycler()->retrieveEffect(game, L"EXPLOSION");
	explosionSprite->setDefaultX(((bullPos.x) / pixelScaling) - 20);
	explosionSprite->setDefaultY(((bullPos.y) / pixelScaling) - 20);
	game->getGSM()->getSpriteManager()->addEffect(explosionSprite);
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
