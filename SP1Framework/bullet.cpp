#include "bullet.h"

int bullet::bulletnumber = 0;

bullet::bullet()
{
	damage = 1;
	bulletnumber++;
}

bullet::bullet(int direction, int x, int y)
{
	damage = 1;
	this->direction = direction;
	C.X = x;
	C.Y = y;
	bulletnumber++;
}

bullet::~bullet()
{
	bulletnumber--;
}

void bullet::spawn_bullet(int direction, int iX, int iY)
{
	this->direction = direction;
	C.X = iX;
	C.Y = iY;
}

void bullet::set_x(int x)
{
	this->x = x;
}

void bullet::set_y(int y)
{
	this->y = y;
}

void bullet::set_damage(int dmg)
{
	damage = dmg;
}

int bullet::get_damage(void)
{
	return damage;
}

int bullet::getbulletnumber()
{
	return bulletnumber;
}

char bullet::move(char ent, maps& gamemap)
{
	if (direction == 1)
	{
		if (gamemap.getchar(C.Y, (C.X - 1)) != '1' && gamemap.getchar(C.Y, (C.X - 1)) != '=')
		{
			gamemap.setchar(' ', C.X, C.Y);
			C.X -= 1;
			gamemap.setchar(ent, C.X, C.Y);
			return gamemap.getchar(C.Y, (C.X - 1));
		}
	}
	else if (direction == 2)
	{
		if (gamemap.getchar(C.Y, (C.X + 1)) != '1' && gamemap.getchar(C.Y, (C.X + 1)) != '=')
		{
			gamemap.setchar(' ', C.X, C.Y);
			C.X += 1;
			gamemap.setchar(ent, C.X, C.Y);
			return gamemap.getchar(C.Y, (C.X + 1));
		}
	}
}
