#include "Player.h"
#include "src\sssf\gsm\state\GameStateManager.h"


Player::Player()
{
	selectedGun = gunSelection::DEFAULT;
	playerHealth = 200;
	nextShowCountdown = 2;
	collidingWithBot = false;
	playerLives = 3;
	playerStartingHealth = 200;
	outOfLives = false;
	outOfHealth = false;
	immuneCounter = 66;
	isImmune = false;

}


Player::~Player()
{
	delete status;
	status = NULL;
}

void Player::initStatusSprite()
{
	status = new AnimatedSprite();
	status->setAlpha(255);
	status->setSpriteType(game->getGSM()->getSpriteManager()->getSpriteType(12));
	status->setCurrentState(L"ONFIRE");
	status->setBody(this->getBody());
}

void Player::updateStatus()
{
	status->updateSprite();
}

void Player::updateSprite()
{
	AnimatedSprite::updateSprite();
	
	if (isImmune)
		immuneCounter--;
	if (immuneCounter == 0)
	{
		immuneCounter = 66;
		isImmune = false;
		playerHealth = playerStartingHealth;
		playerLives--;
		outOfHealth = false;
	}
}

void Player::decPlayerHealth(int x)
{
	if (isImmune)
	{
	}
	else
	{
		playerHealth = playerHealth - x;
		if (playerHealth <= 0)
		{
			outOfHealth = true;

			if (playerLives == 0)
			{
				outOfLives = true;
				this->setMarkedForDeath(true);
			}
			else
			{			
				isImmune = true;
				game->getHud()->loseLife();
			}
		}
	}
}
