#include "PhysicsCollisionListener.h"
#include "src\sssf\gsm\ai\Bot.h"
#include "src\sssf\game\Game.h"
#include "src\sssf\gsm\state\GameStateManager.h"
#include "physicsManager.h"
#include "MeleeBot.h"
#include "Fireball.h"
#include "Laser.h"


PhysicsCollisionListener::PhysicsCollisionListener()
{
}


PhysicsCollisionListener::~PhysicsCollisionListener()
{
}

void PhysicsCollisionListener::BeginContact(b2Contact *contact)
{
	void *dataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void *dataB = contact->GetFixtureB()->GetBody()->GetUserData();

	physicsManager *phy = game->getGSM()->getPhyiscs();

	// THIS IS ASSUMING EVERY PIECE OF DATA ATTACHED TO BODIES ARE ANIMATED SPRITES (MIGHT CAUSE ERRORS LATER)
	AnimatedSprite *A = static_cast<AnimatedSprite*>(dataA);
	AnimatedSprite *B = static_cast<AnimatedSprite*>(dataB);

	bool sensA = contact->GetFixtureA()->IsSensor();
	bool sensB = contact->GetFixtureB()->IsSensor();

	if (dataA == NULL || dataB == NULL) // ITS A WALL COLLISION 
	{
		// ADDITIONAL DYNAMIC CASTING WILL HAVE TO BE DONE TO DETERMAIN WHAT TYPE OF BULLET IT ACTUALLY IS
		Bullet *b;

		if (dataA != NULL) // CHECK IF DATA A IS A BULLET
		{
			b = dynamic_cast<Bullet*>(A);
			if (b != 0)
			{
				b->handleCollision(game);
			}
		}
		//BUG
		else
		{
			b = dynamic_cast<Bullet*>(B);
			Fireball *f = dynamic_cast<Fireball*>(b);

			if (b != 0)
			{
				b->handleCollision(game);
			}
		}
		// IF NONE OF THEM WERE BULLETS IT A BOT/BOSS OR THE PLAYER HIT THE WALL AND WE DONT NEED TO DO ANYTHING


	}
	else
	{
		// LOTS OF THINGS TO TEST
		Bullet *a;
		Bullet *b;
		a = dynamic_cast<Bullet*>(A);
		b = dynamic_cast<Bullet*>(B);

		if (a == 0 && b == 0) // COLLISION DID NOT INVOLVE BULLETS
		{
			// CHECK FOR SENSOR COLLISION
			bool sensA = contact->GetFixtureA()->IsSensor();
			bool sensB = contact->GetFixtureB()->IsSensor();

			
			if ((sensA && sensB) || !(sensA || sensB))
			{
				if (!(sensA || sensB)) // COLLISON WAS BETWEEN PLAYER AND BOT
				{
					if (contact->GetFixtureA()->GetFilterData().categoryBits == phy->PLAYER)
					{
						Player *p = dynamic_cast<Player*>(A);
						p->setCollidingWithBot(true);
					}
					else if (contact->GetFixtureB()->GetFilterData().categoryBits == phy->PLAYER)
					{
						Player *p = dynamic_cast<Player*>(B);
						p->setCollidingWithBot(true);
					}

				}
			}
			else
			{
				//PLAYER IN BOT RADIUS
				if (sensA)
				{
					Bot *bot = static_cast<Bot*>(A);
					bot->setPlayerInRadius(true);

					if (contact->GetFixtureA()->GetFilterData().categoryBits == phy->BOT_DAMAGE_RADIUS)
					{
						MeleeBot *mBot = dynamic_cast<MeleeBot*>(A);
						mBot->setInAttackRadius(true);
					}					
				}
				else
				{
					Bot *bot = static_cast<Bot*>(B);
					bot->setPlayerInRadius(true);

					if (contact->GetFixtureB()->GetFilterData().categoryBits == phy->BOT_DAMAGE_RADIUS)
					{
						MeleeBot *mBot = dynamic_cast<MeleeBot*>(B);
						mBot->setInAttackRadius(true);
					}
				}
			}
		}
		else
		{

			bool sensA = contact->GetFixtureA()->IsSensor();
			bool sensB = contact->GetFixtureB()->IsSensor();

			if (sensA)
			{
				Bot *bot = static_cast<Bot*>(A);
				if ((contact->GetFixtureA()->GetFilterData().categoryBits == phy->BOT_DODGE) && (bot->getType() == L"MAGE_BOSS"))
				{
					//Bot *bot = dynamic_cast<Bot*>(A);
					bot->setPlayerInRadius(true);
					return;
				}

			}
			else if (sensB)
			{
				Bot *bot = static_cast<Bot*>(B);
				if ((contact->GetFixtureB()->GetFilterData().categoryBits == phy->BOT_DODGE) && (bot->getType() == L"MAGE_BOSS"))
					{
						//Bot *bot = dynamic_cast<Bot*>(B);
						bot->setPlayerInRadius(true);
						return;
					}
			}


			if (sensA || sensB)
			{
				return;
			}

			if (a != 0) // a is the bullet
			{
				b2Fixture *detectFixture = contact->GetFixtureA();
				detectFixture->GetType();
				if (contact->GetFixtureA()->GetFilterData().categoryBits != phy->ENEMY_BULLET)
				{
					Bot *bot = static_cast<Bot*>(B);
					if (a->getType() == L"S")
						bot->setHealth(bot->getHealth() - a->getSecondaryDamage());
					else
						bot->setHealth(bot->getHealth() - a->getPrimaryDamage());

					bot->setJustShot(true);
					a->handleCollision(game);
				}
				else
				{
					a->handleCollision(game);
					Player *p = static_cast<Player*>(B);
					p->decPlayerHealth(a->getPrimaryDamage());
				}

			}
			else // b is the bullet
			{
				if (contact->GetFixtureB()->GetFilterData().categoryBits != phy->ENEMY_BULLET)
				{
					Bot *bot = static_cast<Bot*>(A);
					if (b->getType() == L"S")
						bot->setHealth(bot->getHealth() - b->getSecondaryDamage());
					else
						bot->setHealth(bot->getHealth() - b->getPrimaryDamage());

					bot->setJustShot(true);
					b->handleCollision(game);
				}
				else
				{
					b->handleCollision(game);
					Player *p = static_cast<Player*>(A);
					p->decPlayerHealth(b->getPrimaryDamage());
				}

			}
		}


	}
}

