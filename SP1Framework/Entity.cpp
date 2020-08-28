#include "Entity.h"
int Entity::enemyTotal = 5;
int Entity::count = 0;
int Entity::score = 0;
void Entity::setscore(int num)
{
	score = num;
}
Entity::Entity()
{
	type = ' ';
	hp = 1;
	x = 0;
	y = 0;
	C.X = 0;
	C.Y = 0;
	direction = 1;
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

void Entity::setX(SHORT x)
{
	this->C.X = x;
}

void Entity::setY(SHORT y)
{
	this->C.Y = y;
}

void Entity::setdirection(int direction)
{
	this->direction = direction;
}

int Entity::getHP(void)
{
	return this->hp;
}

int Entity::getscore(void)
{
	return score;
}

int Entity::getdirection(void)
{
	return direction;
}

char Entity::gettype(void)
{
	return type;
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

void Entity::addtomap(char add, maps& Gamemap)
{
	if (Gamemap.getchar(C.Y, C.X) == ' ')
	{
		Gamemap.setchar(add, C.X, C.Y);
	}
}

char Entity::move(double time, char ent, maps& gamemap, COORD Player)
{
	if (direction == 1)
	{
		if (gamemap.getchar(C.Y, (C.X - 1)) != '1' && gamemap.getchar(C.Y, (C.X - 1)) != '=' && gamemap.getchar(C.Y+1, C.X-1) != ' ')
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
		if (gamemap.getchar(C.Y, (C.X + 1)) != '1' && gamemap.getchar(C.Y, (C.X + 1)) != '=' && gamemap.getchar(C.Y+1, C.X+1) != ' ')
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
	return 0;
}

char Entity::collisioncheck(maps& gamemap)
{
	int iX = C.X;
	int iY = C.Y;
	if (gamemap.getchar(iY - 1,iX) != ' ' && gamemap.getchar(iY - 1, iX) != '=' && gamemap.getchar(iY - 1, iX) != 'H' && gamemap.getchar(iY - 1, iX) != '1')
	{
		return gamemap.getchar(iY - 1, iX);
	}
	else if (gamemap.getchar(iY, iX - 1) != ' ' && gamemap.getchar(iY, iX - 1) != '=' && gamemap.getchar(iY, iX - 1) != 'H' && gamemap.getchar(iY, iX - 1) != '1')
	{
		return gamemap.getchar(iY, iX - 1);
	}
	else if (gamemap.getchar(iY + 1, iX) != ' ' && gamemap.getchar(iY + 1, iX) != '=' && gamemap.getchar(iY + 1, iX) != 'H' && gamemap.getchar(iY + 1, iX) != '1')
	{
		return gamemap.getchar(iY + 1, iX);
	}
	else if (gamemap.getchar(iY, iX + 1) != ' ' && gamemap.getchar(iY, iX + 1) != '=' && gamemap.getchar(iY, iX + 1) != 'H' && gamemap.getchar(iY, iX + 1) != '1')
	{
		return gamemap.getchar(iY, iX + 1);
	}
	else if (gamemap.getchar(iY, iX) != ' ' && gamemap.getchar(iY, iX) != '=' && gamemap.getchar(iY, iX) != 'H' && gamemap.getchar(iY, iX) != '1')
	{
		return gamemap.getchar(iY, iX);
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
