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
	detonateTime = 40;
}


MageBullet::~MageBullet()
{
}

void MageBullet::handleCollision(Game *game)
{
	initCollide = true;
	this->detonate(game);
	
}


void MageBullet::detonate(Game *game)
{
	float pixelScaling = game->getGSM()->getPhyiscs()->getPixelScaling();
	b2Vec2 bullPos = this->getBody()->GetPosition();
	Effect *darkEnergy = game->getGSM()->getSpriteManager()->getEffectRecycler()->retrieveEffect(game, L"DARKENERGY");
	darkEnergy->setDefaultX(((bullPos.x) / pixelScaling) - 50);
	darkEnergy->setDefaultY(((bullPos.y) / pixelScaling) - 50);
	game->getGSM()->getSpriteManager()->addEffect(darkEnergy);
	initCollide = true;
}

void MageBullet::reset()
{
	initCollide = false;
	detonateTime = 40;
}

void MageBullet::decDetonateTime()
{
	detonateTime--;

}


Bullet*	MageBullet::clone(Game *game)
{
	MageBullet *clone = new MageBullet();
	game->getGSM()->getPhyiscs()->initBullet(clone);
	clone->setSpriteType(this->getSpriteType());
	clone->setAlpha(255);
	clone->detonateTime = 40;
	return clone;
}