void PhysicsCollisionListener::EndContact(b2Contact *contact)
{
	void *dataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void *dataB = contact->GetFixtureB()->GetBody()->GetUserData();

	// THIS IS ASSUMING EVERY PIECE OF DATA ATTACHED TO BODIES ARE ANIMATED SPRITES (MIGHT CAUSE ERRORS LATER)
	AnimatedSprite *A = static_cast<AnimatedSprite*>(dataA);
	AnimatedSprite *B = static_cast<AnimatedSprite*>(dataB);

	physicsManager *phy = game->getGSM()->getPhyiscs();

	bool sensA = contact->GetFixtureA()->IsSensor();
	bool sensB = contact->GetFixtureB()->IsSensor();

	if ((sensA && sensB) || !(sensA || sensB))
	{
		if (!(sensA || sensB)) // COLLISON WAS BETWEEN PLAYER AND BOT
		{
			if (contact->GetFixtureA()->GetFilterData().categoryBits == phy->PLAYER)
			{
				Player *p = dynamic_cast<Player*>(A);
				p->setCollidingWithBot(false);
			}
			else if (contact->GetFixtureB()->GetFilterData().categoryBits == phy->PLAYER)
			{
				Player *p = dynamic_cast<Player*>(B);
				p->setCollidingWithBot(false);
			}

		}
	}
	else
	{
		//PLAYER IN BOT RADIUS
		if (sensA)
		{
			//BOT DMG RADIUS IS A SPECIFIC RADIUS TO INDICATED MELEE TYPE BOTS ARE IN "MELEE RANGE"
			if (contact->GetFixtureA()->GetFilterData().categoryBits == phy->BOT_DAMAGE_RADIUS)
			{
				MeleeBot *mBot = dynamic_cast<MeleeBot*>(A);
				mBot->setInAttackRadius(false);
			}
			else
			{
				Bot *bot = static_cast<Bot*>(A);
				bot->setPlayerInRadius(false);
			}
		}
		else
		{

			if (contact->GetFixtureB()->GetFilterData().categoryBits == phy->BOT_DAMAGE_RADIUS)
			{
				MeleeBot *mBot = dynamic_cast<MeleeBot*>(B);
				mBot->setInAttackRadius(false);
			}
			else
			{
				Bot *bot = static_cast<Bot*>(B);
				bot->setPlayerInRadius(false);
			}
		}
	}
}