#include "Andromalius.h"
#include "Fireball.h"
#include "MageBullet.h"
#include "Lightning.h"
#include <cmath>
#include <math.h>


Andromalius::Andromalius()
{
	movementPattern = new SimpleMovement(this->body, SimpleMovement::SQUARE);
	bossHealth = 500;
	selectedGun = gunSelection::FIREBALL;
	fireCooldown = 30;
	bulletCooldown = 50;
	type = L"MAGE_BOSS";
	bulletFire = -1;
	pivot = false;
	fired = false;
	dashCooldown = 15;
	srand(time(NULL));
	orbsActive = false;
	lightningCooldown = 3;
	lightningAngle = 0.0f;
}



Andromalius::~Andromalius()
{
	for (int i = 0; i < 4; i++)
	{
		if (orbs[i] != NULL)
		{

			game->getGSM()->getPhyiscs()->getGameWorld()->DestroyBody(orbs[i]->getBody());
			delete orbs[i];
			orbs[i] = NULL;
		}
	}
}

void Andromalius::changeAnimationState()
{

}


void Andromalius::think(Game *game)
{
	int pX = this->getBody()->GetPosition().x;
	int pY = this->getBody()->GetPosition().y;
	
	if (dashCooldown <= 0)
	{
		this->dash(game);
	}

	if (this->getCurrentState() == L"IDLE" || this->getCurrentState() == L"IDLE_RIGHT")
	{
		if (this->getMarkedForDeath() == true)
		{
			this->setCurrentState(L"CHILLIN");
			this->setMarkedForDeath(false);
			this->setHealth(500);
		}
		else
		{
			if (this->isPlayerInRadius() || this->wasJustShot())
			{

				if (this->getFireCooldown() <= 0)
				{
					this->setSelectedGun(FIREBALL);
					Bullet *bullet = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"FIREBALL");
					bullet->setDamageType('P');
					bullet->setCurrentState(L"PRIMARY_FIRE");
					game->getGSM()->getPhyiscs()->activateEnemyBullet(bullet, this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);
					game->getGSM()->getSpriteManager()->addActiveBullet(bullet);
					this->setFireCooldown(5);
				}
				else
				{
					this->decFireCooldown();
				}

				b2Vec2 vel = this->body->GetLinearVelocity();
				if (vel.x < 0)
					this->setCurrentState(L"IDLE");
				else
					this->setCurrentState(L"IDLE_RIGHT");
			}
			else
			{
				changeAnimationState();
			}
		}
	}
	else if (this->getCurrentState() == L"PHASE_TWO_IDLE")
	{
		if (this->getMarkedForDeath() == true)
		{
			this->setCurrentState(L"PHASE_THREE_IDLE");
			this->setMarkedForDeath(false);
			this->setHealth(500);
		}
		else
		{
			if (this->isPlayerInRadius() || this->wasJustShot())
			{

				if (this->getBulletCooldown() <= 0)
				{
					this->setSelectedGun(MAGE_BULLET);
					Bullet *b = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"MAGE_BULLET");
					MageBullet *mageBullet = dynamic_cast<MageBullet*>(b);
					mageBullet->reset();
					mageBullet->setDamageType('P');
					mageBullet->setCurrentState(L"PRIMARY_FIRE");

					Bullet *b1 = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"MAGE_BULLET");
					MageBullet *mageBullet1 = dynamic_cast<MageBullet*>(b1);
					mageBullet1->reset();
					mageBullet1->setDamageType('P');
					mageBullet1->setCurrentState(L"PRIMARY_FIRE");

					Bullet *b2 = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"MAGE_BULLET");
					MageBullet *mageBullet2 = dynamic_cast<MageBullet*>(b2);
					mageBullet2->reset();
					mageBullet2->setDamageType('P');
					mageBullet2->setCurrentState(L"PRIMARY_FIRE");

					game->getGSM()->getPhyiscs()->activateEnemyBullet(mageBullet, 0, -50);
					game->getGSM()->getPhyiscs()->activateEnemyBullet(mageBullet1, -30, 30);
					game->getGSM()->getPhyiscs()->activateEnemyBullet(mageBullet2, 30, -30);
					game->getGSM()->getSpriteManager()->addActiveBullet(mageBullet);
					game->getGSM()->getSpriteManager()->addActiveBullet(mageBullet1);
					game->getGSM()->getSpriteManager()->addActiveBullet(mageBullet2);
					this->setBulletCooldown(40);
					bulletFire = 10;
					fired = true;
				}
				else
				{
					this->decBulletCooldown();
				}

				if (this->getFireCooldown() <= 0)
				{
					this->setSelectedGun(FIREBALL);
					Bullet *fireBall = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"FIREBALL");
					fireBall->setDamageType('P');
					fireBall->setCurrentState(L"PRIMARY_FIRE");
					game->getGSM()->getPhyiscs()->activateEnemyBullet(fireBall, this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);
					game->getGSM()->getSpriteManager()->addActiveBullet(fireBall);
					this->setFireCooldown(5);
				}
				else
				{
					this->decFireCooldown();
				}

				b2Vec2 vel = this->body->GetLinearVelocity();
				if (vel.x < 0)
					this->setCurrentState(L"PHASE_TWO_IDLE");
				else
					this->setCurrentState(L"PHASE_TWO_IDLE");
			}
			else
			{
				changeAnimationState();
			}

		}
	}

}

void Andromalius::dash(Game *game)
{
	b2Body *botBody = this->getBody();
	b2Vec2 finalPos;
	bool validX = false;
	bool validY = false;
	while (!validX || !validY)
	{
		int r = (rand() % (2 - 0 + 1));
		int r2 = (rand() % (2 - 0 + 1));
		int dX = 1;
		int dY = 1;
		if (r < 1)
			dX = -1;
		else
			dX = 1;
		if (r2 < 1)
			dY = -1;
		else
			dY = 1;
		int maxV = rangeY;
		int maxH = rangeX;
		int distV = ((rand() % (maxV - 1))) + 1;
		int distH = ((rand() % (maxH - 1))) + 1;
		distV *= dY;
		distH *= dX;
		float xLowerBound = this->initPos.x - rangeX;
		float xUpperBound = this->initPos.x + rangeX;
		float yLowerBound = this->initPos.y - rangeY;
		float yUpperBound = this->initPos.y + rangeY;
		float curPosX = botBody->GetPosition().x;
		float curPosY = botBody->GetPosition().y;
		float testPosX = curPosX + distH;
		float testPosY = curPosY + distV;
		if (testPosX < xUpperBound && testPosX > xLowerBound)
			validX = true;
		if (testPosY < yUpperBound && testPosY > yLowerBound)
			validY = true;
		finalPos.x = testPosX;
		finalPos.y = testPosY;
	}
	botBody->SetTransform(finalPos, botBody->GetAngle());

	dashCooldown = 30;

}

Bot* Andromalius::clone(Game *game)
{
	Andromalius *newBot = new Andromalius();
	newBot->setHealth(this->getHealth());
	//game->getGSM()->getPhyiscs()->initAndromalius(newBot, 40, 40, 50);
	newBot->movementPattern->setBody(newBot->getBody());
	newBot->registerGame(this->game);
	newBot->setRangeX(this->rangeX);
	newBot->setRangeY(this->rangeY);
	return newBot;
}