#pragma once

#include "stdafx.h"
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "Player.h"
#include "Bullet.h"
#include "PhysicsCollisionListener.h"
#include "src\sssf\gsm\ai\Bot.h"

class physicsManager
{

private:

	

	PhysicsCollisionListener *listener;

	b2World *levelSelectWorld;
	b2World *gameWorld;

	bool playerMoveLeft;
	bool playerMoveRight;
	bool playerMoveUp;
	bool playerMoveDown;
	bool viewportMoved;

	b2Body *playerBody;

    bool mouseClicked;

	b2Vec2 clickedPoint;
	b2Vec2 mouseLoc;

	float viewportConverter;
	
	Game *game;

public:
	physicsManager();
	~physicsManager();

	enum collisionCatagory
	{
		WALL = 0x0001,
		PLAYER = 0x0002,
		ENEMY = 0x0004,
		PLAYER_BULLET = 0x0008,
		ENEMY_BULLET = 0x0016,
		BOT_DETECTOR = 0x0032,
		BOT_DAMAGE_RADIUS = 0x0064,
		BOT_RANGEATTACK_RADIUS = 0x0128,
		BOT_DODGE = 0x0256,


	};

	float32 timeStep;     
	int32 velocityIterations;   
	int32 positionIterations;   
	float pixelScaling;

	b2World *getGameWorld()
	{
		return gameWorld;
	}

	float getPixelScaling()
	{
		return pixelScaling;
	}

	b2Body* getPlayerBody()
	{
		return playerBody;
	}

	void setMouseClicked(bool b)
	{
		mouseClicked = b;
	}

	void setMouseVec(float x, float y);
	void setMouseLoc(float x, float y);

	void initLevelSelectWorld();
	void initGameWorld();
	void clearGameWorld();
	void registerGameToListener();

	void deleteSpriteBody(AnimatedSprite *sprite);

	void setGame(Game *g)
	{
		game = g;
	}

	void initSpriteBodyForLevelSelect(AnimatedSprite *sprite, float x, float y);

	void levelSelectWorldStep();

	void initBullet(Bullet *sprite);

	void initEnemyBullet(Bullet *sprite);

	void activateBullet(Bullet *sprite);
	void activateEnemyBullet(Bullet *sprite, float x, float y);

	/*Takes 3 bullets to activate and produce a tri spread like effect*/
	void activateBulletSpread(Bullet *b1, Bullet *b2, Bullet *b3);

	void deactivateBullet(Bullet *sprite);

	void initWallForGame(float x, float y);

	void initTriangleWallForGame(b2Vec2 verts[],int32 count);

	void gameWorldStep();

	void initPlayer(Player *player, float x, float y);

	void movePlayerLeft();
	void movePlayerRight();
	void movePlayerUp();
	void movePlayerDown();
	void viewportM();

	void initMeleeBot(Bot *bot, int bX, int bY, int aR);
	void initMageBoss(Bot *bot, int bX, int bY, int aR);
	void initRangeBot(Bot *bot, int bX, int bY, int aR);
	void activateBot(Bot *bot, float x, float y);
	void deactivateBot(Bot *bot);

	void testResetGameWorld();

	
};

