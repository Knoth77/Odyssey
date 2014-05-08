#pragma once
#include "MeleeBot.h"
#include "src\sssf\game\Game.h"
#include "SimpleMovement.h"
#include "src\sssf\gsm\state\GameStateManager.h"
#include "src\sssf\gsm\sprite\SpriteManager.h"
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "Player.h"
class MageBoss : public MeleeBot
{
private:
	//int walkTicks;
	//string lastState;
	//int ticksMoved;
	SimpleMovement* movementPattern;
	unsigned int bossHealth;
	int selectedGun;
	int fireCooldown;
	int bulletCooldown;
	int bulletFire;
	int dashCooldown;
	boolean pivot;
	boolean fired;
	bool dashB;
public:
	MageBoss();
	~MageBoss();

	enum gunSelection
	{
		FIREBALL,
		MAGE_BULLET,
		ACID

	};

	void setSelectedGun(unsigned int x)
	{
		selectedGun = x;
	}

	int getSelectedGun()
	{
		return selectedGun;
	}

	int	getBossHealth()	{ return bossHealth; }

	boolean getPivot() { return pivot; }
	void setPivot(boolean p) { pivot = p; }

	void setBossHealth(unsigned int x)
	{
		bossHealth = x;
	}

	unsigned int getFireCooldown()
	{
		return fireCooldown;
	}

	void setFireCooldown(int x)
	{
		fireCooldown = x;
	}

	void decFireCooldown()
	{
		fireCooldown--;
	}

	unsigned int getBulletCooldown()
	{
		return bulletCooldown;
	}

	void setBulletCooldown(int x)
	{
		bulletCooldown = x;
	}

	void decBulletCooldown()
	{
		bulletCooldown--;
	}

	void changeAnimationState();
	void dash(Game *game);
	void changeMovementType(int type) { movementPattern->changeMovementType(type); }
	//void setWalkTicks(int wT) { walkTicks = wT; }
	Bot* clone(Game *game);
	void think(Game *game);

};

