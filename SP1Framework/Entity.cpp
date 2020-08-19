#include "Entity.h"

Entity::Entity()
{
	enemyTotal = 10;
	count = 0;
	hp = 1;
	mp = 1;
}

Entity::~Entity()
{
}

void Entity::setHP(int h)
{
	hp = h;
}

void Entity::setMP(int m)
{
	mp = m;
}

int Entity::getHP(void)
{
	return hp;
}

int Entity::getMP(void)
{
	return mp;
}
