#include "StationaryMob.h"

StationaryMob::StationaryMob()
{
	hp = 1;
	mp = 1;
}

StationaryMob::~StationaryMob()
{
}

void StationaryMob::spawnStationaryMob(int h, int m)
{
	hp = h;
	mp = m;
}

void StationaryMob::setHP(int h)
{
	hp = h;
}

void StationaryMob::setMP(int m)
{
	mp = m;
}

int StationaryMob::getHP()
{
	return hp;
}

int StationaryMob::getMP()
{
	return mp;
}
