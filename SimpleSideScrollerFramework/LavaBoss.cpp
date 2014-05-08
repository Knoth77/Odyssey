#include "LavaBoss.h"
#include "physicsManager.h"
#include "src\sssf\game\Game.h"
#include "src\sssf\gsm\state\GameStateManager.h"
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "Player.h"


LavaBoss::LavaBoss()
{
	movementPattern = new SimpleMovement(this->body, SimpleMovement::SQUARE);
	//walkTicks = 20;
	//lastState = "north";
	//ticksMoved = 0;
	type = L"LAVA_BOSS";
}



LavaBoss::~LavaBoss()
{
}

void LavaBoss::changeAnimationState()
{
	if (this->getMarkedForDeath() == true)
	{
		return;
	}

		this->setCurrentState(L"IDLE");
	/*if (lastState.find("north") != -1)
	this->setCurrentState(states[1]);
	else if (lastState.find("east") != -1)
	this->setCurrentState(states[3]);
	else if (lastState.find("south") != -1)
	this->setCurrentState(states[2]);
	else//west
	this->setCurrentState(states[4]);*/


}

void LavaBoss::think(Game *game)
{
	if (0 < 1)
		int i = 101;

	return;
}

Bot* LavaBoss::clone(Game *game)
{
	LavaBoss *newBot = new LavaBoss();
	newBot->setHealth(this->getHealth());
	game->getGSM()->getPhyiscs()->initMeleeBot(newBot,32,32,50);
	newBot->movementPattern->setBody(newBot->getBody());
	return newBot;
}
