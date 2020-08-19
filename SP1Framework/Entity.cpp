#include "Entity.h"
int enemyTotal = 10;
int count = 0;
Entity::Entity()
{
	hp = 1;
	mp = 1;
}

Entity::~Entity()
{
}

void Entity::spawnEntity(int h, int m)
{
	hp = h;
	mp = m;
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
