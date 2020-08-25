#include "Mob.h"

Mob::Mob()
{
	type = 'Z';
	hp = 3;
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

char Mob::move(double time, char ent, maps& gamemap)
{
	if (fmod(time, 0.2) <= 0.02) // Moving the enemies
	{
		if (direction == 1)
		{
			if (gamemap.getchar(C.Y, (C.X - 1)) != '1' && gamemap.getchar(C.Y, (C.X - 1)) != '=' && gamemap.getchar(C.Y + 1, C.X - 1) != ' ')
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
		else if (direction == 2)
		{
			if (gamemap.getchar(C.Y, (C.X + 1)) != '1' && gamemap.getchar(C.Y, (C.X + 1)) != '=' && gamemap.getchar(C.Y + 1, C.X + 1) != ' ')
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
	return 0;
}

