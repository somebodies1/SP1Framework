#pragma once
#include "Entity.h"
class SlowMob : public Entity
{
public:
	SlowMob();
	~SlowMob();
	char move(double time, char ent, maps& gamemap, COORD Player);
};

