#include "StationaryMob.h"

StationaryMob::StationaryMob()
{
	hp = 2;
	type = 'L';
}

StationaryMob::~StationaryMob()
{
	score += 10;
}

char StationaryMob::move(double time, char ent, maps& gamemap, COORD Player)
{
	gamemap.setchar(ent, C.X, C.Y);
	return 0;
}
