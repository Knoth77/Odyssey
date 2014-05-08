#include "MageBoss.h"
#include "Fireball.h"
#include "MageBullet.h"



MageBoss::MageBoss()
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
}



MageBoss::~MageBoss()
{
}

void MageBoss::changeAnimationState()
{
}

void MageBoss::think(Game *game)
{
	if (this->getCurrentState() == L"IDLE" || this->getCurrentState() == L"IDLE_RIGHT")
	{
		if (this->getMarkedForDeath() == true)
		{
			this->setCurrentState(L"PHASE_TWO_IDLE");
			this->setMarkedForDeath(false);
			this->setHealth(500);
		}
		else
		{	
			if (this->isPlayerInRadius() || this->wasJustShot())
			{
					//Bullet *bullet = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"FIREBALL");
					/*b2Vec2 run;
					b2Body *botBody = this->getBody();
					b2Body *player = game->getGSM()->getPhyiscs()->getPlayerBody();
					run.x = botBody->GetPosition().x - player->GetPosition().x;
					run.y = botBody->GetPosition().y - player->GetPosition().y;
					run.Normalize();
					run *= 2;
					this->getBody()->SetLinearVelocity(run);
					setPivot(false);*/

					//this->setSelectedGun(FIREBALL);
					if (this->getFireCooldown() <= 0)
					{
						this->setSelectedGun(FIREBALL);
						Bullet *bullet = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"FIREBALL");
						//game->getAudio()->playSound(L"data\\sounds\\laser_pro.wav", false);
						bullet->setDamageType('P');
						bullet->setCurrentState(L"PRIMARY_FIRE");
						game->getGSM()->getPhyiscs()->activateEnemyBullet(bullet, this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);
						game->getGSM()->getSpriteManager()->addActiveBullet(bullet);
						this->setFireCooldown(30);
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

				movementPattern->processNextMovement();
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
				/*b2Vec2 run;
				b2Body *botBody = this->getBody();
				b2Body *player = game->getGSM()->getPhyiscs()->getPlayerBody();
				run.x = botBody->GetPosition().x - player->GetPosition().x;
				run.y = botBody->GetPosition().y - player->GetPosition().y;
				run.Normalize();
				run *= 2;
				this->getBody()->SetLinearVelocity(run);
				setPivot(false);*/
				
				//this->setSelectedGun(MAGE_BULLET);
				//Bullet *fireBall = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"FIREBALL");
				//Bullet *mageBullet = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"MAGE_BULLET");
				if (this->getBulletCooldown() <= 0)
				{
					this->setSelectedGun(MAGE_BULLET);
					Bullet *mageBullet = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"MAGE_BULLET");
					//game->getAudio()->playSound(L"data\\sounds\\laser_pro.wav", false);
					//Bullet *bullet = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"MAGE_BULLET");
					mageBullet->setDamageType('P');
					mageBullet->setCurrentState(L"PRIMARY_FIRE");
					game->getGSM()->getPhyiscs()->activateEnemyBullet(mageBullet, this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);
					game->getGSM()->getSpriteManager()->addActiveBullet(mageBullet);
					this->setBulletCooldown(50);
					bulletFire = 10;
					fired = true;
				}
				else
				{
					this->decBulletCooldown();
				}
				if (fired == true)
				{
					if (bulletFire == 0)
					{
						b2Vec2 bullPos;
						list<Bullet*>::iterator active = game->getGSM()->getSpriteManager()->getActiveBulletsIterator();
						while (active != game->getGSM()->getSpriteManager()->getEndOfActiveBulletsIterator())
						{
							Bullet *b = (*active);
							if (b->getType() == L"MAGE_BULLET")
							{
								bullPos = b->getBody()->GetPosition();
								b->handleCollision(game);
							}
							active++;
						}
						float pixelScaling = game->getGSM()->getPhyiscs()->getPixelScaling();
						Effect *explosionSprite = game->getGSM()->getSpriteManager()->getEffectRecycler()->retrieveEffect(game, L"EXPLOSION");
						explosionSprite->setDefaultX(((bullPos.x) / pixelScaling) - 20);
						explosionSprite->setDefaultY(((bullPos.y) / pixelScaling) - 20);
						game->getGSM()->getSpriteManager()->addEffect(explosionSprite);
					}
					else 
						bulletFire--;
				}

				if (this->getFireCooldown() <= 0)
				{
					this->setSelectedGun(FIREBALL);
					Bullet *fireBall = game->getGSM()->getSpriteManager()->getBulletRecycler()->retrieveBullet(game, L"FIREBALL");
					//game->getAudio()->playSound(L"data\\sounds\\laser_pro.wav", false);
					fireBall->setDamageType('P');
					fireBall->setCurrentState(L"PRIMARY_FIRE");
					game->getGSM()->getPhyiscs()->activateEnemyBullet(fireBall, this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);
					game->getGSM()->getSpriteManager()->addActiveBullet(fireBall);
					this->setFireCooldown(30);
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

				movementPattern->processNextMovement();
				changeAnimationState();
			}

		}
	}
	else if (this->getCurrentState() == L"PHASE_THREE_IDLE" || this->getCurrentState() == L"PHASE_THREE_SHOCK")
	{
		if (this->getCurrentState() == L"PHASE_THREE_IDLE")
		{
			/*float pixelScaling = game->getGSM()->getPhyiscs()->getPixelScaling();
			b2PolygonShape shape;
			shape.SetAsBox((252 * pixelScaling) / 2, (288 * pixelScaling) / 2);
			b2Fixture *ft = this->getBody()->GetFixtureList();
			b2Shape *sp = ft->GetShape();
			sp-> = shape;*/
			//ftl.shape = ft->GetShape();
			//b2Shape *sp = ft->GetShape();
			
			//this->getBody()->SetTransform(bPos, 0.0f);
		}
		this->setCurrentState(L"PHASE_THREE_SHOCK");
	}
	
}

void MageBoss::dash(Game game)
{
	//b2Vec2 run;
	//b2Body *botBody = this->getBody();
	////b2Body *player = game->getGSM()->getPhyiscs()->getPlayerBody();
	//run.x = botBody->GetPosition().x - player->GetPosition().x;
	//run.y = botBody->GetPosition().y - player->GetPosition().y;
	//run.Normalize();
	//run *= 2;
	//this->getBody()->SetLinearVelocity(run);
	//setPivot(false);
}

Bot* MageBoss::clone(Game *game)
{
	MageBoss *newBot = new MageBoss();
	newBot->setHealth(this->getHealth());
	game->getGSM()->getPhyiscs()->initMageBoss(newBot, 40, 40, 50);
	newBot->movementPattern->setBody(newBot->getBody());
	return newBot;
}
