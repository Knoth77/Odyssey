#pragma once
#include "MeleeBot.h"
#include "src\sssf\game\Game.h"
#include "SimpleMovement.h"
#include "src\sssf\gsm\state\GameStateManager.h"
#include "src\sssf\gsm\sprite\SpriteManager.h"
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "Player.h"
class RatBot : public MeleeBot
{

private:

	SimpleMovement* movementPattern;
	int thinkTime = 10;
	bool finishedAttacking = true;
	bool chase = false;

public:
	RatBot();
	~RatBot();

	void changeAnimationState();
	void changeMovementType(int type) { movementPattern->changeMovementType(type); }

	void think(Game *game);
	Bot* clone(Game *game);
};

