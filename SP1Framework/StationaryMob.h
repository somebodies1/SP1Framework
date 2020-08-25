#pragma once
#include "Entity.h"
class StationaryMob : public Entity
{
private:

public:
	StationaryMob();
	~StationaryMob();

	void spawnStationaryMob(int h, int m);
	char move(double time, char ent, maps& gamemap, COORD Player);
};

