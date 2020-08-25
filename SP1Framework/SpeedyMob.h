#pragma once
#include "Entity.h"
class SpeedyMob : public Entity
{
public:
	SpeedyMob();
	~SpeedyMob();
	void spawnSpeedyMob(int h, int m);
    char move(double time, char ent, maps& gamemap, COORD Player);
};

