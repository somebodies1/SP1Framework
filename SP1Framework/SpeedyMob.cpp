#include "SpeedyMob.h"

SpeedyMob::SpeedyMob()
{
	hp = 1;
	mp = 1;
}

SpeedyMob::~SpeedyMob()
{
}

void SpeedyMob::spawnSpeedyMob(int h, int m)
{
	hp = h;
	mp = m;
}

void SpeedyMob::setHP(int h)
{
	hp = h;
}

void SpeedyMob::setMP(int m)
{
	mp = m;
}

int SpeedyMob::getHP(void)
{
	return hp;
}

int SpeedyMob::getMP(void)
{
	return mp;
}
