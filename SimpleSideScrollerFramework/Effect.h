#pragma once
#include "src\sssf\gsm\sprite\AnimatedSprite.h"
#include "src\sssf\game\Game.h"
#include "stdafx.h"

class Effect :	public AnimatedSprite
{

protected:

	wstring type;

public:
	Effect();
	~Effect();

	void update();
	wstring getType()
	{
		return type;
	}

	virtual Effect* clone(Game *game) = 0;
};

