#include "Mob.h"

Mob::Mob()
{
	hp = 1;
	mp = 1;
}

Mob::~Mob()
{
	// blank intentionally
}

void Mob::spawnMob(int h, int m)
{
	hp = h;
	mp = m;
}

void Mob::setHP(int h)
{
	hp = h;
}

void Mob::setMP(int m)
{
	mp = m;
}

int Mob::getHP(void)
{
	return hp;
}

int Mob::getMP(void)
{
	return mp;
}

