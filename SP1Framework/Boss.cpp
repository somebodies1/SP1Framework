#include "Boss.h"

Boss::Boss()
{
	hp = 1;
	mp = 1;
}

Boss::~Boss()
{
}

void Boss::spawnBoss(int h, int m)
{
	hp = h;
	mp = m;
}

void Boss::setHP(int h)
{
	hp = h;
}

void Boss::setMP(int m)
{
	mp = m;
}

int Boss::getHP(void)
{
	return hp;
}

int Boss::getMP(void)
{
	return mp;
}
