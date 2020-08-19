#include "SlowMob.h"

SlowMob::SlowMob()
{
	hp = 1;
	mp = 1;
}

SlowMob::~SlowMob()
{
}

void SlowMob::spawnSlowMob(int h, int m)
{
	hp = h;
	mp = m;
}

void SlowMob::setHP(int h)
{
	hp = h;
}

void SlowMob::setMP(int m)
{
	mp = m;
}

int SlowMob::getHP(void)
{
	return hp;
}

int SlowMob::getMP(void)
{
	return mp;
}
