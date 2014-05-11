#pragma once
#include "MeleeBot.h"
#include "src\sssf\game\Game.h"
#include "SimpleMovement.h"
class LavaBoss : public MeleeBot
{
private:
	//int walkTicks;
	//string lastState;
	//int ticksMoved;
	SimpleMovement* movementPattern;
	int lavaBurstCooldown;
	int sinkCooldown;
	int selectedGun;
	bool invincible;
public:
	LavaBoss();
	~LavaBoss();

	enum gunSelection
	{
		LAVA_BURST,
		SWIPE,
		ACID

	};

	void setSelectedGun(unsigned int x)
	{
		selectedGun = x;
	}

	void setInvincible(bool iv){ invincible = iv; }
	bool getInvincible(){ return invincible; }
	void changeAnimationState();
	void changeMovementType(int type) { movementPattern->changeMovementType(type); }
	//void setWalkTicks(int wT) { walkTicks = wT; }
	Bot* clone(Game *game);
	void think(Game *game);

};

