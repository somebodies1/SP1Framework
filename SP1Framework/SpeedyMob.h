#pragma once
#include "Entity.h"
class SpeedyMob : public Entity
{
public:
	SpeedyMob();
	~SpeedyMob();
    char move(double time, char ent, maps& gamemap, COORD Player);
};

