#pragma once
#include "Entity.h"
class SlowMob : public Entity
{
public:
	SlowMob();
	~SlowMob();
	void spawnSlowMob(int h, int m);
	char move(double time, char ent, maps& gamemap, COORD Player);
};

