#include "Entity.h"
int Entity::enemyTotal = 5;
int Entity::count = 0;
Entity* counter[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
Entity::Entity()
{
	hp = 1;
	mp = 1;
	x = 0;
	y = 0;
	C.X = 0;
	C.Y = 0;
	if (enemyTotal > count)
	{
		if (counter[count] != nullptr)
		{
			counter[count] = new Entity;
			count++;
		}
	}
	this->id = count;
}

Entity::~Entity()
{
}

void Entity::spawnEntity(int h, int m)
{
	this->hp = h;
	this->mp = m;
}

void Entity::setHP(int h)
{
	this->hp = h;
}

void Entity::setMP(int m)
{
	this->mp = m;
}

void Entity::setX(SHORT x)
{
	this->C.X = x;
}

void Entity::setY(SHORT y)
{
	this->C.Y = y;
}

int Entity::getHP(void)
{
	return this->hp;
}

int Entity::getMP(void)
{
	return this->mp;
}

SHORT Entity::X(void)
{
	return this->C.X;
}

SHORT Entity::Y(void)
{
	return this->C.Y;
}

COORD Entity::getXY(void)
{
	return this->C;
}

int Entity::getID(void)
{
	return this->id;
}

void Entity::moveEnemy()
{

}
