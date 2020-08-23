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
	direction = 1;
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

void Entity::spawnEntity(int x, int y)
{
	this->C.X = x;
	this->C.Y = y;
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

void Entity::addtomap(char add, maps& Gamemap)
{
	if (Gamemap.getchar(C.Y, C.X) == ' ')
	{
		Gamemap.setchar(add, C.X, C.Y);
	}
}

void Entity::move(char ent, maps& gamemap)
{
	if (direction == 1)
	{
		if (gamemap.getchar(C.Y, (C.X - 1)) != '1' && gamemap.getchar(C.Y, (C.X - 1)) != '=')
		{
			gamemap.setchar(' ', C.X, C.Y);
			C.X -= 1;
			gamemap.setchar(ent, C.X, C.Y);
		}
		else
		{
			direction = 2;
		}
	}
	else if(direction == 2)
	{
		if (gamemap.getchar(C.Y, (C.X + 1)) != '1' && gamemap.getchar(C.Y, (C.X + 1)) != '=')
		{
			gamemap.setchar(' ', C.X, C.Y);
			C.X += 1;
			gamemap.setchar(ent, C.X, C.Y);
		}
		else
		{
			direction = 1;
		}
	}
}

char Entity::collisioncheck(maps& gamemap)
{
	int iX = C.X;
	int iY = C.Y;
	if (gamemap.getchar(iY - 1,iX) != ' ' && gamemap.getchar(iY - 1, iX) != '=' && gamemap.getchar(iY - 1, iX) != 'H')
	{
		return gamemap.getchar(iY - 1, iX);
	}
	else if (gamemap.getchar(iY, iX - 1) != ' ' && gamemap.getchar(iY, iX - 1) != '=' && gamemap.getchar(iY, iX - 1) != 'H')
	{
		return gamemap.getchar(iY, iX - 1);
	}
	else if (gamemap.getchar(iY + 1, iX) != ' ' && gamemap.getchar(iY + 1, iX) != '=' && gamemap.getchar(iY + 1, iX) != 'H')
	{
		return gamemap.getchar(iY + 1, iX);
	}
	else if (gamemap.getchar(iY, iX + 1) != ' ' && gamemap.getchar(iY, iX + 1) != '=' && gamemap.getchar(iY, iX + 1) != 'H')
	{
		return gamemap.getchar(iY, iX + 1);
	}
	else
	{
		return ' ';
	}
	//if (gamemap.getchar(iY, iX) == 'Z')
	//{
	//	return 'Z';
	//}
	//else if (gamemap.getchar(iY - 1, iX) == 'Z')
	//{
	//	return 'Z';
	//}
	//else if (gamemap.getchar(iY, iX - 1) == 'Z')
	//{
	//	return 'Z';
	//}
	//else if (gamemap.getchar(iY + 1, iX) == 'Z')
	//{
	//	return 'Z';
	//}
	//else if (gamemap.getchar(iY, iX + 1) == 'Z')
	//{
	//	return 'Z';
	//}
	//else
	//{
	//	return ' ';
	//}
}
