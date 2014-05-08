#include "MeleeBot.h"
#include "physicsManager.h"
#include "src\sssf\game\Game.h"
#include "src\sssf\gsm\state\GameStateManager.h"
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "Player.h"


MeleeBot::MeleeBot()
{
	
	this->setPlayerInRadius(false);
	this->setJustShot(false);
	readyToDamagePlayer = false;
	playerInAttackRadius = false;
	dmgCountDown = 33;
	//type = L"MELEE_BOT";
}


MeleeBot::~MeleeBot()
{
}


//silly think
void MeleeBot::think(Game *game)
{



}




