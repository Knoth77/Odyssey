#pragma once
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "src\sssf\game\Game.h"
class Player :	public AnimatedSprite
{
private:

	int playerHealth;
	int selectedGun;
	unsigned int nextShowCountdown;
	bool collidingWithBot;
	unsigned int playerLives;
	bool outOfHealth;
	bool outOfLives;
	int playerStartingHealth;
	int immuneCounter;
	bool isImmune;
	Game *game;
	

public:
	Player();
	~Player();

	enum gunSelection
	{
		DEFAULT,
		SPREAD,
		ROCKET

	};

	void registerPlayer(Game *g)
	{
		game = g;
	}

	bool isOutOfLives()
	{
		return outOfLives;
	}

	void decPlayerHealth(int x);

	int getStartingHealth()
	{
		return playerStartingHealth;
	}

	void setPlayerLives(unsigned int x)
	{
		playerLives = x;
	}
	unsigned int getPlayerLives()
	{
		return playerLives;
	}
	void setSelectedGun(unsigned int x)
	{
		selectedGun = x;
	}

	 int getSelectedGun()
	{
		return selectedGun;
	}

	void updateSprite();
	int	getPlayerHealth()	{ return playerHealth; }

	void setPlayerHealth(unsigned int x)
	{
		playerHealth = x;
	}

	void setStartingHealth(int x)
	{
		playerStartingHealth = x;
	}

	unsigned int getNextShotTime()
	{
		return nextShowCountdown;
	}

	void setNextShotTime(unsigned int x)
	{
		nextShowCountdown = x;
	}

	void decNextShotTime()
	{
		nextShowCountdown--;
	}

	void setCollidingWithBot(bool b)
	{
		collidingWithBot = b;
	}

	bool isCollidingWithBot()
	{
		return collidingWithBot;
	}

	void reset()
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
};


