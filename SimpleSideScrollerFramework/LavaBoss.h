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
public:
	LavaBoss();
	~LavaBoss();
	void changeAnimationState();
	void changeMovementType(int type) { movementPattern->changeMovementType(type); }
	//void setWalkTicks(int wT) { walkTicks = wT; }
	Bot* clone(Game *game);
	void think(Game *game);

};

