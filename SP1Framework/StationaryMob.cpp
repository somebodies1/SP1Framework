#include "StationaryMob.h"

StationaryMob::StationaryMob()
{
	hp = 2;
	mp = 1;
	type = 'L';
}

StationaryMob::~StationaryMob()
{
}

void StationaryMob::spawnStationaryMob(int h, int m)
{
	hp = h;
	mp = m;
}

char StationaryMob::move(double time, char ent, maps& gamemap, COORD Player)
{
	gamemap.setchar(ent, C.X, C.Y);
	return 0;
}
