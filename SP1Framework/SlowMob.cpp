#include "SlowMob.h"

SlowMob::SlowMob()
{
	hp = 5;
	mp = 1;
	type = '#';
}

SlowMob::~SlowMob()
{
}

void SlowMob::spawnSlowMob(int h, int m)
{
	hp = h;
	mp = m;
}

char SlowMob::move(double time, char ent, maps& gamemap)
{
	if (fmod(time, 0.2) < 0.01)
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
