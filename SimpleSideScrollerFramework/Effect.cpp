#include "Effect.h"


Effect::Effect()
{
	body = NULL;
}


Effect::~Effect()
{
}

void Effect::reset()
{
	this->animationCounter = 0;
	this->frameIndex = 0;
}

void Effect::update()
{
	AnimatedSprite::updateSprite();
}
