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

}

void LavaBoss::think(Game *game)
{
	b2Vec2 playerPos = game->getGSM()->getSpriteManager()->getPlayer()->getBody()->GetPosition();
	//this->getBody()->GetWorldCenter();
	b2Vec2 bossPos = this->getBody()->GetPosition();
	if ((playerPos.x >= 17.538 || playerPos.x <= 14.387) && (playerPos.y < 28.49 || playerPos.y > 26.6256294))
	{
		if (playerPos.x < bossPos.x)
			this->setCurrentState(L"IDLE_LEFT");
		else
			this->setCurrentState(L"IDLE_RIGHT");

	}
	else if (playerPos.y > bossPos.y + 1)
		this->setCurrentState(L"IDLE_FOWARD");
	else if (playerPos.y < bossPos.y)
		this->setCurrentState(L"IDLE_BACK");
}

Bot* LavaBoss::clone(Game *game)
{
	LavaBoss *newBot = new LavaBoss();
	newBot->setHealth(this->getHealth());
	game->getGSM()->getPhyiscs()->initLavaBoss(newBot, 192, 234, 50);
	newBot->movementPattern->setBody(newBot->getBody());
	return newBot;
}
