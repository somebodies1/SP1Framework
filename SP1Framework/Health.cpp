#include "Health.h"

Health::Health()
{
	hp = 2;
	type = '+';
}

Health::~Health()
{
	score += 10;
}

char Health::move(double time, char ent, maps& gamemap, COORD Player)
{
	gamemap.setchar(ent, C.X, C.Y);
	if (C.Y >= 24)
	{
		hp = 0;
	}
	return 0;
}
