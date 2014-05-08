#include "Effect.h"


Effect::Effect()
{
	body = NULL;
}


Effect::~Effect()
{
}

void Effect::update()
{
	AnimatedSprite::updateSprite();
}
