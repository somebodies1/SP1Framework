#include "SpeedyMob.h"

SpeedyMob::SpeedyMob()
{
	hp = 1;
	mp = 1;
	type = 'K';
}

SpeedyMob::~SpeedyMob()
{
}

void SpeedyMob::spawnSpeedyMob(int h, int m)
{
	hp = h;
	mp = m;
}

char SpeedyMob::move(double time, char ent, maps& gamemap)
{
	if (fmod(time, 0.2) < 0.1)
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

