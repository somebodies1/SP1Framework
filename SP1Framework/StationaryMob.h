#pragma once
#include "Entity.h"
class StationaryMob : public Entity
{
public:
	StationaryMob();
	~StationaryMob();
	char move(double time, char ent, maps& gamemap, COORD Player);
};

