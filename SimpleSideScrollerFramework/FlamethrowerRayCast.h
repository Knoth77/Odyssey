#pragma once
#include "../SimpleSideScrollerFramework/Box2D/Dynamics/b2WorldCallbacks.h"
class FlamethrowerRayCast :
	public b2RayCastCallback
{
public:
	FlamethrowerRayCast();
	~FlamethrowerRayCast();
};

